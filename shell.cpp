#include "shell.h"

#include <QPainter>
#include <iostream>
#include <QVector3D>
#include <QGraphicsScene>
#include "gap.h"

using namespace std;

Shell::Shell(int id, QVector3D velocity) {
    this->velocity = velocity;
    this->id = id;
    this->z = 0;
}

QRectF Shell::boundingRect() const {
    return QRectF(-getRadius(), -getRadius(), 2 * getRadius(), 2 * getRadius());
}

QPainterPath Shell::shape() const {
    return QPainterPath(QPointF(0, 0));
}

double Shell::getRadius() const {
    return z / 30;
}

void Shell::advance(int phase) {
    velocity.setZ(velocity.z() - 0.01);
    z += velocity.z();
    setPos(mapToParent(QPointF(velocity.x(), velocity.y())));
    if (z < 0) {
        foreach (QGraphicsItem* item, collidingItems()) {
            if (dynamic_cast<CombatUnit*>(item) != NULL) {
                CombatUnit* unit = (CombatUnit*)item;
                if (!unit->isDisabled()) {
                    unit->hit();
                    /*foreach (QGraphicsItem* gap, scene()->items()) {
                        if (dynamic_cast<Gap*>(gap) != NULL) {
                            if (id == ((Gap*)gap)->getId()) {
                                scene()->removeItem(gap);
                            }
                        }
                    }*/
                }
            }
        }

        QGraphicsItem* gap = new Gap(id);
        gap->setPos(pos());
        gap->setRotation(270);

        scene()->addItem(gap);
        scene()->removeItem(this);
    }
}

void Shell::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    painter->drawEllipse(boundingRect());
}

double Shell::getZ() const {
    return z;
}

double Shell::getVelocityZ() const {
    return velocity.z();
}

int Shell::getId() const {
    return id;
}
