#include "gap.h"

#include <QPainter>
#include <iostream>

using namespace std;

Gap::Gap(int id) {
    this->id = id;
}

QRectF Gap::boundingRect() const {
    //1.421
    return QRectF(0, -8, 16 * 1.421, 16);
}

QPainterPath Gap::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Gap::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->drawImage(boundingRect(), QImage("fire.png"));
}

void Gap::advance(int phase) {
}

int Gap::getId() const {
    return id;
}
