#include <QtDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create grapher for graphicsView widget
    _graphicsView = new GraphicsView;
    _graphicsView->setParent(ui->frame);
    _graphicsView->resize(ui->frame->width(), ui->frame->height());

    // set up grapher to handle graphing of nodes
    _grapher = new Grapher(_graphicsView);

    _x = _y = _z = _weight = 0;

}

MainWindow::~MainWindow()
{
    delete _grapher;
    delete ui;
}


// Setters for user inputs
void MainWindow::on_xInput_valueChanged(double arg1) { _x = arg1; }
void MainWindow::on_yInput_valueChanged(double arg1) { _y = arg1; }
void MainWindow::on_zInput_valueChanged(double arg1) { _z = arg1; }
void MainWindow::on_weightInput_valueChanged(double arg1) { _weight = arg1; }


/**
 * Slot called when button to add point is clicked
 * @brief MainWindow::on_addPoint_clicked
 */
void MainWindow::on_addPoint_clicked()
{
    _grapher->addPoint(_x, _y, _z);
}


/**
 * Slot called when add edge button is clicked
 * @brief MainWindow::on_addEdge_clicked
 */
void MainWindow::on_addEdge_clicked()
{
    _grapher->addEdge(_weight);
}

void MainWindow::on_deleteEdge_clicked()
{
    _grapher->removeEdge();
}

void MainWindow::on_deletePoint_clicked()
{
    _grapher->removeSelectedPoints();
}