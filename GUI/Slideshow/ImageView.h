#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointer>
#include "Playlist.h"
#include "SlideshowTimer.h"

class ImageView : public QGraphicsView
{
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();

    void setPlaylist(Playlist* playlist) {
        this->playlist = playlist;
    }

    void startSlideshow(Playlist& playlist); // start the slideshow
    void stopSlideshow(); // stop the timer if running
    void setNextImage() const; // set the playlist to the next image
    SlideshowTimer slideshowTimer; // structure containing timer and its properties

public slots:
    void displayImage(); // function called on timer event

private:
    QPointer<QGraphicsScene> scene; // GraphicsScene to display images (smart pointer)
    Playlist* playlist;
};

#endif // IMAGEVIEW_H
