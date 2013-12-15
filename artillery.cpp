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

Artillery::Artillery(const QString& name, int id, const Side& side) : CombatUnit(name, side), velocity0(2.75) {
    alpha = 1.0;
    radius = 20;
    this->id = id;
    steps = 0;
    timer = NULL;
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

int Artillery::getChargeTime() {
    return 10 * 1000;
}

void Artillery::fireToDisable() {
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(guidanceAndFireAndCharge()));
    timer->start(getChargeTime());
}

bool Artillery::guidance() {
    foreach (QGraphicsItem* item, scene()->items()) {
        if (dynamic_cast<CombatUnit*>(item) != NULL) {
            CombatUnit* unit = (CombatUnit*)item;
            if (unit->getSide() != getSide() && !unit->isDisabled()) {
                QVector2D dir = QVector2D(unit->pos() - pos());

                double l = 0.0099 * dir.length() / qPow(velocity0, 2);
                if (l > 1) {
                    continue;
                }
                alpha = 0.5 * qAsin(l);
                setRotation(angle(dir));

                emit send(
                        QString() +
                        "Наведение на цель произведено."
                        //"угол " + QString::number(angle(dir)) + ",\n" +
                        //"дистанция " + QString::number(dir.length()) + "."
                );
                return true;
            }
        }
    }
}

void Artillery::fireAndCharge() {
    fire(0);
    timer->singleShot(getChargeTime(), this, SLOT(emitReady()));
}

void Artillery::emitReady() {
    emit ready();
}

void Artillery::guidanceAndFireAndCharge() {
    if (!guidance()) {
        return;
    }

    fire(1);
    timer->singleShot(getChargeTime(), this, SLOT(emitReady()));
}

void Artillery::fire(int id) {
    /*QList<Gap*> gaps;
    foreach (QGraphicsItem* item, scene()->items()) {
        if (dynamic_cast<Gap*>(item) != NULL) {
            Gap* gap = (Gap*)item;
            if (gap->getId() == id) {
                gaps.push_back(gap);
            }
        }
    }
    bool ok = false;
    if (gaps.size() >= 2) {
        QVector2D mid = QVector2D((gaps[0]->pos() + gaps[1]->pos()) / 2);
        CombatUnit* target = NULL;
        foreach (QGraphicsItem* item, scene()->items()) {
            if (dynamic_cast<CombatUnit*>(item) != NULL) {
                CombatUnit* unit = (CombatUnit*)item;
                if (unit->getSide() != getSide() && !unit->isDestroyed()) {
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

        double l = 0.01 * dir.length() / qPow(velocity0, 2);
        if (l > 1) {
            continue;
        }
        alpha = 0.5 * qAsin(l);
        setRotation(angle(dir));


        ok = true;
        emit send("Веду стрельбу на поражение!");
        emit send("Угол " + QString::number(angle(dir)) + ", дистанция " + QString::number(dir.length()));


    }
    if (!ok) {
        emit send("Веду пристрелку!");
    }*/

    emit send("Огонь!");
    Shell* shell = new Shell(id, QVector3D(velocity0 * qCos(alpha), 0, velocity0 * qSin(alpha)));
    shell->setPos(this->mapToParent(0, 0));
    shell->setRotation(rotation() + (rand() % 4) - 1.5);
    scene()->addItem(shell);
}

void Artillery::mousePressEvent(QGraphicsSceneMouseEvent*) {
    this->fire(0);
}

qreal Artillery::angle(const QVector2D& p) const {
    return qAtan2(p.y(), p.x()) / M_PI * 180;
}

void Artillery::correction() {
    emit send("Корректуры получены. Навожусь.");
}
