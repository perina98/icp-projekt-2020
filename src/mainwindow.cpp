/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QVariantAnimation>
#include <QGraphicsProxyWidget>
#include <QDateTime>
#include <QTimeEdit>

/**
 * @brief MainWindow::MainWindow man window constructor
 */
MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("ICP");

    // Zoom slider
    connect(ui->ZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

    // Reset button
    connect(ui->resetTimer, SIGNAL(released()), this, SLOT(resetTimeLabel()));

    // Init timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getTime()));
    QTime time = QTime(05, 0, 0);
    QString time_str = time.toString("hh : mm : ss");

    ui->timeLabel->setText(time_str);
    timer->start(1000 * speedMultiplier);

    // Connect timer to button so time can be speeded up/down
    connect(ui->timeTravelBox, SIGNAL(valueChanged(double)), this, SLOT(setSpeed(double)));

    // Drop-down menu for street speed
    QStringList commands = {
        "Normal",
        "Slow",
        "Slower",
        "Slowest"
    };

    combo = ui->comboBox;
    combo->addItems(commands);
    connect(combo, SIGNAL(activated(int)), this, SLOT(streetSpeedChanged(int)));

    // Cancel road button
    connect(ui->cancelRoad, SIGNAL(released()), this, SLOT(cancelRoad()));
    ui->closedLabel->setVisible(false);

    QGraphicsScene * scene = new QGraphicsScene(ui->graphicsView);
    QGraphicsScene * busScene = new QGraphicsScene(ui->graphicsView_2);

    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(busScene);
    myScene = scene;
    myBusScene = busScene;

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}


/**
 * @brief MainWindow::~MainWindow main window destructor
 */
MainWindow::~MainWindow() {
    delete ui;
}


/**
 * @brief Handler of zoom signal
 * @param z Integer carying value of zoom scale
 */
void MainWindow::zoom(int z) {
    auto org = ui->graphicsView->transform();
    qreal scale = z / 5.0;
    ui->graphicsView->setTransform(QTransform(scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}


/**
 * @brief MainWindow::InitScene Initializes map scene, adds streets and bus stops to map
 * @param streets Vector containtng pairs of street_id and street object
 * @param stops Vector type conating pairs of stop_name and stop object
 * @return Pointer to the scene
 */
QGraphicsScene * MainWindow::initScene(std::vector < Street * > streets, std::vector < Stop * > stops) {
    myStreets = streets;
    myStops = stops;

    // Roads
    for (Street * street: streets) {
        drawnStreets.push_back(street);

        connect(street, SIGNAL(enableComboSignal(Street * )), this, SLOT(enableCombo(Street * )));
        connect(street, SIGNAL(ptrClosedStreet(Street * )), this, SLOT(ptrClosedStreet(Street * )));

        myScene->addItem(street);
    }

    // Stops
    for (Stop * stop: stops) {

        // Stop does not belong to street, error
        if (!stop->onStreet(streets)) {
            return nullptr;
        }

        QString name = stop->getName();
        QString streetID = stop->getID();

        double x1 = stop->getCoordinates()[0];
        double y1 = stop->getCoordinates()[1];

        auto myStop = new Stop(streetID, name, x1, y1);

        myStop->setPos(x1 - 3, y1 - 3);
        myScene->addItem(myStop);
    }

    return myScene;
}


/**
 * @brief MainWindow::getTime Display time in QLabel
 */
void MainWindow::getTime() {
    QTime time = QTime::fromString(ui->timeLabel->text(), "hh : mm : ss");
    time = time.addSecs(1);
    myTime = time;
    QString time_str = time.toString("hh : mm : ss");
    ui->timeLabel->setText(time_str);

    simulateTransport();
}


/**
 * @brief MainWindow::resetTimeLabel Reset time and scene to default values
 */
void MainWindow::resetTimeLabel() {
    QTime time = QTime(05, 0, 0);
    timer->stop();
    QString time_str = time.toString("hh : mm : ss");
    ui->timeLabel->setText(time_str);
    ui->timeTravelBox->setValue(1.00);

    for (Vehicle * item: allVehicles) {
        disconnect(item, nullptr, nullptr, nullptr);
        myScene->removeItem(item);
    }

    allVehicles.clear();

    ui->comboBox->setCurrentText(0);
    ui->cancelRoad->setText("Close Road");
    ui->comboBox->setDisabled(1);
    ui->cancelRoad->setDisabled(1);

    // Reset bus lines to their defaults
    for (Line * line: myLines) {
        line->resetLine();
    }

    // Reset street speeds
    for (Street * street: myStreets) {
        street->receiveNewSpeed("Normal");
    }

    clearBusInfo();

    this->initPublicTransport(myLines);
    timer->start();
}


/**
 * @brief MainWindow::setSpeed If value changed, stop timer and start it with new value
 * @param x speed multiplier
 */
void MainWindow::setSpeed(double x) {
    timer->stop();
    speedMultiplier = x;
    timer->start(1000 / speedMultiplier);
}


/**
 * @brief MainWindow::initPublicTransport initializes public transport
 * @param scene pointer to scene where public transport icons should be generated
 */
void MainWindow::initPublicTransport(std::vector < Line * > lines) {
    myLines = lines;

    for (Line * line: lines) {
        Vehicle * v = new Vehicle(myScene, line, QTime::fromString(ui->timeLabel->text(), "hh : mm : ss"), 1);
        allVehicles.push_back(v);
        line->busesOnRoad++;

        connect(v, SIGNAL(paintInfoSignal(Vehicle * )), this, SLOT(generateInfo(Vehicle * )));
        connect(v, SIGNAL(createLabelSignal(QString, QString, qreal, Vehicle * )), this, SLOT(generateLabel(QString, QString, qreal, Vehicle * )));
        connect(v, SIGNAL(paintRoadSignal(int, int, int, int, QString)), this, SLOT(paintRoad(int, int, int, int, QString)));
        connect(v, SIGNAL(clearBusInfoSignal()), this, SLOT(clearBusInfo()));
    }
}


/**
 * @brief MainWindow::simulateTransport Move vehicle to new location
 */
void MainWindow::simulateTransport() {

    // Spwan new vehicle every 6 minutes
    if (myTime.minute() % 6 == 0 && myTime.minute() != 0 && myTime.second() == 0) {

        for (Line * line: myLines) {

            if (line->getBusNo() > line->busesOnRoad) {
                Vehicle * v = new Vehicle(myScene, line, QTime::fromString(ui->timeLabel->text(), "hh : mm : ss"), line->busesOnRoad + 1);
                allVehicles.push_back(v);
                line->busesOnRoad++;

                connect(v, SIGNAL(paintInfoSignal(Vehicle * )), this, SLOT(generateInfo(Vehicle * )));
                connect(v, SIGNAL(createLabelSignal(QString, QString, qreal, Vehicle * )), this, SLOT(generateLabel(QString, QString, qreal, Vehicle * )));
                connect(v, SIGNAL(paintRoadSignal(int, int, int, int, QString)), this, SLOT(paintRoad(int, int, int, int, QString)));
                connect(v, SIGNAL(clearBusInfoSignal()), this, SLOT(clearBusInfo()));
            }
        }
    }

    for (Vehicle * v: allVehicles) {
        v->updatePosition(myTime);
    }

    update();
    moveMinibus();
}


/**
 * @brief MainWindow::moveMinibus Move minibus around the bottom minimap, as well as update delay
 */
void MainWindow::moveMinibus() {
    if (minibus != nullptr) {
        // Position
        minibus->setPos(mini->positionOnLine() * 1000, 0);

        // Delay
        QTime a(0, 0, 0);
        a = a.addSecs(int(mini->delay));

        delete delay;
        delay = myBusScene->addText("Current delay: " + a.toString("m ") + "mins");
        delay->setPos(-180, 5);

        if (mini->positionOnLine() > 0.9) swap = true;

        if (mini->positionOnLine() == 0 and swap) {
            for (QGraphicsTextItem * item: departures) {
                QTime itemTime = QTime::fromString(item->toPlainText(), "hh:mm");
                itemTime = itemTime.addSecs(3600);
                QString time_str = itemTime.toString("hh:mm");
                item->setPlainText(time_str);
            }

            swap = false;
        }

    }
}


/**
 * @brief MainWindow::generateInfo Generate info about vehicle
 * @param vehicle Vehicle which info is displayed
 */
void MainWindow::generateInfo(Vehicle * vehicle) {
    for (Vehicle * item: allVehicles) {
        item->setGraphicsEffect(0);
    }

    // Info about line
    auto lineName = myBusScene->addText("Line: " + vehicle->lineName);
    lineName->setPos(-180, -25);

    // Info about bus
    auto no = QString::number(vehicle->busNo);
    auto busNo = myBusScene->addText("Bus: " + no);
    busNo->setPos(-180, -10);

    // Info abou delay
    QTime a(0, 0, 0);
    a = a.addSecs(int(vehicle->delay));

    delay = myBusScene->addText("Current delay: " + a.toString("m ") + "mins");
    delay->setPos(-180, 5);

}


/**
 * @brief MainWindow::generateLabel Generate info about vehicle
 * @param label_name Name of stop
 * @param departure Departure time
 * @param distance Distance to next stop
 * @param vehicle Vehicle whos info is displayed
 */
void MainWindow::generateLabel(QString label_name, QString departure, qreal distance, Vehicle * vehicle) {
    // Vehicle
    if (ui->cancelRoad->text() != "OK") {
        combo->setDisabled(1);
        ui->cancelRoad->setDisabled(1);
    }
    mini = vehicle;
    auto line = myBusScene->addLine(0, 0, 1000, 0);
    line->setPen(QPen({
        Qt::black
    }, 2));

    // Representation of bus stop (ellipse icon)
    QPen pen;
    pen.setBrush(Qt::black);
    myBusScene->addEllipse(1000 * distance, -5, 10, 10, pen, QBrush(Qt::black));

    // Name of the stop
    auto stop = myBusScene->addText(label_name);
    stop->setPos(1000 * distance - 13, -30);

    // Departure time from the stop
    auto departureTime = myBusScene->addText(departure);
    departureTime->setPos(1000 * distance - 13, 10);
    departures.push_back(departureTime);

    if (minibus == nullptr) {
        minibus = myBusScene->addEllipse(mini->positionOnLine() - 2, -7, 14, 14, pen);
    }
}


/**
 * @brief MainWindow::paintRoad Paint road of selected vehicle
 * @param x1 coord
 * @param y1 coord
 * @param x2 coord
 * @param y2 coord
 * @param lineName Name of line
 */
void MainWindow::paintRoad(int x1, int y1, int x2, int y2, QString lineName) {
    coloredLine = myScene->addLine(x1, y1, x2, y2);

    // Every bus line has different color
    if (lineName == "Yellow") {
        coloredLine->setPen(QPen({
            QColor(252, 191, 30)
        }, 3));
    } else if (lineName == "Green") {
        coloredLine->setPen(QPen({
            QColor(34, 139, 34)
        }, 3));
    } else if (lineName == "Blue") {
        coloredLine->setPen(QPen({
            QColor(3, 90, 166)
        }, 3));
    }
    // In case new line was added, color would be red
    else {
        coloredLine->setPen(QPen(Qt::red, 3));
    }

    coloredLines.push_back(coloredLine);
}


/**
 * @brief MainWindow::clearBusInfo Clear info about bus
 */
void MainWindow::clearBusInfo() {
    //delete minibus;
    minibus = nullptr;
    myBusScene->clear();
    departures.clear();

    if (coloredLines.size() > 0) {
        for (QGraphicsLineItem * item: coloredLines) {
            delete item;
        }
    }

    coloredLines.clear();
}


/**
 * @brief MainWindow::enableCombo Slot for changing street limitations
 * @param pressed Which street was pressed
 */
void MainWindow::enableCombo(Street * pressed) {

    // Do not show any info about lines
    emit clearBusInfo();

    if (ui->cancelRoad->text() == "OK") {
        if (std::find(pressedStreets.begin(), pressedStreets.end(), pressed) != pressedStreets.end()) {
            pressedStreets.erase(std::remove(pressedStreets.begin(), pressedStreets.end(), pressed), pressedStreets.end());
            pressed->setPen(QPen(Qt::black, 2));
            return;
        } else {
            if (pressed->getSpeedLimit() == 0) {
                return;
            }
            pressedStreets.push_back(pressed);
            pressed->setPen(QPen(Qt::red, 3));
            return;
        }
    }

    ui->closedLabel->setVisible(false);
    combo->setVisible(true);
    disconnect(this, SIGNAL(newSpeedForStreet(QString)), nullptr, nullptr);
    connect(this, SIGNAL(newSpeedForStreet(QString)), pressed, SLOT(receiveNewSpeed(QString)));

    if (pressed->getSpeedLimit() == 1) {
        combo->setCurrentIndex(0);
    } else if (pressed->getSpeedLimit() == 0.75) {
        combo->setCurrentIndex(1);
    } else if (pressed->getSpeedLimit() == 0.5) {
        combo->setCurrentIndex(2);
    } else if (pressed->getSpeedLimit() == 0.25) {
        combo->setCurrentIndex(3);
    } else if (pressed->getSpeedLimit() == 0.0) {
        combo->setVisible(false);
        ui->closedLabel->setVisible(true);
    }

    if (pressed->getSpeedLimit() != 0.0) {
        combo->setDisabled(0);
        ui->cancelRoad->setDisabled(0);
    }
}


/**
 * @brief MainWindow::cancelRoad Cancel/close specified road
 */
void MainWindow::cancelRoad() {
    qDebug() << "Button text " << ui->cancelRoad->text();

    if (ui->cancelRoad->text() == "Close Road") {
        emit newSpeedForStreet("Closed");
        ui->cancelRoad->setText("OK");
        combo->setDisabled(1);
        timer->stop();
    } else {
        ui->cancelRoad->setText("Close Road");

        // Clear out selection
        for (Street * item: pressedStreets) {
            item->setPen(QPen(Qt::black, 2));
        }

        int canClose = 0;

        // Check if street can be closed
        for (Line * line: myLines) {
            QString success = line->closedRoadCheck(lastClosed, pressedStreets);

            if (success == "Success") {
                canClose++;
                continue;
            } else {
                // Route specified is not valid
                QString message = "Could no init deroute for line: " + line->getLineName() + "\n" + success;

                // Write errror message
                errorWindow(message);

                // Do not close the street
                emit newSpeedForStreet("Normal");
                break;
            }
        }

        // There is no conflict in deroute roads => street can be closed
        if (canClose == static_cast < int > (myLines.size())) {
            for (Line * line: myLines) {
                line->closeRoad(lastClosed);
            }
        }

        pressedStreets.clear();
        ui->cancelRoad->setDisabled(1);

        timer->start();
    }
}


/**
 * @brief MainWindow::errorWindow Creates new modal window and prints error message
 * @param message Error message
 */
void MainWindow::errorWindow(QString message) {
    ErrorWindow * err = new ErrorWindow();
    err->setGeometry(650, 500, 555, 111);
    err->setModal(true);
    err->writeErr(message);
    err->exec();

    delete err;
}


/**
 * @brief MainWindow::streetSpeedChanged Slot for changing street limitations
 * @param new_speed New speed for street
 */
void MainWindow::streetSpeedChanged(int new_speed) {
    if (new_speed == 0) {
        emit newSpeedForStreet("Normal");
    } else if (new_speed == 1) {
        emit newSpeedForStreet("Slow");
    } else if (new_speed == 2) {
        emit newSpeedForStreet("Slower");
    } else if (new_speed == 3) {
        emit newSpeedForStreet("Slowest");
    }

    combo->setDisabled(1);
    ui->cancelRoad->setDisabled(1);
}


/**
 * @brief MainWindow::ptrClosedStreet Save last closed street
 * @param closed Last closed street
 */
void MainWindow::ptrClosedStreet(Street * closed) {
    this->lastClosed = closed;
}
