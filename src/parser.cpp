/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#include "parser.h"

/**
 * @brief parser::parser Empty constructor
 */
Parser::Parser() {

}

/**
 * @brief Function that parses CSV representation of map
 *
 * Each line of file represents either whole road or more partsof the same road.
 * CSV is represented in format:
 * road_id, road_name, x1, y1, x2, y2, max_speed_on_road
 *
 * @param fileName Name of CSV file with roads
 * @return map Map representation of roads
 *
 */
std::vector < Street * > Parser::parseRoads(QString fileName) {
    // Representation of street
    Street * street;

    // All streets are stored in vector
    std::vector < Street * > streets;

    // Open CSV file with roads
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return streets;

    // Street attributes
    QString street_id, street_name;
    int x1, y1, x2, y2;

    // Parse and store CSV file
    QTextStream in ( & file);
    QString line = in .readLine();
    while (!line.isNull()) {
        line = in .readLine();
        QStringList row = line.split(',');

        if (row[0] == "") {
            break;
        }

        street_id = row[0];
        street_name = row[1];
        x1 = row[2].toInt();
        y1 = row[3].toInt();
        x2 = row[4].toInt();
        y2 = row[5].toInt();

        street = new Street(street_id, street_name, x1, y1, x2, y2);
        streets.push_back(street);
    }

    return streets;
}

/**
 * @brief Function that parses CSV representation of stops
 *
 * Each line of file represents one stop
 * CSV is represented in format:
 * stop_name, x, y
 *
 * @param fileName Name of CSV file with stops
 * @return map Map representation of stops
 *
 */
std::vector < Stop * > Parser::parseStops(QString fileName) {
    // Representation of stop
    Stop * stop;

    // All stops are stored in vector
    std::vector < Stop * > stops;

    // Open CSV file with stops
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return stops;

    // Street attributes
    QString name, streetID;
    int x, y;

    // Parse and store CSV file
    QTextStream in ( & file);
    QString line = in .readLine();
    while (!line.isNull()) {
        line = in .readLine();
        QStringList row = line.split(',');

        if (row[0] == "") {
            break;
        }

        streetID = row[0];
        name = row[1];
        x = row[2].toInt();
        y = row[3].toInt();

        stop = new Stop(streetID, name, x, y);
        stops.push_back(stop);
    }

    return stops;
}

/**
 * @brief Function that parses CSV representation of bus lines
 *
 * Each line of file represents one bus line
 * CSV is represented in format:
 * line_name,line_stops,line_streets,stop_times
 *
 * @param fileName Name of CSV file with stops
 * @return map Map representation of stops
 *
 */
std::vector < Line * > Parser::parseLines(QString fileName) {
    // Representation of bus line
    Line * busLine;

    // All lines are stored in vector
    std::vector < Line * > lines;

    // Open CSV file with stops
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return lines;

    // Parse and store CSV file
    QTextStream in ( & file);
    QString line = in .readLine();
    while (!line.isNull()) {
        // Bus line attributes
        QString lineName;
        std::vector < QString > stops;
        std::vector < QString > streets;
        std::vector < int > times;
        int busNo;

        line = in .readLine();
        QStringList row = line.split(',');

        if (row[0] == "") {
            break;
        }

        // Name of line
        lineName = row[0];

        // All the stops of the line
        QStringList qStopList = row[1].split("-");
        for (QString stop: qStopList) {
            stops.push_back(stop);
        }

        // All the roads of the line
        QStringList qStreetList = row[2].split("-");
        for (QString street: qStreetList) {
            streets.push_back(street);
        }

        // Times of the base bus of the line
        QStringList qTimesList = row[3].split("-");
        for (QString time: qTimesList) {
            times.push_back(time.toInt());
        }

        // Number of buses of the line
        busNo = row[4].toInt();

        busLine = new Line(lineName, stops, streets, times, busNo);
        lines.push_back(busLine);
    }

    return lines;
}
