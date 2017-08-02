#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointer>
#include <QDebug>
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

    const Playlist* getPlaylist() const {
        return playlist;
    }

    void startSlideshow(Playlist* playlist) throw(std::invalid_argument); // start the slideshow
    void startSlideshow() throw(std::invalid_argument); // start the timer
    void stopSlideshow(); // stop the timer
    void setSlideshowTimer(int interval); // set the timer interval

    virtual void subscribe(Observer *o) override;
    virtual void unsubscribe(Observer *o) override;
    virtual void notify() override;

public slots:
    void displayImage(); // function called on timer event
    void showNextImage(); // show the next image in the playlist
    void showPreviousImage(); // show the previous image in the playlist

private:
    void setNextImage() const; // set the playlist to the next image
    QPointer<QGraphicsScene> scene; // GraphicsScene to display images (smart pointer)
    Playlist* playlist;
    SlideshowTimer slideshowTimer; // structure containing timer and its properties
    std::list<Observer*> observers;
};

#endif // IMAGEVIEW_H
