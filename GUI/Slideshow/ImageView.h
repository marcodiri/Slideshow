#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointer>
#include "Playlist.h"
#include "SlideshowTimer.h"
#include "../../Subject.h"

class ImageView : public QGraphicsView, public Subject {
public:
    explicit ImageView(QWidget *parent = 0);
    virtual ~ImageView() override ;

    void setPlaylist(Playlist* playlist) {
        this->playlist = playlist;
    }

    const int& getCurrentImage() const {
        return playlist->currentImage;
    }

    void startSlideshow(Playlist& playlist); // start the slideshow
    void stopSlideshow(); // stop the timer if running
    void setNextImage() const; // set the playlist to the next image
    SlideshowTimer slideshowTimer; // structure containing timer and its properties

    virtual void subscribe(Observer *o) override;

    virtual void unsubscribe(Observer *o) override;

    virtual void notify() override;

public slots:
    void displayImage(); // function called on timer event

private:
    QPointer<QGraphicsScene> scene; // GraphicsScene to display images (smart pointer)
    Playlist* playlist;
    std::list<Observer*> observers;
};

#endif // IMAGEVIEW_H