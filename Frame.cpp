//
// Created by Harry Shen on 2022-01-01.
//

#include "Frame.h"
#include <iostream>

Frame::Frame(QGraphicsScene *) {
    setSceneRect(0, 0, 640, 480);
    setItemIndexMethod(QGraphicsScene::NoIndex);
    player = new Player(this->width() / 2 - 4, this->height() / 2 - 12, 50);
    addItem(player);

    auto *ticker = new QTimer;
    ticker->setSingleShot(false);
    ticker->start(15);

    Asteroid *a = new Asteroid(4);
    asteroids.emplace_back(a);
    addItem(a);

//    Asteroid *new_stroid1 = new Asteroid(100, 100, 45, 60);
//    asteroids.emplace_back(new_stroid1);
//    addItem(new_stroid1);

    timer = new QElapsedTimer;
    timer->start();

    reload_timer = new QElapsedTimer;
    reload_timer->start();

    invul = new QElapsedTimer;

    QObject::connect(ticker, &QTimer::timeout, this, &QGraphicsScene::advance);
    QObject::connect(ticker, &QTimer::timeout, this, &Frame::tick);

    QFont f;
    f.setPointSize(20);
    QGraphicsTextItem *score_text = addText("SCORE : ");
    score = this->addText(QString::number(points));
    score_text->setFont(f);
    score->setFont(f);
    score_text->setPos(0, this->height() - 35);
    score->setPos(100, this->height() - 35);
    score_text->setDefaultTextColor(Qt::white);
    score->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *health_text = addText("HEALTH : ");
    health = this->addText(QString::number(player->GetHealth()));
    health_text->setFont(f);
    health->setFont(f);
    health_text->setPos(this->width() - 150, this->height() - 35);
    health->setPos(this->width() - 40, this->height() - 35);
    health_text->setDefaultTextColor(Qt::white);
    health->setDefaultTextColor(Qt::white);
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
    srand(time(nullptr));

    // player asteroid collision
    for (int j = 0; j < asteroids.size(); j++) {
        if (player->collidesWithItem(asteroids[j])) {
            if (invul->elapsed() >= 2750) {
                player->SetHealth(player->GetHealth() - 10);
                invul->restart();
                health->setPlainText(QString::number(player->GetHealth()));
            }

            player->SetHit(true);

            removeItem(asteroids[j]);
            asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids[j]),
                            asteroids.end());
        }
    }

    if (invul->elapsed() >= 2750) {
        player->SetHit(false);
    }

    for (int j = 0; j < bullets.size(); j++) {
        // if bullets are not in frame, remove them
        if (!bullets[j]->InFrame()) {
            removeItem(bullets[j]);
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]), bullets.end());
        }

        // bullets and asteroids collision
        for (int i = 0; i < asteroids.size(); i++) {
            if (asteroids[i]->collidesWithItem(bullets[j]) && !asteroids[i]->GetInvul()) {
                double randomangle1, randomangle2;

                randomangle1 = rand() % 361;
                randomangle2 = randomangle1 + 180;

                if (asteroids[i]->GetSize() != 40) {
                    Asteroid *new_stroid1 = new Asteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), randomangle1, asteroids[i]->GetSize() - 10);
                    Asteroid *new_stroid2 = new Asteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), randomangle2, asteroids[i]->GetSize() - 10);
                    asteroids.emplace_back(new_stroid1);
                    asteroids.emplace_back(new_stroid2);
                    addItem(new_stroid1);
                    addItem(new_stroid2);
                }
                removeItem(bullets[j]);
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]), bullets.end());

                removeItem(asteroids[i]);
                asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids[i]),
                                asteroids.end());

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
    if (reload_timer->elapsed() >= 250) {
        if (event->key() == Qt::Key_Space) {
            auto *newBullet = new Bullet(player->GetX(), player->GetY(), player->GetAngle());
            this->addItem(newBullet);
            bullets.emplace_back(newBullet);
            reload_timer->restart();
        }
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

