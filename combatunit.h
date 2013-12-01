#ifndef COMBATUNIT_H
#define COMBATUNIT_H

#include <QGraphicsItem>

class CombatUnit : public QGraphicsObject {
public:
    enum Side {
        FRIEND,
        FOE
    };

    CombatUnit(Side side);

    void hit();

    Side getSide() const;
    bool getStruck() const;

protected:
    Side side;
    QPointF velocity;
    bool isStruck;

    void advance(int phase);

    QColor getColor() const;
};

#endif // COMBATUNIT_H
