#include "combatunit.h"
#include "gap.h"
#include <QGraphicsScene>
#include <iostream>

using namespace std;

CombatUnit::CombatUnit(const QString& name, const Side& side) {
    this->name = name;
    this->side = side;
    this->velocity = QPointF(0, 0);
    this->disabled = false;
}

void CombatUnit::hit() {
    disabled = true;
    emit destroyed();
}

void CombatUnit::advance(int phase) {

    if (disabled) {
        velocity = QPointF(0, 0);
    }
    setPos(mapToParent(velocity));
    foreach (QGraphicsItem* item, collidingItems()) {
        //CombatUnit* unit = (CombatUnit*)item;
        //if (unit != NULL) {
        //    unit->hit();
        //}
        //Gap* gap = (Gap*)item;
        //if (gap != NULL) {
        //    scene()->removeItem(gap);
        //}
    }
}

QColor CombatUnit::getColor() const {
    if (disabled) {
        return QColor(50, 50, 50);
    }
    if (side == FRIEND) {
        return QColor(255, 0, 0);
    }
    return QColor(0, 0, 255);
}

QString CombatUnit::getName() const {
    return name;
}

CombatUnit::Side CombatUnit::getSide() const {
    return side;
}

bool CombatUnit::isDisabled() const {
    return disabled;
}

QRectF CombatUnit::boundingRect() const {
    return QRectF();
}

QPainterPath CombatUnit::shape() const {
    return QPainterPath();
}

void CombatUnit::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}
