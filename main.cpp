#include <QApplication>
#include "Frame.h"

int main(int argc, char **argv) {
    QApplication app{argc, argv};
    Frame f;
    QGraphicsView view(&f);
    view.setBackgroundBrush(QPixmap("images/background.png").scaled(640,480,Qt::KeepAspectRatioByExpanding));
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Asteroid Game 2"));
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(640, 480);
    view.show();

    return app.exec();
}