#ifndef INTELLIGENCE_H
#define INTELLIGENCE_H

#include "combatunit.h"

class Intelligence : public CombatUnit {
    Q_OBJECT
public:
    Intelligence(const QString& name, const Side& side);



public slots:
    void notch();
};

#endif // INTELLIGENCE_H
