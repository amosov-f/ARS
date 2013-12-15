#ifndef PANZER_H
#define PANZER_H

#include "combatunit.h"

class Panzer : public CombatUnit {
public:
    Panzer(const QString& name, const Side& side);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QPolygonF getPolygonF() const;

    double radius;
};

#endif // PANZER_H
