#include "artillery.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QtMath>
#include <QVector3D>
#include <QVector2D>
#include "gap.h"

using namespace std;

Artillery::Artillery(int id, Side side) : CombatUnit(side), velocity0(2.75) {
    alpha = 1.0;
    radius = 20;
    this->id = id;

    timer.singleShot(2 * id * 1000, this, SLOT(init()));
}

void Artillery::init() {
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(fire()));
    timer.start(7 * 1000);
}

QRectF Artillery::boundingRect() const {
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

QPainterPath Artillery::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Artillery::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(getColor()));

    painter->drawEllipse(boundingRect());
    painter->drawLine(QLineF(-0.75 * radius, 0, 0.75 * radius, 0));
    painter->drawLine(QLineF(-0.25 * radius, -0.5 * radius, 0.25 * radius, -0.5 * radius));
    painter->drawLine(QLineF(-0.25 * radius, 0.5 * radius, 0.25 * radius, 0.5 * radius));
}

void Artillery::fire() {
    QList<Gap*> gaps;
    foreach (QGraphicsItem* item, scene()->items()) {
        if (dynamic_cast<Gap*>(item) != NULL) {
            Gap* gap = (Gap*)item;
            if (gap->getId() == id) {
                gaps.push_back(gap);
            }
        }
    }
    if (gaps.size() >= 2) {
        QVector2D mid = QVector2D((gaps[0]->pos() + gaps[1]->pos()) / 2);
        CombatUnit* target = NULL;
        foreach (QGraphicsItem* item, scene()->items()) {
            if (dynamic_cast<CombatUnit*>(item) != NULL) {
                CombatUnit* unit = (CombatUnit*)item;
                if (unit->getSide() != getSide() && !unit->getStruck()) {
                    if (target == NULL) {
                        target = unit;
                    }
                    if (
                            mid.distanceToPoint(QVector2D(unit->pos())) <
                            mid.distanceToPoint(QVector2D(target->pos()))
                    ) {
                        target = unit;
                    }
                }
            }
        }
        if (target == NULL) {
            return;
        }
        QVector2D dir = QVector2D(target->pos() - pos());
        double l = dir.length();
        alpha = 0.5 * qAsin(0.01 * l / qPow(velocity0, 2));
        //cout << l << endl;
        setRotation(angle(dir));
    }

    Shell* shell = new Shell(id, QVector3D(velocity0 * qCos(alpha), 0, velocity0 * qSin(alpha)));
    shell->setPos(this->mapToParent(0, 0));
    shell->setRotation(rotation() + (rand() % 5) - 2);
    this->scene()->addItem(shell);
}

void Artillery::mousePressEvent(QGraphicsSceneMouseEvent*) {
    this->fire();
}

qreal Artillery::angle(const QVector2D& p) const {
    return qAtan2(p.y(), p.x()) / M_PI * 180;
}

