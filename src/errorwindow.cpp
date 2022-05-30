/**
 * @author Martin Fekete <xfeket00@stud.fit.vutbr.cz>
 */
#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(ui->graphicsView_3);
    ui->graphicsView_3->setScene(scene);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

void ErrorWindow::writeErr(QString message)
{
    QGraphicsTextItem *text = scene->addText(message);
    text->setPos(300, 200);
    scene->update();
}
