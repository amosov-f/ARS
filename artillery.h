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
    Artillery(const QString& name, int id, const Side& side);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    int getChargeTime();
    bool guidance();
    void fire(int id);

public slots:

    void fireAndCharge();
    void guidanceAndFireAndCharge();
    void fireToDisable();

signals:
    void ready();

private slots:

    void emitReady();
    void correction();

private:
    double alpha;
    const double velocity0;
    double radius;
    int id;

    int steps;

    bool isGuidanced;

    QTimer* timer;

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    qreal angle(const QVector2D& p) const;

};

#endif // ARTILLERY_H
