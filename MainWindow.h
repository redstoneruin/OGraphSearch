#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Graphics/Grapher.h"
#include "Graphics/GraphicsView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addPoint_clicked();

    void on_xInput_valueChanged(double arg1);
    void on_yInput_valueChanged(double arg1);
    void on_zInput_valueChanged(double arg1);
    void on_weightInput_valueChanged(double arg1);

    void on_addEdge_clicked();

    void on_deleteEdge_clicked();

    void on_deletePoint_clicked();

private:
    Ui::MainWindow *ui;

    Grapher* _grapher;
    GraphicsView* _graphicsView;

    double _x, _y, _z, _weight;
    QString _name;
};
#endif // MAINWINDOW_H
