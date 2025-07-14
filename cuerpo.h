#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPointF>

class Cuerpo : public QGraphicsEllipseItem {
public:
    Cuerpo(double radioFisico, QPointF posicionFisica, QPointF velocidad, double masa, QColor color);

    void calcularAceleracion(const QList<Cuerpo*> &otros);
    void mover();
    void actualizarGrafica();      // convierte posición física a Qt
    void actualizarTrayectoria();  // actualiza la curva visual

    // Datos físicos
    QPointF posicionFisica;
    QPointF velocidad;
    QPointF aceleracion;
    double masa;
    double radioFisico;

    // Gráficos
    QGraphicsPathItem *trayectoria;
    QPainterPath path;
};

#endif // CUERPO_H
