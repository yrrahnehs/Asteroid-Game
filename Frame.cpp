//
// Created by Harry Shen on 2022-01-01.
//

#include "Frame.h"
#include <iostream>

Frame::Frame(QGraphicsScene *) {
    setSceneRect(0, 0, 640, 480);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsTextItem *score_text = this->addText("SCORE : ");
    score = this->addText(QString::number(points));
    QFont f;
    f.setPointSize(20);
    score_text->setFont(f);
    score->setFont(f);
    score_text->setPos(0, this->height() - 30);
    score->setPos(75, this->height() - 30);

    player = new Player(this->width()/2 - 4, this->height()/2-12, 50);
    addItem(player);

    auto *ticker = new QTimer;
    ticker->setSingleShot(false);
    QObject::connect(ticker, &QTimer::timeout, this, &QGraphicsScene::advance);
    QObject::connect(ticker, &QTimer::timeout, this, &Frame::tick);
    ticker->start(15);

    timer = new QElapsedTimer;
    timer->start();

    Asteroid *a = new Asteroid(0);
    asteroids.emplace_back(a);
    addItem(a);
}

void Frame::tick() {
    srand(std::time(nullptr));
    // spawn a new asteroid every 5 seconds
    if (timer->elapsed() >= 5000) {
        auto *p = new Asteroid(rand() % 4);
        this->addItem(p);
        asteroids.emplace_back(p);
        timer->restart();
    }

    // player asteroid collision
    for (int j = 0; j < asteroids.size(); j++) {
        if (player->collidesWithItem(asteroids[j])) {
            removeItem(asteroids[j]);
            asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids[j]),
                            asteroids.end());
        }
    }

    // bullets and asteroid collision
    for (int j = 0; j < bullets.size(); j++) {
        if (!bullets[j]->InFrame()) {
            removeItem(bullets[j]);
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]), bullets.end());
        }

        for (int i = 0; i < asteroids.size(); i++) {
            if (asteroids[i]->collidesWithItem(bullets[j])) {

                removeItem(asteroids[i]);
                asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids[i]),
                                asteroids.end());

                removeItem(bullets[j]);
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]), bullets.end());

                points++;
                score->setPlainText(QString::number(points));
            }
        }
    }
}

void Frame::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
            player->SetKey(0, true);
            break;
        case Qt::Key_A:
            player->SetKey(1, true);
            break;
        case Qt::Key_S:
            player->SetKey(2, true);
            break;
        case Qt::Key_D:
            player->SetKey(3, true);
            break;
    }
    if (event->key() == Qt::Key_Space) {
        auto *newBullet = new Bullet(player->GetX(), player->GetY(), player->GetAngle());
        this->addItem(newBullet);
        bullets.emplace_back(newBullet);
    }
}

void Frame::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
            player->SetKey(0, false);
            break;
        case Qt::Key_A:
            player->SetKey(1, false);
            break;
        case Qt::Key_S:
            player->SetKey(2, false);
            break;
        case Qt::Key_D:
            player->SetKey(3, false);
            break;
    }
}

