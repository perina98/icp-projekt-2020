/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#include "street.h"


/**
 * @brief Street::Street Street object constructor
 * @param id ID of street
 * @param name Street name
 * @param x1 Starting x-position
 * @param y1 Starting y-position
 * @param x2 Ending x-position
 * @param y2 Ending y-position
 */
Street::Street(QString id, QString name, int x1, int y1, int x2, int y2): QGraphicsLineItem(x1, y1, x2, y2) {

    setPen(QPen(Qt::black, 2));
    this->id = id;
    this->name = name;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->hasStop = false;
    this->speedLimit = 1;
    this->speedString = "Normal";
}


/**
 * @brief Street::Street street object copy constructor
 * @param street Street which is being copied
 */
Street::Street(const Street & street): QGraphicsLineItem(street.x1, street.y1, street.x2, street.y2) {
    setPen(QPen(Qt::black, 2));
    id = street.id;
    name = street.name;
    x1 = street.x1;
    y1 = street.y1;
    x2 = street.x2;
    y2 = street.y2;
    hasStop = street.hasStop;
    speedLimit = street.speedLimit;
    speedString = street.speedString;
    replaced = street.replaced;
}


/**
 * @brief Street::getStreetName Get name of a given street
 * @return Name of the street
 */
QString Street::getStreetName() {
    return this->name;
}


/**
 * @brief Street::getStreetID Get ID of a given street
 * @return ID of the street
 */
QString Street::getStreetID() {
    return this->id;
}


/**
 * @brief Street::getCoordinates Gets coordinates of given street
 * @return Coordinates of the street in int array
 */
int * Street::getCoordinates() {
    int * coord = new int[4];

    coord[0] = this->x1;
    coord[1] = this->y1;
    coord[2] = this->x2;
    coord[3] = this->y2;

    return coord;
}


/**
 * @brief Street::checkEnds Checks if streets is connected from the both sides
 * @param streets Vector containng all the streets
 * @return true or false
 */
bool Street::checkEnds(std::vector < Street * > streets) {
    // Coordinates of this street
    int * t = this->getCoordinates();

    bool beg, end = false;

    for (Street * street: streets) {
        // Skip this street
        if (street->getStreetID() == this->getStreetID()) {
            continue;
        }

        // Coordinates of the current street from the vector
        int * s = street->getCoordinates();

        if ((s[0] == t[0] && s[1] == t[1]) || (s[0] == t[2] && s[1] == t[3])) {
            beg = true;
        }

        if ((s[2] == t[0] && s[3] == t[1]) || (s[2] == t[2] && s[3] == t[3])) {
            end = true;
        }
    }

    if (beg && end) {
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Street::getStreetLen Calculates length of the street
 * @return Length of the street
 */
double Street::getStreetLen() {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


/**
 * @brief Street::isOnStreet Checks whether point with given coordinates lies on the street
 * @param pX X-coordinate of point
 * @param pY Y-coordinates of the point
 * @return True if coords are on streets, false when they are not
 */
bool Street::isOnStreet(double pX, double pY) {
    double roadLen = this->getStreetLen();
    double distance1 = math.distance(pX, pY, x1, y1);
    double distance2 = math.distance(pX, pY, x2, y2);

    if (fabs(distance1 + distance2 - roadLen) < 0.1) {
        return true;
    }

    return false;
}


/**
 * @brief Street::setSpeedLimit Sets speed limitation on the street
 */
void Street::setSpeedLimit(double limit) {
    this->speedLimit = limit;
}


/**
 * @brief Street::swapEnds Swaps start and end coordinates of the street
 */
void Street::swapEnds() {
    int tmp;
    tmp = x1;
    this->x1 = x2;
    this->x2 = tmp;
    tmp = y1;
    this->y1 = y2;
    this->y2 = tmp;
}

/**
 * @brief Street::getSpeedLimit Returns speed limitation (if defined) on the street (number between 0-1)
 * @return Speed limitation
 */
double Street::getSpeedLimit() {
    return this->speedLimit;
}


/************************ UI **********************/


/**
 * @brief Street::mousePressEvent catch mouse press on street and emit signal to mainwindow
 * @param event event
 */
void Street::mousePressEvent(__attribute__((unused)) QGraphicsSceneMouseEvent * event) {
    qDebug() << "street pressed" << this->getStreetID() << this->hasStop;
    emit enableComboSignal(this);
}


/**
 * @brief Street::receiveNewSpeed receive new speed limitation
 * @param newspeed New speed limitation
 */
void Street::receiveNewSpeed(QString newspeed) {
    this->speedString = newspeed;

    if (newspeed == "Normal") {
        this->speedLimit = 1;
        setPen(QPen({QColor(0, 0, 0)}, 2));
    } else if (newspeed == "Slow") {
        this->speedLimit = 0.75;
        setPen(QPen({QColor(138, 69, 74)}, 2));
    } else if (newspeed == "Slower") {
        this->speedLimit = 0.5;
        setPen(QPen({QColor(242, 104, 115)}, 2));
    } else if (newspeed == "Slowest") {
        this->speedLimit = 0.25;
        setPen(QPen({QColor(245, 22, 39)}, 2));
    } else if (newspeed == "Closed") {
        this->speedLimit = 0;
        setPen(QPen({QColor(174, 174, 174)}, 2, Qt::DashDotLine));
        emit ptrClosedStreet(this);
    }

    emit speedChange(this, speedLimit);
}
