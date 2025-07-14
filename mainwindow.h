#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "cuerpo.h"
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();
    void on_sistema1_clicked();
    void on_sistema2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QTimer *timer;
    QList<Cuerpo *> cuerposSimulados;
    std::ofstream archivo;
};

#endif // MAINWINDOW_H
