//
// Created by Harry Shen on 2022-01-19.
//

#ifndef ASTEROIDGAME2_PLAYER_H
#define ASTEROIDGAME2_PLAYER_H

#include <QtWidgets>
#include <iostream>

class Player : public QGraphicsItem{

private:
    double x, y;
    double angle = 0;
    double speed = 1.7;
    int size = 30;
    int health;
    QPixmap image;
    bool wKey = false;
    bool sKey = false;
    bool aKey = false;
    bool dKey = false;
    bool hit = false;
    QElapsedTimer *timer;

public slots:

protected:
    void advance(int step) override;

public:
    Player();

    Player(double x, double y, int health);

    ~Player();

    double GetX() const;

    double GetY() const;

    void SetX(double newX);

    void SetY(double newY);

    double GetSpeed() const;

    double GetAngle();

    void SetAngle(double newAngle);

    void SetSpeed(double newSpeed);

    void SetHit(bool newHit);

    int GetHealth();

    void SetHealth(int newHealth);

    bool InFrame(double offsetx, double offsety);

    QPixmap GetImage();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void MovePlayer();

    void SetKey(int keyVal, bool newState);
};


#endif //ASTEROIDGAME2_PLAYER_H
