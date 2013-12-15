#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>

class Foo : public QObject {
    Q_OBJECT
public:
    Foo();
public slots:
    void print();
};



#endif // OBJECT_H
