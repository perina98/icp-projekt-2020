/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */

#ifndef STOPS_H
#define STOPS_H

#include "street.h"

#include <math.h>

#include <iostream>
#include <QString>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>

//! Class representig bus stop
class Stop  : public QGraphicsItem
{
    Street *street;

    QString name, streetID;
    double x, y;

public:
    Stop(QString streetID, QString name, int x, int y);
    Street* getStreet();

    QString getID();
    QString getName();
    double *getCoordinates();
    void loadStreet(Street *street);
    bool onStreet(std::vector<Street*>);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // STOPS_H
