#ifndef ARS_H
#define ARS_H

#include "combatunit.h"
#include <QList>

class ARS : public CombatUnit {
    Q_OBJECT
public:
    ARS(const QString& name, const Side& side);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public slots:
    void correction();

protected:
    void advance(int phase);

private:
    double base;

    QList<QGraphicsItem*> targets;

};

#endif // ARS_H
