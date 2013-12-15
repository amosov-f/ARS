#ifndef BEAM_H
#define BEAM_H

#include <QGraphicsItem>
#include "shell.h"

class Beam : public QGraphicsItem {
public:
    Beam(Shell* target);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void advance(int phase);

private:
    Shell* target;
};

#endif // BEAM_H
