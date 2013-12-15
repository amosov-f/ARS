#ifndef FOREFRONT_H
#define FOREFRONT_H

#include "combatunit.h"
#include <QGraphicsItem>
#include <vector>

using namespace std;

class Forefront : public QGraphicsItem {
public:
    Forefront();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private:
    int len;

    vector<double> angles;

};

#endif // FOREFRONT_H
