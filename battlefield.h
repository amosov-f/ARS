#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QGraphicsView>
#include "pager.h"
#include "artillery.h"
#include "panzer.h"
#include <vector>
#include "ars.h"

using namespace std;

class Battlefield : public QGraphicsView {
    Q_OBJECT
public:
    Battlefield(Pager* pager);

public slots:
    void init();
    void start();
    void stop();

private:
    QTimer* timer;
    ARS* ars;

    QList<Artillery*> crews;
    int troopSize;
    int mainDir;
    CombatUnit* headquarters;

    Panzer* target;

};

#endif // BATTLEFIELD_H
