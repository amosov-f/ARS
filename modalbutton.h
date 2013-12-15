#ifndef MODALBUTTON_H
#define MODALBUTTON_H

#include <QPushButton>
#include "battlefield.h"

class ModalButton : public QPushButton {
    Q_OBJECT
public:
    ModalButton(Battlefield* battlefield);

public slots:
    void changeMode();

private:
    Battlefield* battlefield;

};

#endif // MODALBUTTON_H
