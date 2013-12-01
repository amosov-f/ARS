#ifndef ARS_H
#define ARS_H

#include "combatunit.h"

class ARS : public CombatUnit {
public:
    ARS(Side side);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    double base;

};

#endif // ARS_H
