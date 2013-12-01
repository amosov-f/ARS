#ifndef GAP_H
#define GAP_H

#include <QGraphicsItem>

class Gap : public QGraphicsItem {
public:
    Gap(int id);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    int getId() const;

protected:
    void advance(int phase);

private:
    int id;
};

#endif // GAP_H
