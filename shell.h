#ifndef SHELL_H
#define SHELL_H

#include "combatunit.h"
#include <QVector3D>

class Shell : public QGraphicsItem {
public:
    Shell(int id, QVector3D vel);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    double getZ() const;
    double getVelocityZ() const;

private:
    double z;
    QVector3D velocity;
    int id;

    double getRadius() const;

    void advance(int phase);
};

#endif // SHELL_H
