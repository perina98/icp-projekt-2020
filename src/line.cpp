/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */
#include "line.h"

/**
 * @brief Line::Line Constructor of bus line
 * @param name Name of bus line, e.g. Red
 * @param stops Vector of QString objects of bus stops
 * @param streets Vector of QString objects of streets of bus line
 * @param times Vector of times of base departure from the stop
 * @param busNo Number of buses that are operating on this line
 */
Line::Line(QString name, std::vector<QString> stops, std::vector<QString> streets, std::vector<int> times, int busNo)
{
    this->name = name;
    this->stopStrs = stops;
    this->streetStrs = streets;
    this->times = times;
    this->timesBackup = times;
    this->busNo = busNo;
    this->busesOnRoad = 0;
}

/**
 * @brief Line::Line Copy constructor of the bus line
 * @param line line which is being copied
 */
Line::Line(const Line &line)
{
    name = line.name;
    stopObjs = line.stopObjs;
    times = line.times;
    busNo = line.busNo;

    for (Street *street : line.streetObjs)
    {
        Street *streetCopy = new Street(*street);
        streetObjs.push_back(streetCopy);
    }
}


/**
 * @brief Line::loadStreets Converts QString objects of streets to Street objects
 * @param streetsOnMap All the streets on the map
 * @return True on success, false if any of the streets is not valid
 */
bool Line::loadStreets(std::vector<Street*> streetsOnMap)
{
    for (QString streetStr : streetStrs)
    {
        for (Street *streetObj : streetsOnMap)
        {
            if (streetStr == streetObj->getStreetID())
            {
                // Push copy of the street to vector
                // Needed because of different ends/beginnings of the streets
                Street *newStr = new Street(*streetObj);
                this->streetObjs.push_back(newStr);

                // For defining speed limitations on the streets
                connect(streetObj, SIGNAL(speedChange(Street*,double)), this, SLOT(streetSpeedChange(Street*,double)));
            }
        }
    }

    int *firstStr = streetObjs.at(0)->getCoordinates();
    int *secondStr = streetObjs.at(1)->getCoordinates();

    // First street is rotated the wrong way
    if ((firstStr[2] != secondStr[2] || firstStr[3] != secondStr[3]) && (firstStr[2] != secondStr[0] || firstStr[3] != secondStr[1]))
    {
        streetObjs.at(0)->swapEnds();
    }

    // Check if end of one street is begginning of another, if not, swap coordinates of the next street
    for (int i = 0; i < static_cast<int>(streetObjs.size()) - 1; i++)
    {
        int *currStreet = streetObjs.at(i)->getCoordinates();
        int *nextStreet = streetObjs.at(i+1)->getCoordinates();

        if (currStreet[2] != nextStreet[0] || currStreet[3] != nextStreet[1])
        {
                streetObjs.at(i+1)->swapEnds();
        }
    }


    for (Street *street : streetObjs)
    {
        streetBackup.push_back(street);
    }

    if (streetObjs.size() != streetStrs.size())
    {
        return false;
    }
    else
    {
        return true;
    }
}


/**
 * @brief Line::loadStops Converts QString objects of stops to Stop objects
 * @param stopsOnMap All the stops on the map
 * @return true on success, false if any of the stops is not valid
 */
bool Line::loadStops(std::vector<Stop*> stopsOnMap)
{
    for (QString stopStr : stopStrs)
    {
        for (Stop *stopObj : stopsOnMap)
        {
            if (stopStr == stopObj->getName())
            {
                // Stop does not belong to street, error
                if (!stopObj->onStreet(streetObjs))
                {
                    return false;
                }

                this->stopObjs.push_back(stopObj);
            }
        }
    }

    for (Stop *stop : stopObjs)
    {
        stopBackup.push_back(stop);
    }

    if (stopObjs.size() != stopStrs.size())
    {
        return false;
    }
    else
    {
        return true;
    }
}


/**
 * @brief Line::getLineName Returns name of actual line
 */
QString Line::getLineName()
{
    return this->name;
}


/**
 * @brief Line::getLineStreets Returns vector of Street object copies of the bus line
 * @return Vector of Street object copies of the line
 */
std::vector<Street*> Line::getLineStreets()
{
    return this->streetObjs;
}


/**
 * @brief Line::getLineTimes Returns departure times from the each stop of the line
 * @return Departure times from the each stop of the line
 */
std::vector<int> Line::getLineTimes()
{
    return this->times;
}


/**
 * @brief Line::getLineStops Returns all the stops of the bus line
 * @return All the stops of the bus line
 */
std::vector<Stop*> Line::getLineStops()
{
    return this->stopObjs;
}


/**
 * @brief Line::getBusNo Returns number of buses operating on the line
 * @return Number of buses operating on the line
 */
int Line::getBusNo()
{
    return this->busNo;
}


/**
 * @brief Line::getLineLen Calculates bus line legth
 * @return Bus line length
 */
double Line::getLineLen()
{
    double len = 0.0;
    for (Street *streetObj : streetObjs)
    {
        len += streetObj->getStreetLen();
    }

    return len;
}


/**
 * @brief Line::getSpeedBetweenStops Returns the speed of the vehicle between stops, so that it  rides accordingly to schedule
 * @param first First stop
 * @param second Second stop
 * @param minutes How long does the road take
 * @return Length of one step the vehicle should make each second
 */
double Line::getSpeedBetweenStops(Stop *first, Stop *second, double minutes)
{
    return distanceBetweenStops(first, second)/(minutes * 60);
}


/**
 * @brief Line::distanceBetweenStops Calculates distance between 2 given stops on the line
 * @param first First stop of the line
 * @param second Second stop
 * @return Distance between first and second stop passed as argument
 */
double Line::distanceBetweenStops(Stop *first, Stop *second)
{
    double subtractor = 0.0;
    double lenBeweenStops = 0.0;
    bool between = false;


    // Len betewwn and stop and the first one
    if (first->getID() == stopObjs.back()->getID() && second->getID() == stopObjs.front()->getID())
    {
        std::swap(first, second);
        subtractor = this->getLineLen();
    }

    for (unsigned int i = streetObjs.size() - 1; i >= 0; i--)
    {
        Street *currStreet = streetObjs.at(i);

        if (currStreet->getStreetID() == second->getID())
        {
            between = true;
            double *stopCoords = second->getCoordinates();
            int *streetCoords = currStreet->getCoordinates();
            lenBeweenStops += math.distance(stopCoords[0] , stopCoords[1], streetCoords[0], streetCoords[1]);
            continue;
        }

        if (between)
        {
            if (currStreet->getStreetID() == first->getID())
            {
                between = false;
                double *stopCoords = first->getCoordinates();
                int *streetCoords = currStreet->getCoordinates();
                lenBeweenStops += math.distance(stopCoords[0] , stopCoords[1], streetCoords[2], streetCoords[3]);
                break;
             }
             else
             {
                 lenBeweenStops += currStreet->getStreetLen();
             }
        }
    }

    return abs(subtractor - lenBeweenStops);
}


/**
 * @brief Line::distanceFromStart Calculates the distance of a point with coordinates x and y from the first bus stop
 * @param street Current where vehicle is driving
 * @param x X-position of a point
 * @param y Y-position of a point
 * @return Distance from the beginning of a street
 */
double Line::distanceFromStart(double x, double y)
{
    double distance = 0.0;
    double *stopCoords = stopObjs.at(0)->getCoordinates();
    int *streetCoords = streetObjs.at(0)->getCoordinates();
    bool subtractOffset = false;
    double initOffset = math.distance(streetCoords[0], streetCoords[1], stopCoords[0], stopCoords[1]);

    for (Street *street : streetObjs)
    {
        // Point is on current street
        if (street->isOnStreet(x, y))
        {
            int *strCoords = street->getCoordinates();

            // Current street is the first street of a line
            if (street->getStreetID() == streetObjs.at(0)->getStreetID())
            {

                // Point is at the beginning of a line
                if (math.isPointOnLine(stopCoords[0], stopCoords[1], strCoords[2], strCoords[3], x, y))
                {
                    distance += math.distance(x, y, stopCoords[0], stopCoords[1]);
                    break;
                }
                // Point is at the end of a line
                else
                {
                    distance += this->getLineLen() - math.distance(stopCoords[0], stopCoords[1], x, y);
                    break;
                }
            }
            else
            {
               distance += math.distance(x, y, strCoords[0], strCoords[1]);
               break;
            }
        }
        // Point is on the street further away
        else
        {
            subtractOffset = true;
            distance += street->getStreetLen();
        }

    }

    if (subtractOffset)
        return distance - initOffset;
    else
        return distance;
}



/**
 * @brief Line::closedRoadCheck Checks if road can be closed and returns success message
 * @param lastClosed Points to last closed road
 * @param pressedStreets Array of pressed streets used for configuring deroute
 * @return QString containing info about success or failure
 */
QString Line::closedRoadCheck(Street *lastClosed, std::vector<Street*> pressedStreets)
{

    if (pressedStreets.size() == 0)
    {
        return "No deroute streets were selected";
    }

    if (lastClosed->getStreetID() == streetObjs.front()->getStreetID())
    {
        return "First line street cannot be closed";
    }

    // Check if closed street is in the line, if not, finish
    for (Street *street : streetObjs)
    {
        // Closed street belongs to the line
        if (lastClosed->getStreetID() == street->getStreetID())
        {
            break;
        }

        // Closed street does not belong to the line
        if (street == streetObjs.back())
        {
            return "Success";
        }
    }

    // Street after the closed one
    Street *front = nullptr;
    // Street behind the closed one
    Street *back = nullptr;
    // Get coordinates of the street before closed one
    for (int i = 0; i < static_cast<int>(streetObjs.size()); i++)
    {
        if (streetObjs.at(i)->getStreetID() == lastClosed->getStreetID())
        {
            if (i == 0)
            {
                front = streetObjs.back();
                back = streetObjs.at(i + 1);
                break;
            }
            else if (i == static_cast<int>(streetObjs.size()) - 1)
            {
                front = streetObjs.at(i - 1);
                back = streetObjs.front();
                break;
            }
            else
            {
                front = streetObjs.at(i - 1);
                back = streetObjs.at(i + 1);
                break;
            }
        }
    }

    std::vector<Street*> ordered;
    int *lastCoords = front->getCoordinates();

    // Sort vector of detour streets by coordinates
    int j = 0;
    while (j < static_cast<int>(pressedStreets.size()))
    {
        int *currCoords = pressedStreets.at(j)->getCoordinates();

        if (lastCoords[2] == currCoords[0] && lastCoords[3] == currCoords[1])
        {
            // Make a copy of a street ptr
            Street *newStr = new Street(*pressedStreets.at(j));
            connect(pressedStreets.at(j), SIGNAL(speedChange(Street*,double)), this, SLOT(streetSpeedChange(Street*,double)));

            ordered.push_back(newStr);
            lastCoords = ordered.back()->getCoordinates();
            pressedStreets.erase(pressedStreets.begin() + j);
            j = 0;

            continue;
        }
        else if (lastCoords[2] == currCoords[2] && lastCoords[3] == currCoords[3])
        {
            // Make a copy of a street ptr
            Street *newStr = new Street(*pressedStreets.at(j));
            connect(pressedStreets.at(j), SIGNAL(speedChange(Street*,double)), this, SLOT(streetSpeedChange(Street*,double)));

            ordered.push_back(newStr);
            ordered.back()->swapEnds();
            lastCoords = ordered.back()->getCoordinates();
            pressedStreets.erase(pressedStreets.begin() + j);
            j = 0;

            continue;
        }

        j++;
    }

    // Redundant streets were selected
    if (pressedStreets.size() != 0)
    {
        return "Selected streets of deroute do not connect with line";
    }

    // Selected streets do not connect to the line
    int *frontDeroute = ordered.back()->getCoordinates();
    int *backtRoute = back->getCoordinates();
    if (frontDeroute[2] != backtRoute[0] || frontDeroute[3] != backtRoute[1])
    {
        return "Deroute route does not connect to line route";
    }

    // Save deroute streets
    this->derouteObjs = ordered;

    return "Success";
}


/**
 * @brief Line::closeRoad Function to close selected road
 * @param closed Road selected for closing
 */
void Line::closeRoad(Street *closed)
{
    if (derouteObjs.size() == 0)
    {
        return;
    }


    // Remove stops from the closed street from the route
    for (int i = 0; i < static_cast<int>(stopObjs.size()); i++)
    {
        if (stopObjs.at(i)->getID() == closed->getStreetID())
        {
            stopObjs.erase(stopObjs.begin() + i);
            times.erase(times.begin() + i);
        }
    }


    // Add deroute streets to vector defining route of the line
    for (int i = 0; i < static_cast<int>(streetObjs.size()); i++)
    {
        if (streetObjs.at(i)->getStreetID() == closed->getStreetID())
        {
            streetObjs.erase(streetObjs.begin() + i);

            int j = 0;
            for (Street *street : derouteObjs)
            {
                // Set speed limit => bus moves slower
                street->setSpeedLimit(0.5);
                // Save which street is being replaced by the detour streets
                street->replaced.append(closed);
                streetObjs.insert(streetObjs.begin() + i + j, street);
                j++;
            }
        }
    }


    for (int i = 0; i < static_cast<int>(streetObjs.size()) - 1; i++)
    {
        int *currStreet = streetObjs.at(i)->getCoordinates();
        int *nextStreet = streetObjs.at(i+1)->getCoordinates();

        if (currStreet[2] != nextStreet[0] || currStreet[3] != nextStreet[1])
        {
                streetObjs.at(i+1)->swapEnds();
        }
    }


    // Check if there are any dead-end streets
    // Bus would go to the dead-end street, returned and then continued as it should - useless
    for (int i = 0; i < static_cast<int>(streetObjs.size()) - 1; i++)
    {
        QString currID = streetObjs.at(i)->getStreetID();
        QString nextID = streetObjs.at(i+1)->getStreetID();

        // There is dead end
        if (currID == nextID)
        {
            // There is a stop on the dead end, cannot cut it
            if (streetObjs.at(i)->hasStop)
            {
                continue;
            }

            // There is no stop, cut it
            streetObjs.erase(streetObjs.begin() + i);
            streetObjs.erase(streetObjs.begin() + i);
        }


        // Street has a dead-end and does not have a stop
        if (!streetObjs.at(i)->checkEnds(streetObjs))
        {
            // Has a stop, do not cut it
            if (streetObjs.at(i)->hasStop)
            {
                continue;
            }

            // No stop, cut it
            streetObjs.erase(streetObjs.begin() + i);
        }
    }
}


/**
 * @brief Line::streetSpeedChange change speed limit of speed
 * @param streetChanged Street whose value was changed
 * @param value New value for speedlimit
 */
void Line::streetSpeedChange(Street *streetChanged, double value)
{
    for (Street *street : streetObjs)
    {
        if (street->getStreetID() == streetChanged->getStreetID())
        {
            street->setSpeedLimit(value);
        }
    }
}


/**
 * @brief Line::resetLine reset line to default state
 */
void Line::resetLine()
{
    streetObjs.clear();
    for (Street *street : streetBackup)
    {
        streetObjs.push_back(street);
    }

    stopObjs.clear();
    for (Stop *stop : stopBackup)
    {
        stopObjs.push_back(stop);
    }

    times.clear();
    times = timesBackup;

    this->busesOnRoad = 0;
}
