/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */
#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>
#include <QGraphicsView>
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

namespace Ui {
class ErrorWindow;
}
//! Class representing error window on bad deroute setup
class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);
    ~ErrorWindow();

    QGraphicsScene *scene;
    void writeErr(QString);

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H
