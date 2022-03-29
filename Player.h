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
    double angle, speed;
    int size, health;
    QPixmap image;
    bool wKey, sKey, aKey, dKey;
    bool hit;
    QElapsedTimer *timer;

public slots:

protected:
    void advance(int step) override;

public:
    Player();

    Player(double x, double y, int health);

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

    void SetImage(QString imageName);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void MovePlayer();

    void SetKey(int keyVal, bool newState);
};


#endif //ASTEROIDGAME2_PLAYER_H
