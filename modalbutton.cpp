#include "modalbutton.h"
#include <QThread>

ModalButton::ModalButton(Battlefield* battlefield) : QPushButton("Начать пристрелку с АРК!") {
    this->battlefield = battlefield;

    connect(this, SIGNAL(clicked()), this, SLOT(changeMode()));
}

void ModalButton::changeMode() {
    if (text() == "Стоп") {
        battlefield->stop();
        setText("Продолжить");
        return;
    }
    if (text() == "Продолжить") {
        battlefield->start();
        setText("Стоп");
        return;
    }
    battlefield->init();
    setText("Стоп");
}
