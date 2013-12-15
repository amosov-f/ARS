#include "beam.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QRectF>
#include <iostream>
#include <QVector2D>
#include <cmath>

using namespace std;

Beam::Beam(Shell* target) {
    this->target = target;
}

QRectF Beam::boundingRect() const {
    return QRectF(target->pos() - pos(), QPointF(0, 0));
}

QPainterPath Beam::shape() const {
    QPainterPath path;
    path.lineTo(QVector2D(target->pos() - pos()).length(), 0);

    return path;
}

void Beam::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (target->scene() == NULL || target->getVelocityZ() < -1.5) {
        this->scene()->removeItem(this);
        return;
    }

    //cout << target->pos().x() << ' ' << target->pos().y() << endl;
    painter->setPen(QColor(rand() % 255, rand() % 255, rand() % 255));
    painter->drawPath(shape());
    painter->drawLine(0, 0, QVector2D(target->pos() - pos()).length(), 0);
}

void Beam::advance(int phase) {
    setRotation(-QLineF(pos(), target->pos()).angle());
}
