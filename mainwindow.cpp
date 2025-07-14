#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cuerpo.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <fstream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 800, 800);
    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedSize(800, 800);
    this->setFixedSize(1026, 826);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        for (Cuerpo *c : std::as_const(cuerposSimulados))
            c->calcularAceleracion(cuerposSimulados);
        for (Cuerpo *c : std::as_const(cuerposSimulados)) {
            c->mover();
            c->actualizarGrafica();
            c->actualizarTrayectoria();
        }
        if (archivo) {
            for (Cuerpo *c : std::as_const(cuerposSimulados))
                archivo << c->posicionFisica.x() << "   " << c->posicionFisica.y() << "  ";
            archivo << "\n";
        }
    });
}

MainWindow::~MainWindow()
{
    archivo.close();
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    this->close();
}


void MainWindow::on_sistema1_clicked()
{
    for(auto* item : escena->items()){
        delete item;
    }
    // === Sistema 1 ===

    Cuerpo *c1 = new Cuerpo(120, QPointF(0, -7000), QPointF(2, 0), 70, Qt::black);
    Cuerpo *c2 = new Cuerpo(300, QPointF(0, 0),     QPointF(0, 0), 70000, Qt::white);
    Cuerpo *c3 = new Cuerpo(100, QPointF(4000, 5000), QPointF(-1.6, 1.2), 25, Qt::blue);

    cuerposSimulados = {c1, c2, c3};

    for (Cuerpo *c : std::as_const(cuerposSimulados)) {
        escena->addItem(c->trayectoria);
        escena->addItem(c);
    }

    archivo.open("../../data/salida.txt");
    for (int i = 0; i < cuerposSimulados.size(); ++i) {
        archivo << "x" << (i+1) << "    " << "y" << (i+1);
        if (i < cuerposSimulados.size() - 1) archivo << "   ";
    }
    archivo << "\n";
    timer->start(16);
}


void MainWindow::on_sistema2_clicked()
{
    for(auto* item : escena->items()){
        delete item;
    }

    // === Sistema 2 ===
    Cuerpo *c1 = new Cuerpo(200, QPointF(0, 0), QPointF(0, 0), 50000, Qt::black);
    Cuerpo *c2 = new Cuerpo(70, QPointF(-5000, 0),     QPointF(0, -2), 70, Qt::blue);
    Cuerpo *c3 = new Cuerpo(70, QPointF(5000, 0), QPointF(0, 2), 70, Qt::red);
    Cuerpo *c4 = new Cuerpo(70, QPointF(0, -5000), QPointF(2, 0), 70, Qt::green);
    Cuerpo *c5 = new Cuerpo(70, QPointF(0, 5000),     QPointF(-2, 0), 70, Qt::cyan);

    cuerposSimulados = {c1, c2, c3, c4, c5};

    for (Cuerpo *c : std::as_const(cuerposSimulados)) {
        escena->addItem(c->trayectoria);
        escena->addItem(c);
    }

    archivo.open("../../data/salida.txt");
    for (int i = 0; i < cuerposSimulados.size(); ++i) {
        archivo << "x" << (i+1) << "    " << "y" << (i+1);
        if (i < cuerposSimulados.size() - 1) archivo << "   ";
    }
    archivo << "\n";
    timer->start(16);
}


void MainWindow::on_pushButton_4_clicked()
{
    if(timer) timer->start(16);
}


void MainWindow::on_pushButton_3_clicked()
{
    if(timer) timer->stop();
}

