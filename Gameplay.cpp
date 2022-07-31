//
// Created by Harry Shen on 2022-01-01.
//

#include "Gameplay.h"
#include <iostream>
#include <QAbstractButton>




Gameplay::Gameplay(QGraphicsScene *) {
    srand(std::time(nullptr));
    // sets up screen size
    setSceneRect(0, 0, 640, 480);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    // boolean for changing respawn rate
    toggle = false;

    ticker->start(15);
#ifdef __APPLE__
#define OFFSET 85
#endif

    QFont f;
    f.setPointSize(60);
    // title text
    title_text = addText("A S T E R O I D S");
    title_text->setFont(f);
    title_text->setPos(30 + OFFSET, 60);
    title_text->setDefaultTextColor(Qt::white);

    f.setPointSize(40);

    QPalette palette1;
    palette1.setColor(QPalette::Window, Qt::black);

    // start button
    startbutton = new QPushButton("START");
    startbutton->setGeometry(QRect(this->width() / 2 - 40, this->height() / 2 + 30, 80, 30));
    QGraphicsWidget *startBtn = this->addWidget(startbutton);
    startBtn->setPalette(palette1);

    // quit button
    quitbutton = new QPushButton("QUIT");
    quitbutton->setGeometry(QRect(this->width() / 2 - 40, this->height() / 2 + 90, 80, 30));
    QGraphicsWidget *quitBtn = this->addWidget(quitbutton);
    quitBtn->setPalette(palette1);
    QObject::connect(quitbutton, &QPushButton::released, this, &Gameplay::quit);

    f.setPointSize(15);
    startBtn->setFont(f);
    quitBtn->setFont(f);

    // connect start button and timer to startGame and advance() respectively
    QObject::connect(startbutton, &QPushButton::released, this, &Gameplay::startGame);
    QObject::connect(ticker, &QTimer::timeout, this, &QGraphicsScene::advance);
}

void Gameplay::startGame() {
    QFont f;
    f.setPointSize(20);
    respawnrate = 6000;

    player = new Player(this->width() / 2 - 4, this->height() / 2 - 12, 10);
    addItem(player);


#ifdef __APPLE__
#undef OFFSET
#define OFFSET 25
#endif

    // score text
    points = 0;
    score_text = new QGraphicsTextItem;
    score_text = addText("SCORE : ");
    score = new QGraphicsTextItem;
    score = this->addText(QString::number(points));
    score_text->setFont(f);
    score->setFont(f);
    score_text->setPos(0 + OFFSET, this->height() - 35);
    score->setPos(100, this->height() - 35);
    score_text->setDefaultTextColor(Qt::white);
    score->setDefaultTextColor(Qt::white);

    timer->restart();

    // health text
    health_text = new QGraphicsTextItem;
    health_text = addText("HEALTH :");
    health = new QGraphicsTextItem;
    health = this->addText(QString::number(player->GetHealth()));
    health_text->setFont(f);
    health->setFont(f);
    health_text->setPos(this->width() - 150, this->height() - 35);
    health->setPos(this->width() - 40 - OFFSET, this->height() - 35);
    health_text->setDefaultTextColor(Qt::white);
    health->setDefaultTextColor(Qt::white);

    // player reload timer
    reload_timer->restart();

    // player invulnerability timer
    invul->restart();

    startbutton->deleteLater();
    quitbutton->deleteLater();
    title_text->deleteLater();

    QObject::connect(ticker, &QTimer::timeout, this, &Gameplay::tick);

}

void Gameplay::tick() {
    // changes the respawn rate every 50 destroyed asteroids
    if (points % 50 == 0) {
        toggle = true;
    }

    if (points % 50 == 1 && respawnrate > 1000 && toggle) {
        respawnrate -= 1000;
        toggle = false;
    }

    // spawn a new asteroid at a rate and amount of asteroids on the screen is less than 100
    if (asteroids.size() <= 100) {
        if (timer->elapsed() >= respawnrate) {
            auto *p = new Asteroid(rand() % 4);
            this->addItem(p);
            asteroids.emplace_back(p);
            timer->restart();
        }
    }

    // player-asteroid collision
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
                double randomangle1 = 0;
                double randomangle2 = 0;

                randomangle1 = rand() % 361;
                randomangle2 = randomangle1 + 180;

                if (asteroids[i]->GetSize() != 40) {
                    Asteroid *new_stroid1 = new Asteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), randomangle1,
                                                         asteroids[i]->GetSize() - 10);
                    Asteroid *new_stroid2 = new Asteroid(asteroids[i]->GetX(), asteroids[i]->GetY(), randomangle2,
                                                         asteroids[i]->GetSize() - 10);
                    asteroids.emplace_back(new_stroid1);
                    asteroids.emplace_back(new_stroid2);
                    addItem(new_stroid1);
                    addItem(new_stroid2);
                }

                removeItem(bullets[j]);
                removeItem(asteroids[i]);

                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]), bullets.end());
                asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids[i]),
                                asteroids.end());

                points++;
                score->setPlainText(QString::number(points));
            }
        }
    }

    if (player->GetHealth() <= 0) {
        endGameScreen();
        for (Asteroid *&asteroid: asteroids) {
            removeItem(asteroid);
        }
        asteroids.clear();
        removeItem(player);
        delete player;
        disconnect(ticker, &QTimer::timeout, this, &Gameplay::tick);
    }
}

void Gameplay::endGameScreen() {
#ifdef __APPLE__
#undef OFFSET
#define OFFSET 50
#endif

    score->deleteLater();
    health->deleteLater();
    score_text->deleteLater();
    health_text->deleteLater();

    QFont f;
    f.setPointSize(60);
    title_text = new QGraphicsTextItem;
    title_text = addText("GAME OVER");
    title_text->setFont(f);
    title_text->setPos(this->width() / 2 - 220 + OFFSET, 60);
    title_text->setDefaultTextColor(Qt::white);

    f.setPointSize(40);

    QPalette palette1;
    palette1.setColor(QPalette::Window, Qt::black);

    startbutton = new QPushButton("PLAY AGAIN");
    startbutton->setGeometry(QRect(this->width() / 2 - 80, this->height() / 2 + 30, 160, 30));
    QGraphicsWidget *paBtn = this->addWidget(startbutton);
    paBtn->setPalette(palette1);

    quitbutton = new QPushButton("QUIT");
    quitbutton->setGeometry(QRect(this->width() / 2 - 80, this->height() / 2 + 90, 160, 30));
    QGraphicsWidget *quitBtn = this->addWidget(quitbutton);
    quitBtn->setPalette(palette1);
    QObject::connect(quitbutton, &QPushButton::released, this, &Gameplay::quit);

    f.setPointSize(15);
    paBtn->setFont(f);
    quitBtn->setFont(f);

    QObject::connect(startbutton, &QPushButton::released, this, &Gameplay::startGame);
}


void Gameplay::quit() {
    QApplication::quit();
}

void Gameplay::keyPressEvent(QKeyEvent *event) {
    if (player != nullptr) {
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
}

void Gameplay::keyReleaseEvent(QKeyEvent *event) {
    if (player != nullptr) {
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
}

Gameplay::~Gameplay() {

}

