//
// Created by Harry Shen on 2022-01-16.
//

#ifndef ASTEROIDGAME2_ASTEROID_H
#define ASTEROIDGAME2_ASTEROID_H


#include <QtWidgets>
#include <time.h>


class Asteroid : public QGraphicsItem {
private:
    bool firstspawned, dummy, invul;
    double x, y, speed;
    double xvel, yvel, angle;
    int size;
    QPixmap image;
    QElapsedTimer time, invultimer;

protected:
    void advance(int step) override;

public:
    Asteroid();

    Asteroid(int pos);

    Asteroid(double x, double y, double angle, int size);

    double GetX() const;

    double GetY() const;

    void SetX(double newX);

    void SetY(double newY);

    bool GetInvul();

    void SetInvul(bool newInvul);

    double GetXVel() const;

    double GetYVel() const;

    void SetXVel(double newXVel);

    void SetYVel(double newYVel);

    bool GetFirstSpawned();

    void SetFirstSpawned(bool change);

    int GetSize() const;

    QPixmap GetImage();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void DrawAsteroid(QPainter &qPainter);

    void MoveAsteroid();
};


#endif //ASTEROIDGAME2_ASTEROID_H
