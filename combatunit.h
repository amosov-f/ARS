#ifndef COMBATUNIT_H
#define COMBATUNIT_H

#include <QGraphicsObject>
#include <QGraphicsItem>

class CombatUnit : public QGraphicsObject {
    Q_OBJECT
public:
    enum Side {
        FRIEND,
        FOE
    };

    CombatUnit(const QString& name, const Side& side);

    void hit();

    Side getSide() const;
    bool isDisabled() const;

    QString getName() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

signals:
    void send(QString message);

protected:
    QString name;

    Side side;
    QPointF velocity;
    bool disabled;

    void advance(int phase);

    QColor getColor() const;
};

#endif // COMBATUNIT_H
