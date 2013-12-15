#include "ars.h"

#include <QPainter>
#include <QGraphicsScene>
#include "shell.h"
#include <iostream>
#include "beam.h"

using namespace std;

ARS::ARS(const QString& name, const Side& side) : CombatUnit(name, side) {
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
    painter->setPen(getColor());

    QVector<QPointF> triangle;
    triangle.push_back(QPointF(-base / 3, 0));
    triangle.push_back(QPointF(base / 3, 0));
    triangle.push_back(QPointF(0, base / 3));
    painter->drawPolygon(triangle);

    painter->drawLine(0, base / 3, 0, base / 2);
    painter->drawLine(base / 2.5, base / 2, 0, base / 2);
    painter->drawLine(0, base / 2, -base / 3, 3 * base / 4);
}

void ARS::correction() {
    emit send("Корректуры расчтаны!");
}

void ARS::advance(int phase) {
    QPointF center(0, base / 2);
    foreach (QGraphicsItem* item, scene()->items()) {
        if (dynamic_cast<Shell*>(item) != NULL) {
            Shell* shell = (Shell*)item;
            if (shell->getVelocityZ() < 0 && shell->getId() == 0 && !targets.contains(shell)) {
                emit send("Засек снаряд!");
                targets.append(shell);
                Beam* beam = new Beam(shell);
                beam->setPos(mapToParent(center));
                scene()->addItem(beam);
            }
        }
    }
}

