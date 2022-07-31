#include <QApplication>
#include "Gameplay.h"

class Gameplay;

int main(int argc, char **argv) {
    QApplication app{argc, argv};
    Gameplay g;
    QGraphicsView view(&g);
    app.setWindowIcon(QIcon("images/asteroid.ico"));
    view.setBackgroundBrush(QPixmap("images/background.png").scaled(640,480,Qt::KeepAspectRatioByExpanding));
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Asteroid Game"));
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(640, 480);
    view.show();
    return app.exec();
}
