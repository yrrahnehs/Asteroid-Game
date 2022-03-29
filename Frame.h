//
// Created by Harry Shen on 2022-01-01.
//

#ifndef ASTEROIDGAME2_FRAME_H
#define ASTEROIDGAME2_FRAME_H

#include <QtWidgets>
#include <vector>
#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"

class Frame : public QGraphicsScene {
Q_OBJECT
    QPoint
            mouse_pos;
public:
    Frame(QGraphicsScene *parent = nullptr);

signals:

public
    slots:

    virtual void tick();

protected:
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

private:
    QElapsedTimer *timer;
    QElapsedTimer *reload_timer;
    QElapsedTimer *invul;

    Player *player;
    std::vector<Asteroid *> asteroids;
    std::vector<Bullet *> bullets;
    QPixmap background;

    QGraphicsTextItem *score;

    int points = 0;

    bool spacePressed = false;

    bool wKey, aKey, sKey, dKey;

};


#endif //ASTEROIDGAME2_FRAME_H
