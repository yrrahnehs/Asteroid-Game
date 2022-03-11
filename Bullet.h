//
// Created by Harry Shen on 2022-02-16.
//

#ifndef ASTEROIDGAME2_BULLET_H
#define ASTEROIDGAME2_BULLET_H

#include <QtWidgets>


class Bullet : public QGraphicsItem {

private:
    double x, y, angle;
    double speed;
    int size;
    QElapsedTimer time;

public slots:

protected:
    void advance(int step) override;

public:
    Bullet();

    Bullet(double x, double y, double angle);

    double GetX() const;

    double GetY() const;

    void SetX(double newX);

    void SetY(double newY);

    double GetSpeed() const;

    void SetSpeed(double newSpeed);

    double GetAngle();

    void SetAngle(double newAngle);

    bool InFrame();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void MoveBullet();
};


#endif //ASTEROIDGAME2_BULLET_H
