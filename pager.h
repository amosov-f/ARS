#ifndef PAGER_H
#define PAGER_H

#include <QTextEdit>

class Pager : public QTextEdit {
    Q_OBJECT
public:
    Pager();
public slots:
    void receive(QString message);
};

#endif // PAGER_H
