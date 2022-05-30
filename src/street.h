/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#ifndef STREET_H
#define STREET_H

#include "mymath.h"

#include <QString>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>

#include <math.h>

//! Class representing street
class Street : public QObject , public QGraphicsLineItem
{
    Q_OBJECT

public:
    Street(QString id, QString name, int x1, int y1, int x2, int y2);
    Street(const Street&);

    QString getStreetName();
    QString getStreetID();
    QVector<Street*> replaced;
    int *getCoordinates();
    double getStreetLen();
    double getSpeedLimit();
    void swapEnds();
    void setSpeedLimit(double);
    bool isOnStreet(double, double);
    bool checkEnds(std::vector<Street*> streets);
    bool hasStop;

private:
    MyMath math;
    QString id, name, speedString;
    double speedLimit;
    int x1, y1, x2, y2;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void receiveNewSpeed(QString);

signals:
   void enableComboSignal(Street*);
   void ptrClosedStreet(Street*);
   void speedChange(Street*, double);
};

#endif // STREET_H
