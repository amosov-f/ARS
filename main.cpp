#include <iostream>
#include <QtWidgets>
#include "combatunit.h"
#include "artillery.h"
#include "ars.h"
#include "panzer.h"
#include "battlefield.h"
#include "pager.h"
#include "modalbutton.h"

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Pager* pager = new Pager();
    pager->setReadOnly(true);
    pager->resize(200, 660);

    Battlefield* battlefield = new Battlefield(pager);

    QLayout* vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(pager);
    vBoxLayout->addWidget(new ModalButton(battlefield));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(battlefield);
    layout->addLayout(vBoxLayout);

    QWidget window;
    window.setLayout(layout);

    window.show();

    return app.exec();
}

