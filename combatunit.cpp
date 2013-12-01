#include "combatunit.h"
#include "gap.h"
#include <QGraphicsScene>
#include <iostream>

using namespace std;

CombatUnit::CombatUnit(Side side) {
    this->side = side;
    this->velocity = QPointF(0, 0);
    this->isStruck = false;
}

void CombatUnit::hit() {
    isStruck = true;
}

void CombatUnit::advance(int phase) {

    if (isStruck) {
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
    if (isStruck) {
        return QColor(50, 50, 50);
    }
    if (side == FRIEND) {
        return QColor(255, 0, 0);
    }
    return QColor(0, 0, 255);
}

CombatUnit::Side CombatUnit::getSide() const {
    return side;
}

bool CombatUnit::getStruck() const {
    return isStruck;
}
