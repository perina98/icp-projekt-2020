/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#include "vehicle.h"
#include "mainwindow.h"
#include <QGraphicsDropShadowEffect>

/**
 * @brief Vehicle::Vehicle Vehicle constructor
 * @param scene Pointer to scene where new vehicle will be spawned
 * @param line Public transport line of the vehicle
 * @param time Current system time
 * @param busNo Number of the vehicle in the particular line (e.g. Bus 1 in line Yellow)
 */
Vehicle::Vehicle(QGraphicsScene * scene, Line * line, QTime time, int busNo) {
    this->waitOnStop = 0;
    this->streetCnt = 0;
    this->stopCnt = 1;
    this->delay = 0;

    this->myTime = time;
    this->busNo = busNo;

    this->x = line->getLineStops().at(0)->getCoordinates()[0];
    this->y = line->getLineStops().at(0)->getCoordinates()[1];

    myLine = line;
    myStreets = line->getLineStreets();
    myStops = line->getLineStops();
    myTimes = line->getLineTimes();

    transformSchedule();

    this->nextStop = myStops.at(stopCnt);
    this->currStreet = myStreets.at(streetCnt);
    this->roadCoords = currStreet->getCoordinates();
    this->prevStreetsSize = static_cast < int > (myStreets.size());

    this->speedLimit = myStreets.at(streetCnt)->getSpeedLimit();
    this->lineName = line->getLineName();

    square = this;
    scene->addItem(square);
    square->setFlag(QGraphicsItem::ItemIsSelectable);
    square->setPos(x, y);
}


/**
 * @brief Vehicle::transformSchedule Transform schedule of vehicle based on how long after the first vehicle started its journey
 */
void Vehicle::transformSchedule() {
    for (int time: myTimes) {
        QTime test = myTime;
        test = test.addSecs(time * 60);
        schedule.push_back(test);
    }
}


/**
 * @brief Vehicle::scheduleAddHour Rewinds schedule of a vehicle after completing one round
 * @param minutes How much to the future should be the vehicle schedule rewinded
 */
std::vector < QTime > Vehicle::scheduleRewind(int minutes) {
    std::vector < QTime > newTimes;
    for (QTime time: schedule) {
        time = time.addSecs(minutes * 60);
        newTimes.push_back(time);
    }
    return newTimes;
}


/**
 * @brief Vehicle::updatePosition Updates position of the vehicle on the streets
 * @param time Current system time
 */
void Vehicle::updatePosition(QTime time) {
    this->myStops = myLine->getLineStops();
    this->myStreets = myLine->getLineStreets();
    this->speedLimit = currStreet->getSpeedLimit();
    this->myTime = time;

    // Check if deroute was added and where
    checkDeroute();

    double * delta = calculateDelta(roadCoords, 1);
    double speed = 0;

    // New round
    if (stopCnt == 0) {
        double timeBetweenStops = abs(60 - myTimes.back()) - 0.5;
        speed = myLine->getSpeedBetweenStops(myStops.back(), myStops.at(0), timeBetweenStops);
    } else {
        double timeBetweenStops = abs(myTimes.at(stopCnt - 1) - myTimes.at(stopCnt)) - 0.5;
        speed = myLine->getSpeedBetweenStops(myStops.at(stopCnt - 1), myStops.at(stopCnt), timeBetweenStops);
    }

    double nextPosX = delta[0] * speed * speedLimit;
    double nextPosY = delta[1] * speed * speedLimit;

    // Vehicle continues on the new road
    if (!isPointOnLine(x + nextPosX, y + nextPosY)) {

        // New round
        if (streetCnt + 1 == static_cast < int > (myStreets.size())) {
            this->streetCnt = 0;
        }
        // New street
        else {
            this->streetCnt++;
        }

        double jump = math.distance(x, y, x + nextPosX, y + nextPosY);
        this->currStreet = myStreets.at(streetCnt);

        // Length from previous position to the end of the street
        double endPrevStreet = math.distance(x, y, roadCoords[2], roadCoords[3]);
        this->roadCoords = currStreet->getCoordinates();
        this->speedLimit = myStreets.at(streetCnt)->getSpeedLimit();

        // Size of the jump on the new street
        delta = calculateDelta(roadCoords, 1 - endPrevStreet / jump);

        nextPosX = delta[0] * speed * speedLimit;
        nextPosY = delta[1] * speed * speedLimit;

        this->x = roadCoords[0];
        this->y = roadCoords[1];
    }

    // Check if bus is on the bus stop
    if (nextStop->getID() == currStreet->getStreetID()) {
        if (this->onStop(nextPosX, nextPosY)) {
            // Bus stops in the middle of the bus stop
            this->x = nextStop->getCoordinates()[0];
            this->y = nextStop->getCoordinates()[1];

            this->square->setPos(x, y);

            // Wait on stop
            // If bus is delayed more than 30 secs, wait on every stop for 30 seconds
            if (delay > 30) {
                if (++waitOnStop < 30) {
                    return;
                }
                this->waitOnStop = 0;
            }
            // Bus is not delayed significantly, leaves from the stop at hh:mm:00
            else {
                if (myTime.second() != 59) {
                    return;
                }
            }

            // New round
            if (stopCnt + 1 == static_cast < int > (myStops.size())) {
                this->stopCnt = 0;
            }
            // Next stop
            else {
                this->stopCnt++;
            }

            // Bus as at the first stop, schedule moved one hour into the future
            if (stopCnt == 1) {
                this->schedule = scheduleRewind(60);
            }

            // New next stop
            this->nextStop = myStops.at(stopCnt);

            return;
        }
    }

    // Calculate delay, if there is any
    double speedChanged = math.distance(x, y, x + nextPosX, y + nextPosY);
    double speedNormal = math.distance(x, y, x + nextPosX / speedLimit, y + nextPosY / speedLimit);
    this->delay += (speedNormal / speedChanged - 1) * speedLimit;

    this->x += nextPosX;
    this->y += nextPosY;
    this->square->setPos(x, y);
}


/**
 * @brief Vehicle::calculateDelta Calculates the slope of the road on 2D map needed for updating the position
 * @param roadVect Vector containing start and end coordinates of current road vehicle is driving on
 * @param increment How far from the current position will the vehicle actually move
 * @return  Delta - adder to current position on the road
 */
double * Vehicle::calculateDelta(int * roadVect, double increment) {
    int x1 = roadVect[0];
    int y1 = roadVect[1];
    int x2 = roadVect[2];
    int y2 = roadVect[3];

    double ang = atan2(y1 - y2, x1 - x2);

    double * delta = new double[2];
    delta[0] = -cos(ang) * increment;
    delta[1] = -sin(ang) * increment;

    return delta;
}


/**
 * @brief Vehicle::isPointOnLine Checks whether the next position of the vehicle will be on current road or not
 * @param x next X-position of vehicle
 * @param y next Y-position of vehicle
 * @return True if next position of vehicle is on the current street, false otherwise
 */
bool Vehicle::isPointOnLine(double x, double y) {
    double roadLen = currStreet->getStreetLen();
    double distance = math.distance(x, y, roadCoords[0], roadCoords[1]);

    if (fabs(distance) > fabs(roadLen)) {
        return false;
    }

    return true;
}


/**
 * @brief Vehicle::onStop Determines whether the vehicle is on the bus stop
 * @param nexPosX Next position of the vehicle on the X-axis
 * @param nextPosY Next position of the vehicle on the Y-axis
 * @return true if next position is on the bus stop, false otherwise
 */
bool Vehicle::onStop(double nexPosX, double nextPosY) {
    double * stopCoords = nextStop->getCoordinates();

    // Distance of current position to next position
    double distCurrNext = math.distance(x, y, x + nexPosX, y + nextPosY);

    // Distance of current position to stop
    double distCurrStop = math.distance(x, y, stopCoords[0], stopCoords[1]);

    // Distance of stop position to next position
    double distStopNext = math.distance(stopCoords[0], stopCoords[1], x + nexPosX, y + nextPosY);

    // Distance of next position to next next position
    double distCurrNextNext = math.distance(x + nexPosX, y + nextPosY, x + nexPosX * 2, y + nextPosY * 2);

    // Distance of next position to stop
    double distCurrNextStop = math.distance(x + nexPosX, y + nextPosY, stopCoords[0], stopCoords[1]);

    // Distance of stop position to next next position
    double distStopNextNext = math.distance(stopCoords[0], stopCoords[1], x + nexPosX * 2, y + nextPosY * 2);

    // Compare if current position if closer to the stop than the next one
    if (distCurrStop + distStopNext - distCurrNext < distStopNextNext + distCurrNextStop - distCurrNextNext) {
        return true;
    }

    return false;
}


/**
 * @brief Vehicle::positionOnLine get actual position of bus on line
 * Position is relative to the length of the bus line (number between 0 and 1)
 */
double Vehicle::positionOnLine() {
    double lenFromStart = myLine->distanceFromStart(x, y);
    return lenFromStart / myLine->getLineLen();
}


/**
 * @brief Vehicle::checkDeroute Checks if there was a street closure behind the vehicle
 *  If there was, add number of streets in deroute to current street counter
 */
void Vehicle::checkDeroute() {

    // Deroute was added/deleted
    if (static_cast < int > (myStreets.size()) - prevStreetsSize != 0) {
        int cnt = 0;
        for (Street * street: myStreets) {
            if (street->getStreetID() == currStreet->getStreetID()) {
                break;
            }
            cnt++;
        }

        // Deroute was added and vehicle is behind the added street
        if (streetCnt < cnt) {
            this->streetCnt += myStreets.size() - prevStreetsSize;
        }

        // Deroute was deleted and vehicle was in front of the street
        if (streetCnt > cnt) {
            this->streetCnt -= prevStreetsSize - myStreets.size();
        }
    }

    this->prevStreetsSize = static_cast < int > (myStreets.size());
}

/************************* UI *************************/

/**
 * @brief Vehicle::boundingRect Set bounding rectangle of vehicle object
 * @return QRectF bounding object
 */
QRectF Vehicle::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}


/**
 * @brief Vehicle::paint paint rectangle representing vehicle
 * @param painter Painter object
 * @param option options
 * @param widget widget
 */
void Vehicle::paint(QPainter * painter, __attribute__((unused)) const QStyleOptionGraphicsItem * option, __attribute__((unused)) QWidget * widget) {
    QRectF rec = boundingRect();
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if (this->lineName == "Yellow") {
        brush.setColor(QColor(252, 191, 30));
    } else if (this->lineName == "Blue") {
        brush.setColor(QColor(3, 90, 166));
    } else if (this->lineName == "Green") {
        brush.setColor(QColor(34, 139, 34));
    } else {
        brush.setColor(Qt::red);
    }
    painter->fillRect(rec, brush);
    painter->drawRect(rec);

}


/**
 * @brief Vehicle::mousePressEvent catch event when mouse was clicked
 * @param event event representation
 */
void Vehicle::mousePressEvent(__attribute__((unused)) QGraphicsSceneMouseEvent * event) {
    emit clearBusInfoSignal();
    emit paintInfoSignal(this);

    auto shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(4);
    shadow->setOffset(2);
    shadow->setColor(QColor(62, 62, 62));
    this->setGraphicsEffect(shadow);

    for (Street * street: myLine->getLineStreets()) {
        int * coord = street->getCoordinates();

        int x1 = coord[0];
        int y1 = coord[1];
        int x2 = coord[2];
        int y2 = coord[3];

        emit paintRoadSignal(x1, y1, x2, y2, myLine->getLineName());
    }

    qreal distance = 0;
    QString departure = schedule.at(0).toString("hh:mm");
    QString departureLastStop = schedule.at(0).addSecs(3600).toString("hh:mm");

    emit createLabelSignal(myStops.front()->getName(), departure, 0, this);
    emit createLabelSignal(myStops.front()->getName(), departureLastStop, 1, this);

    int size = 0;
    for (Stop * stop: myStops) {
        // First stop is already printed
        if (size == 0) {
            size++;
            continue;
        }

        distance = myLine->distanceBetweenStops(myStops.at(0), myStops.at(size)) / myLine->getLineLen();

        departure = schedule.at(size).toString("hh:mm");
        emit createLabelSignal(stop->getName(), departure, distance, this);
        size++;
    }
}
