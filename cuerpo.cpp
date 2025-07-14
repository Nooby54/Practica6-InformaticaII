#include "cuerpo.h"
#include <QtMath>
#include <QPen>

#define G 1.0
#define dt 1.0
#define ESCALA 0.05

Cuerpo::Cuerpo(double radioFisico, QPointF posicionInicial, QPointF velocidadInicial, double masa, QColor color)
    : posicionFisica(posicionInicial),velocidad(velocidadInicial),masa(masa),radioFisico(radioFisico)
{
    actualizarGrafica();

    setBrush(color);
    setPen(Qt::NoPen);

    path.moveTo(posicionFisica);
    trayectoria = new QGraphicsPathItem();
    trayectoria->setPen(QPen(color, 1));
    trayectoria->setZValue(-1);  // Detrás del cuerpo
}

void Cuerpo::calcularAceleracion(const QList<Cuerpo*> &otros) {
    aceleracion = QPointF(0, 0);
    for (Cuerpo *otro : otros) {
        if (otro == this) continue;

        QPointF vectorPosicion = otro->posicionFisica - posicionFisica;
        double distanciaala2 = qPow(vectorPosicion.x(), 2) + qPow(vectorPosicion.y(), 2);
        double distancia = qSqrt(distanciaala2);

        if (distancia < 1.0) continue;

        QPointF dir = vectorPosicion / distancia;
        double a = G * otro->masa / distanciaala2;
        aceleracion += dir * a;
    }
}

void Cuerpo::mover() {
    velocidad += aceleracion * dt;
    posicionFisica += velocidad * dt;
}

void Cuerpo::actualizarGrafica() {
    double x = (posicionFisica.x() + 8000) * ESCALA;
    double y = 800 - (posicionFisica.y() + 8000) * ESCALA;
    setPos(x, y);

    double r = radioFisico * ESCALA;
    setRect(-r, -r, 2*r, 2*r);
}

void Cuerpo::actualizarTrayectoria() {
    path.lineTo(posicionFisica);
    QPainterPath visual;
    for (int i = 0; i < path.elementCount(); ++i) {
        QPointF pf = path.elementAt(i);
        QPointF qtP = QPointF((pf.x() + 8000) * ESCALA, 800 - (pf.y() + 8000) * ESCALA);
        if (i == 0)
            visual.moveTo(qtP);
        else
            visual.lineTo(qtP);
    }
    trayectoria->setPath(visual);
}
