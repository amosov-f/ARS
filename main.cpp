#include <iostream>
#include <QtWidgets>
#include "combatunit.h"
#include "artillery.h"
#include "ars.h"
#include "panzer.h"

using namespace std;

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1000, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    CombatUnit* art1 = new Artillery(1, CombatUnit::FRIEND);
    CombatUnit* art2 = new Artillery(2, CombatUnit::FRIEND);
    CombatUnit* art3 = new Artillery(3, CombatUnit::FRIEND);
    CombatUnit* art4 = new Artillery(4, CombatUnit::FRIEND);
    CombatUnit* art5 = new Artillery(5, CombatUnit::FRIEND);
    art1->setPos(800, 550);
    art1->setRotation(220);
    art2->setPos(800, 500);
    art2->setRotation(230);
    art3->setPos(850, 490);
    art3->setRotation(220);
    art4->setPos(850, 590);
    art4->setRotation(220);
    art5->setPos(850, 690);
    art5->setRotation(220);

    CombatUnit* panzer[20];
    for (int i = 0; i < 20; ++i) {
        panzer[i] = new Panzer(CombatUnit::FOE);
        panzer[i]->setPos(rand() % 300, rand() % 300);
        panzer[i]->setRotation(rand() % 15 + 20);
        scene.addItem(panzer[i]);
    }

    CombatUnit* ars = new ARS(CombatUnit::FRIEND);
    ars->setPos(500, 300);
    ars->setRotation(180);

    scene.addItem(art1);
    scene.addItem(art2);
    scene.addItem(art3);
    scene.addItem(art4);
    scene.addItem(art5);
    scene.addItem(ars);

//! [4]
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
//! [4] //! [5]
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Пристрелка с АРК"));
    view.resize(1000, 600);
    view.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(1000 / 33);

    return app.exec();
}

