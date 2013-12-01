#ifndef ARTILLERY_H
#define ARTILLERY_H

#include <QGraphicsItem>
#include <QTimer>
#include "combatunit.h"
#include "shell.h"
#include <QVector2D>

class Artillery : public CombatUnit {
    Q_OBJECT
public:
    Artillery(int id, Side side);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public slots:
    void fire();
    void init();

private:
    double alpha;
    const double velocity0;
    double radius;
    int id;

    QTimer timer;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    qreal angle(const QVector2D& p) const;
};

#endif // ARTILLERY_H
