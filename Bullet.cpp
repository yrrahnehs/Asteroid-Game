//
// Created by Harry Shen on 2022-02-16.
//

#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(double x, double y, double angle) {
    this->x = x;
    this->y = y;
    this->size = 10;
    this->angle = angle;
    this->speed = 9;
    setPos(GetX(), GetY());
}

double Bullet::GetX() const {
    return this->x;
}

double Bullet::GetY() const {
    return this->y;
}

void Bullet::SetX(double newX) {
    this->x = newX;
}

void Bullet::SetY(double newY) {
    this->y = newY;
}

double Bullet::GetSpeed() const {
    return this->speed;
}

void Bullet::SetSpeed(double newSpeed) {
    this->speed = newSpeed;
}

double Bullet::GetAngle() {
    return this->angle;
}

void Bullet::SetAngle(double newAngle) {
    this->angle = newAngle;
}

bool Bullet::InFrame() {
    return (GetX() + 2 > 0 && GetX()  - 4 < 640 && GetY() - 10 > 0 &&
            GetY() + 10 < 480);
}

QRectF Bullet::boundingRect() const {
    QRectF hitbox = QRectF(GetX(), GetY(), this->size - 12, this->size - 6);
    hitbox.translate(-GetX() - (this->size - 12) / 2, -GetY() - (this->size - 6) / 2);
    return hitbox;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QColor yellow("#f0d048");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(yellow, style);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);


    QRectF b = QRectF(GetX(), GetY(), this->size/2, this->size);
    painter->rotate(GetAngle());
    b.translate(-GetX()-this->size/4,-GetY() - this->size/2);
    painter->drawEllipse(b);


//    QPen pen = QPen(Qt::white);
//    Qt::BrushStyle style1 = Qt::NoBrush;
//    QBrush brush1(Qt::white, style1);
//    painter->setPen(pen);
//    painter->setBrush(brush1);
//
//    QRectF hitbox = QRectF(GetX(), GetY(), this->size/2, this->size);
//    hitbox.translate(-GetX()-this->size/4,-GetY() - this->size/2);
//    painter->drawRect(hitbox);

}

void Bullet::advance(int step) {
    if (!step) {
        return;
    }
    MoveBullet();
}

void Bullet::MoveBullet() {
    SetY(GetY() - (GetSpeed() * cos(qDegreesToRadians(angle))));
    SetX(GetX() + (GetSpeed() * sin(qDegreesToRadians(angle))));
    setPos(GetX(), GetY());
}
