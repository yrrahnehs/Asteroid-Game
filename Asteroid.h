//
// Created by Harry Shen on 2022-01-16.
//

#ifndef ASTEROIDGAME2_ASTEROID_H
#define ASTEROIDGAME2_ASTEROID_H


#include <QtWidgets>
#include <time.h>


class Asteroid : public QGraphicsItem {
private:
    bool firstspawned, dummy;
    double x, y;
    double xvel, yvel;
    int size;
    QPixmap image;
    QElapsedTimer time;

protected:
    void advance(int step) override;

public:
    Asteroid();

    Asteroid(int pos);

    double GetX() const;

    double GetY() const;

    void SetX(double newX);

    void SetY(double newY);

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
