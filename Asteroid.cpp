//
// Created by Harry Shen on 2022-01-16.
//

#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid() {}

Asteroid::Asteroid(int start) {
    time.restart();
    image.load("asteroid.png");

    srand(std::time(nullptr));

    int randomnumber = rand() % 9 + 1;

    // randomly generate asteroid size
    if (randomnumber < 3) {
        this->size = 60;
    } else if (randomnumber > 5) {
        this->size = 40;
    } else {
        this->size = 50;
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
    }

    setPos(this->x, this->y);

    // randomly generate a x and y velocity
    double randomspeedx, randomspeedy;
    randomspeedx = (QRandomGenerator().generateDouble() * 1.5) + 0.1;
    randomspeedy = (QRandomGenerator().generateDouble() * 1.5) + 0.1;

    // velocity based off of where asteroid spawns
    if (start == 1) {
        randomspeedx = -randomspeedx;
    }
    if (start == 2) {
        randomspeedy = -randomspeedy;
    }

    // velocity of y and x based off of a random number
    int random_0_or_1 = rand() % 2;

    // if the asteroid spawns on the left or right side
    if (start == 1 || start == 3) {
        // if y position is more than 75% of the screen height
        // and velocity is positive, change to negative
        if (this->y >= (480 * 0.75) && randomspeedy > 0) {
            randomspeedy = -randomspeedy;
        }
        // if y position is less than 25% of the screen height
        // and velocity is negative, change to positive
        if (this->y <= (480 * 0.25) && randomspeedy < 0) {
            randomspeedy = -randomspeedy;
        }
        // if y position is in between 25% and 75%
        // 50/50 to go up or down
        if (this->y > (480 * 0.25) && this->y < (480 * 0.75)){
            if (random_0_or_1 == 1) {
                randomspeedy = -randomspeedy;
            }
        }
    }
    // if the asteroid spawns on the top or bottom side
    if (start == 0 || start == 2) {
        // if x position is more than 75% of the screen width
        // and velocity is positive, change to negative
        if (this->x >= (640 * 0.75) && randomspeedx > 0) {
            randomspeedx = -randomspeedx;
        }
        // if x position is less than 25% of the screen width
        // and velocity is negative, change to positive
        if (this->x <= (640 * 0.25) && randomspeedx < 0) {
            randomspeedx = -randomspeedx;
        }
        // if x position is in between 25% and 75%
        // 50/50 to go left or right
        if (this->x > (640 * 0.25) && this->x < (640 * 0.75)){
            if (random_0_or_1 == 1) {
                randomspeedx = -randomspeedx;
            }
        }
    }
    this->xvel = randomspeedx;
    this->yvel = randomspeedy;
    this->firstspawned = true;
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

double Asteroid::GetXVel() const {
    return this->xvel;
}

double Asteroid::GetYVel() const {
    return this->yvel;
}

void Asteroid::SetXVel(double newXVel) {
    this->xvel = newXVel;
}

void Asteroid::SetYVel(double newYVel) {
    this->yvel = newYVel;
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
    QRectF hitbox = QRectF(GetX(), GetY(), GetSize(), GetSize());
    hitbox.translate(-GetX() - GetSize() / 2, -GetY() - GetSize() / 2);
    return hitbox;
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    auto newPixmap = GetImage().scaled(GetSize(), GetSize());
    painter->drawPixmap(QPoint(-GetSize() / 2, -GetSize() / 2), newPixmap);

//    QRectF hitbox = QRectF(GetX(), GetY(), GetSize(), GetSize());
//    hitbox.translate(-GetX() - GetSize() / 2, -GetY() - GetSize() / 2);
//    painter->drawRect(hitbox);
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
    SetX(GetX() + GetXVel());
    SetY(GetY() + GetYVel());

    // set firstspawned to false after it appears on screen
    if (GetX() > 0 && GetX() < 640 && GetY() > 0 && GetY() < 480) {
        this->firstspawned = false;
    }

    if (!firstspawned) {
        if (GetX() - GetSize() / 2 > 650 && GetXVel() > 0) {
            SetX(-GetSize() / 2);
        }

        if (GetX() + GetSize() / 2 < 0 && GetXVel() < 0) {
            SetX(650 + GetSize() / 2);
        }

        if (GetY() - GetSize() / 2 > 490 && GetYVel() > 0) {
            SetY(-GetSize() / 2);
        }

        if (GetY() + GetSize() / 2 < 0 && GetYVel() < 0) {
            SetY(490 + GetSize() / 2);
        }
    }
    if (dummy) {
        if (GetX() > 100 || GetX() < -100) {
            SetXVel(GetXVel() * -1);
        }
    }

    setPos(GetX(), GetY());
}
