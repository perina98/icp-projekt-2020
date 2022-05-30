/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */
#include "mymath.h"
#include "math.h"

MyMath::MyMath()
{

}

/**
 * @brief MyMath::distance Calculates distance between two points
 * @param x1 X-coordinate of the first point
 * @param y1 Y-coordinate of the first point
 * @param x2 X-coordinate of the second point
 * @param y2 Y-coordinate of the second point
 * @return Calculated distance
 */
double MyMath::distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


/**
 * @brief MyMath::isPointOnLine checks if point is on line
 * @param x1 X-coordinate of starting point of line
 * @param y1 Y-coordinate of starting point of line
 * @param x2 X-coordinate of ending point of line
 * @param y2 Y-coordinate of ending point of line
 * @param pX X-coordinate of the point
 * @param pY Y-coordinate of the point
 * @return True if point is on line, false if isnt
 */
bool MyMath::isPointOnLine(double x1, double y1, double x2, double y2, double pX, double pY)
{
    double lineLen = distance(x1, y1, x2, y2);
    double distance1 = distance(pX, pY, x1, y1);
    double distance2 = distance(pX, pY, x2, y2);

    if (fabs(distance1 + distance2 - lineLen) < 0.1)
    {
        return true;
    }

    return false;
}
