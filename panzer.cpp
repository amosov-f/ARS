#include "panzer.h"
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <iostream>
#include <QGraphicsScene>

using namespace std;

Panzer::Panzer(const QString& name, const Side& side) : CombatUnit(name, side) {
    velocity = QPointF(0.04, 0);
    radius = 20;
}

QRectF Panzer::boundingRect() const {
    return QRectF(-radius, -radius / 2, 2 * radius, radius);
}

QPainterPath Panzer::shape() const {
    QPainterPath path;
    path.addPolygon(getPolygonF());
    return path;
}

void Panzer::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(getColor()));

    painter->drawPolygon(getPolygonF());
}

QPolygonF Panzer::getPolygonF() const {
    QVector<QPointF> vertices;

    vertices.push_back(QPointF(radius, 0));
    vertices.push_back(QPointF(0, radius / 2));
    vertices.push_back(QPointF(-radius, 0));
    vertices.push_back(QPointF(0, -radius / 2));

    return QPolygonF(vertices);
}
