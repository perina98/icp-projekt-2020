/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */

#include "stop.h"

/**
 * @brief Stop::Stop bus stop constructor
 * @param name Name of the bus stop
 * @param x X-coordinate of bus stop on map
 * @param y Y-coordinateof bus stop on map
 */
Stop::Stop(QString streetID, QString name, int x, int y) {
    this->streetID = streetID;
    this->name = name;
    this->x = x;
    this->y = y;
}


/**
 * @brief Stop::getCoordinates Gets coordinates of given bus stop
 * @return Cordinates in int array
 */
double * Stop::getCoordinates() {
    double * coord = new double[2];

    coord[0] = this->x;
    coord[1] = this->y;

    return coord;
}


/**
 * @brief Stop::getID Returns street ID where the stop lies
 * @return ID of the street
 */
QString Stop::getID() {
    return this->streetID;
}


/**
 * @brief Stop::getID Returns street ID where the stop lies
 * @return ID of the street
 */
QString Stop::getName() {
    return this->name;
}


/**
 * @brief Street::getStreet Used for returning actual street representation
 * @return Street representation
 */
Street * Stop::getStreet() {
    return this->street;
}


/**
 * @brief Stop::onStreet Checks whether the stop actually lies on the street
 * @param streets Vector of all the streets on the map
 * @return true or false
 */
bool Stop::onStreet(std::vector < Street * > streets) {
    double x = this->getCoordinates()[0];
    double y = this->getCoordinates()[1];

    // Iterate through streets
    for (Street * street: streets) {
        if (street->getStreetID() == this->getID()) {
            int * coord = street->getCoordinates();

            int x1 = coord[0];
            int y1 = coord[1];
            int x2 = coord[2];
            int y2 = coord[3];

            float streetLen = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
            float dist1 = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
            float dist2 = sqrt(pow(x - x2, 2) + pow(y - y2, 2));

            // Stop lies on the street or in 2px radius from the street
            if ((dist1 + dist2) - streetLen < 2) {
                // Set it exactly on the street
                double k = ((y2 - y1) * (x - x1) - (x2 - x1) * (y - y1)) / ((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
                this->x = x - k * (y2 - y1);
                this->y = y + k * (x2 - x1);

                this->loadStreet(street);

                street->hasStop = true;

                return true;
            }
        }
    }

    // Stop does not lie on the street
    return false;
}


/**
 * @brief Stop::loadStreet set street as actual street
 * @param street street representation
 */
void Stop::loadStreet(Street * street) {
    this->street = street;
}

/************************ UI **********************/


/**
 * @brief Stop::boundingRect Set bounding rectangle of stop object
 * @return QRectF bounding object
 */
QRectF Stop::boundingRect() const {
    return QRectF(0, 0, 5, 5);
}


/**
 * @brief Stop::paint paint ellipse representing stops
 * @param painter Painter object
 * @param option options
 * @param widget widget
 */
void Stop::paint(QPainter * painter, __attribute__((unused)) const QStyleOptionGraphicsItem * option, __attribute__((unused)) QWidget * widget) {
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);
    painter->setPen(QPen({Qt::black}, 5));
    painter->drawEllipse(rec);
}


/**
 * @brief Stop::mousePressEvent catch event when mouse was clicked
 * @param event event representation
 */
void Stop::mousePressEvent(__attribute__((unused)) QGraphicsSceneMouseEvent * event) {
    qDebug() << "stop pressed";
}
