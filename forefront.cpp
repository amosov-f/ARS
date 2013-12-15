#include "forefront.h"
#include <QPainter>
#include <QVector2D>
#include <QTransform>
#include <iostream>

using namespace std;

Forefront::Forefront() {
    len = 600;
    for (int i = 0; i < len; ++i) {
        angles.push_back(rand() % 15 - 7);
    }
}

QRectF Forefront::boundingRect() const {
    return shape().boundingRect();
}

QPainterPath Forefront::shape() const {
    QPointF dir(1.0, 0);
    QPointF cur(0, 0);

    QPainterPath path(cur);

    for (int i = 0; i < len; ++i) {
        cur += dir;
        path.lineTo(cur);
        if ((int)i % 20 == 0) {
            QPointF side = QTransform().rotate(90).map(dir);
            path.lineTo(cur + side * 10);
            path.lineTo(cur);
        }
        dir = QTransform().rotate(angles[i]).map(dir);
    }
    dir = -dir;
    for (int i = len - 1; i >= 0; --i) {
        //cout << i << endl;
        dir = QTransform().rotate(-angles[i]).map(dir);
        cur += dir;
        path.lineTo(cur);
    }

    return path;
}

void Forefront::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(QBrush(Qt::red));
    painter->setPen(Qt::red);
    painter->drawPath(shape());
}
