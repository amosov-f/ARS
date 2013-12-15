#include "pager.h"
#include <QString>
#include "combatunit.h"

Pager::Pager() {
    resize(400, 660);
    setReadOnly(true);
}

void Pager::receive(QString message) {
    QObject* object = sender();
    if (dynamic_cast<CombatUnit*>(object) != NULL) {
        CombatUnit* unit = (CombatUnit*)object;
        append(unit->getName() + ": " + message);
    }
}
