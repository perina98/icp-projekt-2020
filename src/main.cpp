/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#include "mainwindow.h"
#include "street.h"
#include "stop.h"
#include "line.h"
#include "vehicle.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <QApplication>
#include <QDebug>


/**
 * @brief printError Prints massage to stderr and exits program with retVal
 * @param message Message to be printed
 * @param retVal Return code of the program
 */
void printError(std::string message, int retVal) {
    std::cerr << "ERROR: " << message << "\n";
    exit(retVal);
}

/**
 * @brief main main function where everything begins and ends
 * @param argc not used
 * @param argv not used
 * @return QApplication
 */
int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    // CSV file parser
    Parser parse;

    // File with csv representation of map
    // ifdef needed because of differences in build folder structure on MacOS and other OS-es
    #if defined (Q_OS_MACOS)
        QString roadsCSV = "../../../../examples/roads.csv";
        QString stopsCSV = "../../../../examples/stops.csv";
        QString linesCSV = "../../../../examples/lines.csv";
    #else
        QString roadsCSV = "../examples/roads.csv";
        QString stopsCSV = "../examples/stops.csv";
        QString linesCSV = "../examples/lines.csv";
    #endif

    // All streets are stored in map structure
    std::vector < Street * > streets;
    std::vector < Stop * > stops;
    std::vector < Line * > lines;

    streets = parse.parseRoads(roadsCSV);
    stops = parse.parseStops(stopsCSV);
    lines = parse.parseLines(linesCSV);

    if (streets.size() == 0 || stops.size() == 0 || lines.size() == 0) {
        printError("Could not parse CSV", 1);
    }

    // Check if all the streets are connected, i.e. whether there are no dead-end streets
    for (Street * street: streets) {
        if (!street->checkEnds(streets)) {
            printError("CSV file containts at least one dead-end street", 1);
        }
    }

    // Check validity of bus line
    for (Line * line: lines) {
        // QString streets to Street objects
        if (!line->loadStreets(streets)) {
            printError("Street ID in line CSV not valid", 1);
        }

        // QString stops to Stop objects
        if (!line->loadStops(stops)) {
            printError("Stop ID in line CSV not valid", 1);
        }

        // Number of bus stops must be the same as the time schedule in the CSV
        if (line->getLineStops().size() != line->getLineTimes().size()) {
            printError("Number of departure times should be same as number of stops", 1);
        }
    }

    // Create map with streets and bus stops
    QGraphicsScene * scene = w.initScene(streets, stops);

    if (scene == nullptr) {
        printError("Could not init scene", 1);
    }

    w.initPublicTransport(lines);
    w.show();

    return a.exec();
}
