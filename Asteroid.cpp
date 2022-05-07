//
// Created by Harry Shen on 2022-01-16.
//

#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid() {}

Asteroid::Asteroid(int start) {
    this->invul = true;
    time.restart();
    image.load("images/asteroid.png");

    srand(std::time(nullptr));

    int randomnumber = rand() % 9 + 1;

    // randomly generate asteroid size
    if (randomnumber < 3) {
        this->size = 60;
        this->speed = 0.9;
    } else if (randomnumber > 5) {
        this->size = 40;
        this->speed = 1.5;
    } else {
        this->size = 50;
        this->speed = 1.2;
    }

    // starting asteroid spawn position
    switch (start) {
        case 0:
            this->y = 0 - this->size;
            this->x = rand() % (640 - this->size);
            break;
        case 1:
            this->y = rand() % (480 - this->size);
            this->x = 640 + this->size;
            break;
        case 2:
            this->y = 480 + this->size;
            this->x = rand() % (640 - this->size);
            break;
        case 3:
            this->y = rand() % (480 - this->size);
            this->x = (0 - this->size);
            break;
        case 4:
            this->y = -100;
            this->x = -100;
            break;
    }

    setPos(this->x, this->y);

    // randomly generate starting spawn angle
    double random_angle = 0.0;
    if (start == 0) {
        if (this->x < 640.0/2) {
            random_angle = rand() % 81 + 95;
        }
        if (this->x >= 640.0/2) {
            random_angle = rand() % 81 + 185;
        }
    }
    if (start == 1) {
        if (this->y < 480.0/2) {
            random_angle = rand() % 81 + 185;
        }
        if (this->y >= 480.0/2) {
            random_angle = rand() % 81 + 275;
        }
    }
    if (start == 2) {
        if (this->x < 640.0/2) {
            random_angle = rand() % 81 + 5;
        }
        if (this->x >= 640.0/2) {
            random_angle = rand() % 81 + 275;
        }
    }
    if (start == 3) {
        if (this->y < 480.0/2) {
            random_angle = rand() % 86 + 95;
        }
        if (this->y >= 480.0/2) {
            random_angle = rand() % 86 + 5;
        }
    }

    this->angle = random_angle;
    this->firstspawned = true;
    this->invultimer.restart();
}

Asteroid::Asteroid(double x, double y, double angle, int size) {
    this->invul = true;
    time.restart();
    image.load("images/asteroid.png");

    this->angle = angle;
    this->x = x;
    this->y = y;
    this->size = size;
    if (size == 50) {
        this->speed = 1.2;
    }
    if (size == 40) {
        this->speed = 1.5;
    }

    setPos(this->x, this->y);

    this->firstspawned = false;
    this->invultimer.restart();
}

double Asteroid::GetX() const {
    return this->x;
}

double Asteroid::GetY() const {
    return this->y;
}

void Asteroid::SetX(double newX) {
    this->x = newX;
}

void Asteroid::SetY(double newY) {
    this->y = newY;
}

bool Asteroid::GetInvul() {
    return this->invul;
}

void Asteroid::SetInvul(bool newInvul) {
    this->invul = newInvul;
}

bool Asteroid::GetFirstSpawned() {
    return this->firstspawned;
}

void Asteroid::SetFirstSpawned(bool change) {
    this->firstspawned = change;
}

int Asteroid::GetSize() const {
    return this->size;
}

QPixmap Asteroid::GetImage() {
    return this->image;
}

QRectF Asteroid::boundingRect() const {
    QRectF hitbox = QRectF(GetX(), GetY(), GetSize()-10, GetSize()-10);
    hitbox.translate(-GetX() - GetSize() / 2+7, -GetY() - GetSize() / 2+5);
    return hitbox;
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    auto newPixmap = GetImage().scaled(GetSize(), GetSize());
    painter->drawPixmap(QPoint(-GetSize() / 2, -GetSize() / 2), newPixmap);
}

void Asteroid::advance(int step) {
    if (!step) {
        return;
    }
    MoveAsteroid();
}

void Asteroid::MoveAsteroid() {
    // rotation of asteroid
    qreal seconds = ((qreal)(time.elapsed() % 60000)) / 1000;
    setRotation(seconds * 100);

    // asteroid movement
    SetX(GetX() + (this->speed * sin(qDegreesToRadians(angle))));
    SetY(GetY() - (this->speed * cos(qDegreesToRadians(angle))));
    // set firstspawned to false after it appears on screen
    if (GetX() > 0 && GetX() < 640 && GetY() > 0 && GetY() < 480) {
        SetFirstSpawned(false);
    }

    if (!firstspawned) {
        if (GetX() - GetSize() / 2 > 650) {
            SetX(-GetSize() / 2);
        }

        if (GetX() + GetSize() / 2 < 0) {
            SetX(650 + GetSize() / 2);
        }

        if (GetY() - GetSize() / 2 > 490) {
            SetY(-GetSize() / 2);
        }

        if (GetY() + GetSize() / 2 < 0) {
            SetY(490 + GetSize() / 2);
        }
    }

    if (invultimer.elapsed() > 100) {
        SetInvul(false);
    }

    setPos(GetX(), GetY());
}

Asteroid::~Asteroid() = default;
