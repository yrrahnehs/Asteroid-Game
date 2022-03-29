//
// Created by Harry Shen on 2022-01-19.
//

#include "Player.h"
#include <iostream>

Player::Player() {}

Player::Player(double x, double y, int health) {
    this->image.load("images/Player.png");
    this->x = x;
    this->y = y;
    this->health = health;
    this->size = 30;
    this->angle = 0;
    this->speed = 1.7;
    this->hit = false;

    wKey = false;
    sKey = false;
    aKey = false;
    dKey = false;

    timer = new QElapsedTimer;
    timer->start();
}

double Player::GetX() const {
    return this->x;
}

double Player::GetY() const {
    return this->y;
}

void Player::SetX(double newX) {
    this->x = newX;
}

void Player::SetY(double newY) {
    this->y = newY;
}


double Player::GetSpeed() const {
    return this->speed;
}

void Player::SetSpeed(double newSpeed) {
    this->speed = newSpeed;
}

int Player::GetHealth() {
    return this->health;
}

bool Player::InFrame(double offsetx, double offsety) {
    return (GetX() - 9 > 0 - offsetx && GetX() + 9 < 640 + offsetx && GetY() - 12 > 0 - offsety &&
            GetY() + 12 < 480 + offsety);
}

void Player::SetHealth(int newHealth) {
    this->health = newHealth;
}

void Player::SetHit(bool newHit) {
    this->hit = newHit;
}

double Player::GetAngle() {
    return this->angle;
}

void Player::SetAngle(double newAngle) {
    this->angle = newAngle;
}

QPixmap Player::GetImage() {
    return this->image;
}

void Player::SetImage(QString imageName) {
    this->image.load(imageName);
}

QRectF Player::boundingRect() const {
    QRectF hitbox = QRectF(GetX(), GetY(), this->size - 12, this->size - 6);
    hitbox.translate(-GetX() - (this->size - 12) / 2, -GetY() - (this->size - 6) / 2);
    return hitbox;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *qStyleOptionGraphicsItem, QWidget *qWidget) {
    QPixmap newPixmap = GetImage().scaled(this->size, this->size);

    painter->rotate(GetAngle());

    if (this->hit) {
        if (timer->elapsed() <= 250) {
            painter->setOpacity(0.5);
        }
        if (timer->elapsed() > 250) {
            painter->setOpacity(1);
        }
        if (timer->elapsed() >= 500) {
            timer->restart();
        }
    }

    painter->drawPixmap(QPoint(-this->size / 2, -this->size / 2), newPixmap);


//    QRectF hitbox = QRectF(GetX(), GetY(), this->size - 12, this->size - 6);
//    hitbox.translate(-GetX() - (this->size - 12) / 2, -GetY() - (this->size - 6) / 2);
//    painter->drawRect(hitbox);
}

void Player::advance(int step) {
    if (!step) {
        return;
    }
    MovePlayer();
}

void Player::MovePlayer() {

    if (InFrame(0, 0)) {
        if (wKey) {
            SetY(GetY() - (GetSpeed() * cos(qDegreesToRadians(angle))));
            SetX(GetX() + (GetSpeed() * sin(qDegreesToRadians(angle))));
        }

        if (aKey) {
            SetAngle(GetAngle() - 3.5);
        }
        if (dKey) {
            SetAngle(GetAngle() + 3.5);
        }
    }

    if (InFrame(0, 0)) {
        if (sKey) {
            SetY(GetY() + (cos(qDegreesToRadians(angle))));
            SetX(GetX() - (sin(qDegreesToRadians(angle))));
        }
    } else {
        if (GetY() - 12 < 0) {
            SetY(GetY() + 17);
        }

        if (GetY() + 12 > 480) {
            SetY(GetY() - 17);
        }

        if (GetX() - 12 < 0) {
            SetX(GetX() + 17);
        }
        if (GetX() + 12 > 640) {
            SetX(GetX() - 17);
        }
    }

    setPos(GetX(), GetY());
    update();
}

void Player::SetKey(int keyVal, bool newState) {
    switch (keyVal) {
        case 0:
            wKey = newState;
            break;
        case 1:
            aKey = newState;
            break;
        case 2:
            sKey = newState;
            break;
        case 3:
            dKey = newState;
            break;
    }
}
