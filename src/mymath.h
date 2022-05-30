/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */

#ifndef MYMATH_H
#define MYMATH_H

//! Class used for calculating distance between two points
class MyMath
{
public:
    MyMath();
    double distance(double, double, double, double);
    bool isPointOnLine(double, double, double, double, double, double);
};

#endif // MYMATH_H
