/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#ifndef LINE_H
#define LINE_H

#include "stop.h"
#include "mymath.h"
#include "street.h"

#include <algorithm>

//! Class representig public transport line
class Line: public QObject
{
    Q_OBJECT

public:

    Line(QString, std::vector<QString>, std::vector<QString>, std::vector<int>, int);
    Line(const Line&);
    bool loadStreets(std::vector<Street*>);
    bool loadStops(std::vector<Stop*>);
    QString closedRoadCheck(Street*, std::vector<Street*>);
    void closeRoad(Street*);
    void resetLine();

    std::vector<Street*> getLineStreets();
    std::vector<Stop*> getLineStops();
    std::vector<int> getLineTimes();
    QString getLineName();
    int getBusNo();

    double getLineLen();
    double distanceFromStart(double, double);
    double getSpeedBetweenStops(Stop*, Stop*, double );
    double distanceBetweenStops(Stop*, Stop*);

    int busesOnRoad;

private:
    QString name;
    std::vector<Street*> streetObjs;
    std::vector<Street*> streetBackup;
    std::vector<Stop*> stopObjs;
    std::vector<Stop*> stopBackup;
    std::vector<int> times;
    std::vector<int> timesBackup;
    std::vector<Street*> derouteObjs;

    int busNo;
    std::vector<QString> streetStrs;
    std::vector<QString> stopStrs;

    MyMath math;

public slots:
    void streetSpeedChange(Street*, double);

};

#endif // LINE_H
