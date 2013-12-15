#include "intelligence.h"
#include <iostream>

using namespace std;

Intelligence::Intelligence(const QString &name, const Side &side) : CombatUnit(name, side) {
}


void Intelligence::notch() {
    if (side == FRIEND && dynamic_cast<CombatUnit*>(sender()) != NULL) {
        CombatUnit* unit = dynamic_cast<CombatUnit*>(sender());
        emit send("Цель №1 уничтожена!");
    }
}
