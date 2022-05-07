//
// Created by Harry Shen on 2022-01-01.
//

#ifndef ASTEROIDGAME2_GAMEPLAY_H
#define ASTEROIDGAME2_GAMEPLAY_H

#include <QtWidgets>
#include <vector>
#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"

class Gameplay : public QGraphicsScene {
Q_OBJECT

    QPoint
            mouse_pos;
public:
    Gameplay(QGraphicsScene *parent = nullptr);

    ~Gameplay();

signals:

public
    slots:

    void startGame();

    void endGameScreen();

    void quit();

    virtual void tick();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QTimer *ticker = new QTimer;
    QElapsedTimer *timer = new QElapsedTimer;
    QElapsedTimer *reload_timer = new QElapsedTimer;
    QElapsedTimer *invul = new QElapsedTimer;

    Player *player{};
    std::vector<Asteroid *> asteroids;
    std::vector<Bullet *> bullets;

    QGraphicsTextItem *score{}, *health{};
    QGraphicsTextItem *score_text{}, *health_text{};
    QGraphicsTextItem *title_text;

    QPushButton *startbutton;
    QPushButton *quitbutton;

    int points = 0;

    int respawnrate;

    bool toggle;
};


#endif //ASTEROIDGAME2_GAMEPLAY_H
