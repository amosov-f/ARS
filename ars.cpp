#include "ars.h"

#include <QPainter>
#include <QGraphicsScene>
#include "shell.h"
#include <iostream>

using namespace std;

ARS::ARS(Side side) : CombatUnit(side) {
    base = 40;
}

QRectF ARS::boundingRect() const {
    return QRectF(-base / 2, 0, base, base);
}

QPainterPath ARS::shape() const {
    QPainterPath path;
    path.addRect(QRectF(-base / 2, 0, base, base));
    return path;
}

void ARS::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(getColor()));

    QVector<QPointF> triangle;
    triangle.push_back(QPointF(-base / 6, 0));
    triangle.push_back(QPointF(base / 6, 0));
    triangle.push_back(QPointF(0, base / 3));
    painter->drawPolygon(triangle);

    QPointF center(0, base / 2);
    painter->drawLine(0, base / 3, 0, base / 2);


    foreach (QGraphicsItem* item, scene()->items()) {
        if (dynamic_cast<Shell*>(item) != NULL) {
            Shell* shell = (Shell*)item;
            if (shell->getVelocityZ() < 0) {
                painter->drawLine(center, mapToParent(shell->pos()));
            }
        }
    }
}

