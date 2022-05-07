//
// Created by Harry Shen on 2022-01-16.
//

#ifndef ASTEROIDGAME2_ASTEROID_H
#define ASTEROIDGAME2_ASTEROID_H


#include <QtWidgets>
#include <ctime>


class Asteroid : public QGraphicsItem {
private:
    bool firstspawned, invul;
    double x, y, speed;
    double angle;
    int size;
    QPixmap image;
    QElapsedTimer time, invultimer;

protected:
    void advance(int step) override;

public:
    Asteroid();

    Asteroid(int pos);

    Asteroid(double x, double y, double angle, int size);

    ~Asteroid();

    double GetX() const;

    double GetY() const;

    void SetX(double newX);

    void SetY(double newY);

    bool GetInvul();

    void SetInvul(bool newInvul);

    bool GetFirstSpawned();

    void SetFirstSpawned(bool change);

    int GetSize() const;

    QPixmap GetImage();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void MoveAsteroid();
};


#endif //ASTEROIDGAME2_ASTEROID_H
