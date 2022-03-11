#include <QApplication>
#include "Frame.h"

int main(int argc, char **argv) {
    QApplication app{argc, argv};
    Frame f;
    QGraphicsView view(&f);
    view.setBackgroundBrush(QPixmap("background.png").scaled(600,400,Qt::IgnoreAspectRatio));
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Asteroid Game 2"));
    view.resize(640, 480);
    view.show();

    return app.exec();
}