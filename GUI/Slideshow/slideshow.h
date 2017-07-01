#ifndef SLIDESHOWCONTAINER_H
#define SLIDESHOWCONTAINER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPointer>
#include "Playlist.h"
#include "SlideshowTimer.h"

namespace Ui {
class Slideshow;
}

class Slideshow : public QWidget
{
    Q_OBJECT

public:
    explicit Slideshow(QWidget *parent = 0);
    ~Slideshow();

    bool setSceneRect(const QRectF& rectF) {
        if(scene->sceneRect() != rectF) {
            scene->setSceneRect(rectF);
            return true;
        }
        return false;
    }

private slots:
    void browse(); // browse disk to select images folder
    void setPlaylist(const QString &text) throw(std::runtime_error); // prepare playlist to be shown
    void displayImage(); // function called on timer event

private:
    void startSlideshow(); // start the slideshow
    void setNextImage(); // set the playlist to the next image
    Ui::Slideshow *ui;
    int playerMinDimension; // GraphicsView min dimension useful to resize images
    QPointer<QGraphicsScene> scene; // GraphicsScene to display images (smart pointer)
    Playlist playlist; // structure containing images and useful information
    SlideshowTimer slideshowTimer; // structure containing timer and its properties
};

#endif // SLIDESHOWCONTAINER_H
