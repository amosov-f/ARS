#include "battlefield.h"

#include "combatunit.h"
#include "panzer.h"
#include "artillery.h"
#include "ars.h"
#include "forefront.h"
#include <iostream>
#include "intelligence.h"

using namespace std;

Battlefield::Battlefield(Pager* pager) {
    QGraphicsScene* scene = new QGraphicsScene();
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));


    scene->setSceneRect(0, 0, 1000, 700);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    mainDir = 205;

    troopSize = 3;
    for (int i = 0; i < troopSize; ++i) {
        Artillery* artillery = new Artillery("Расчет " + QString::number(i + 1), 0, CombatUnit::FRIEND);
        crews.append(artillery);

        artillery->setPos(800 + rand() % 100, 450 + rand() % 100);
        artillery->setRotation(mainDir + rand() % 10);
        scene->addItem(artillery);
        connect(artillery, SIGNAL(send(QString)), pager, SLOT(receive(QString)));
    }

    Intelligence* intelligence = new Intelligence("Разведка", CombatUnit::FRIEND);
    connect(intelligence, SIGNAL(send(QString)), pager, SLOT(receive(QString)));

    for (int i = 0; i < 1; ++i) {
        Panzer* panzer = new Panzer("Танк " + QString::number(i + 1), CombatUnit::FOE);
        if (i == 0) {
            target = panzer;
        }

        panzer->setPos(rand() % 300, rand() % 300);
        panzer->setRotation(rand() % 15 + 20);
        scene->addItem(panzer);

        connect(panzer, SIGNAL(destroyed()), intelligence, SLOT(notch()));
    }


    ars = new ARS("АРК", CombatUnit::FRIEND);
    ars->setPos(700, 500);
    ars->setRotation(180);
    scene->addItem(ars);
    connect(ars, SIGNAL(send(QString)), pager, SLOT(receive(QString)));

    QGraphicsItem* forefront = new Forefront();
    forefront->setPos(770, 250);
    forefront->setRotation(180);
    scene->addItem(forefront);

    headquarters = new CombatUnit("Штаб", CombatUnit::FRIEND);
    connect(headquarters, SIGNAL(send(QString)), pager, SLOT(receive(QString)));

    setScene(scene);

    setRenderHint(QPainter::Antialiasing);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Пристрелка с АРК"));
    resize(1200, 700);
}

void Battlefield::init() {
    emit headquarters->send(
            "Пристрелку будет вести батарея 1,\n" +
            QString::number(troopSize) + " 122-мм \"гаубицы Д-30\",\n" +
            "основное направление стрелбы " + QString::number((mainDir + 90) / 360.0 * 60) + ",\n" +
            "координаты огневой позиции X = " + QString::number(crews[0]->pos().x() * 100) + ", Y = " + QString::number(crews[0]->pos().y() * 100) + ",\n" +
            "высота 10 м.\n"
    );

    emit headquarters->send(
            QString() +
            "установки для стрельбы батареи №1,\n" +
            "цель №1,\n" +
            "координаты цели X = " + QString::number(target->pos().x() * 100) + ", Y = " + QString::number(target->pos().y() * 100)  + ",\n" +
            "высота 11 м,\n" +
            "снаряд фугасный,\n" +
            "доворот от ОН 5-05 влево,\n" +
            "угол возвышения 5 тысячных,\n" +
            "дальность " + QString::number(QVector2D(target->pos() - crews[0]->pos()).length() * 10) + " м,\n" +
            "высота траектории 260 м,\n" +
            "полетное время снаряда 15 с,\n" +
            "величина деривации 0.01.\n"
    );

    emit ars->send(
            QString() +
            "К обслуживанию стрельбы готов,\n" +
            "темп огня 1 выстрел в 30 секунд.\n"
    );

    crews[0]->fireAndCharge();

    QTimer::singleShot(crews[0]->getChargeTime(), crews[0], SLOT(fireAndCharge()));

    QTimer::singleShot(2 * crews[0]->getChargeTime(), ars, SLOT(correction()));
    QTimer::singleShot(2 * crews[0]->getChargeTime() + 2000, crews[0], SLOT(correction()));

    for(int i = 0; i < crews.size(); ++i) {
        QTimer::singleShot(2 * crews[0]->getChargeTime() + i * 3 * 1000 - 2000, crews[i], SLOT(fireToDisable()));
    }

    start();
}

void Battlefield::start() {
    timer->start(1000 / 33);
}

void Battlefield::stop() {
    timer->stop();
}

