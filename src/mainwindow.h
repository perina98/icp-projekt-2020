/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 * @author Lukas Perina <xperin11@stud.fit.vutbr.cz>
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "errorwindow.h"
#include "street.h"
#include "stop.h"
#include "vehicle.h"
#include "line.h"

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPushButton>
#include <QVariantAnimation>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QComboBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//! Class representing main window and the map itself.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* initScene(std::vector<Street*>, std::vector<Stop*>);
    Ui::MainWindow *ui;
    Vehicle *mini;
    QGraphicsEllipseItem *minibus{nullptr};
    QComboBox *combo;

    void initPublicTransport(std::vector<Line*>);
    void simulateTransport();
    void moveMinibus();

    std::vector<Street*> pressedStreets;
    std::vector<QGraphicsLineItem*> coloredLines;

private:
    QGraphicsScene* myScene;
    QGraphicsScene* myBusScene;
    QGraphicsLineItem* coloredLine;
    Street *lastClosed;
    QGraphicsTextItem *delay;
    QTimer *timer;
    QTime myTime;

    bool swap{false};
    double speedMultiplier{1};
    void errorWindow(QString);

    std::vector<Street*> drawnStreets;
    std::vector<QGraphicsTextItem*> departures;
    std::vector<Vehicle*> allVehicles;
    std::vector<Line*> myLines;
    std::vector<Street*> myStreets;
    std::vector<Stop*> myStops;

private slots:
    void zoom(int z);
    void getTime();
    void setSpeed(double x);
    void resetTimeLabel();

public slots:
    void cancelRoad();
    void generateInfo(Vehicle*);
    void generateLabel(QString, QString, qreal, Vehicle*);
    void paintRoad(int x1,int y1, int x2, int y2,QString lineName);
    void clearBusInfo();
    void enableCombo(Street *pressed);
    void streetSpeedChanged(int new_speed);
    void ptrClosedStreet(Street* closed);

signals:
    void newSpeedForStreet(QString newspeed);

};
#endif // MAINWINDOW_H
