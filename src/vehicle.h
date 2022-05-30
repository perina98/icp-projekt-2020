/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */


#ifndef VEHICLE_H
#define VEHICLE_H

#include "mymath.h"
#include "line.h"
#include "street.h"
#include "stop.h"


#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QList>
#include <QLabel>
#include <QTime>

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QList>
#include <QLabel>

#include <math.h>

//! Class representing vehicle - bus
class Vehicle : public QObject , public QGraphicsItem
{
public:
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

signals:
    void paintInfoSignal(Vehicle*);
    void paintRoadSignal(const int&, const int&, const int&, const int&,const QString& lineName);
    void createLabelSignal(const QString&, const QString&, const qreal&, Vehicle*);
    void clearBusInfoSignal();

public:
    Vehicle(QGraphicsScene*, Line*, QTime, int);

    QString lineName;
    int busNo;
    void updatePosition(QTime);
    double positionOnLine();
    double delay;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

private:
    Line *myLine;
    QTime myTime;
    Stop *nextStop;
    Street *currStreet;
    QGraphicsItem *square;
    MyMath math;

    int waitOnStop;
    int streetCnt;
    int stopCnt;
    int *roadCoords;
    int prevStreetsSize;
    double speedLimit;
    double x, y;
    double *calculateDelta(int*, double);
    bool isPointOnLine(double, double);
    bool onStop(double, double);
    void transformSchedule();
    void checkDeroute();

    std::vector<QTime> scheduleRewind(int minutes);
    std::vector<int> myTimes;
    std::vector<QTime> schedule;
    std::vector<Street*> myStreets;
    std::vector<Stop*> myStops;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // VEHICLE_H
