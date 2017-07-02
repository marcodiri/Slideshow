#include "ImageView.h"

ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(parent)),
    playlist(nullptr)
{
    connect(&slideshowTimer.timer, &QTimer::timeout, this, &ImageView::displayImage); // connect changes in comboBox with displayPlaylist() function passing its text
    setScene(scene); // connect GraphicsView to GraphicsScene
}

ImageView::~ImageView() {
}

void ImageView::stopSlideshow() {
    slideshowTimer.timer.stop();
}

void ImageView::displayImage() {
    // display image in GraphicsView
    playlist->images[playlist->currentImage].get()->setVisible(false); // hide previous image
    setNextImage();
    scene->setSceneRect(playlist->images[playlist->currentImage].get()->boundingRect()); // adjust scene dimension to fit current image
    playlist->images[playlist->currentImage].get()->setVisible(true); // show current image
    notify();
}

void ImageView::startSlideshow(Playlist* playlist) throw(std::invalid_argument) {
    if(playlist) {
        setPlaylist(playlist);
        scene->clear();
        playlist->currentImage = 0;
        auto firstImg = playlist->images[playlist->currentImage].get();
        for (auto itr = playlist->images.begin(); itr != playlist->images.end(); itr++)
            scene->addItem((*itr).get());
        scene->setSceneRect(firstImg->boundingRect());
        firstImg->setVisible(true);
        notify();
    }
    if(this->playlist)
        slideshowTimer.timer.start(slideshowTimer.timerInterval);
    else
        throw std::invalid_argument("Error calling startSlideshow(): passed argument is null");
}

void ImageView::startSlideshow() throw(std::invalid_argument) {
    if(this->playlist)
        slideshowTimer.timer.start(slideshowTimer.timerInterval);
    else
        throw std::invalid_argument("Error calling startSlideshow(): playlist is not set, provide playlist address as function argument");
}

void ImageView::setNextImage() const {
    playlist->currentImage++;
    if(playlist->currentImage >= playlist->imagesCount)
        playlist->currentImage = 0;
}

void ImageView::showNextImage() {
    if(slideshowTimer.timer.isActive()) {
        stopSlideshow();
        displayImage();
        startSlideshow();
    }
}

void ImageView::showPreviousImage() {
    if(slideshowTimer.timer.isActive()) {
        stopSlideshow();
        playlist->images[playlist->currentImage].get()->setVisible(false); // hide previous image
        playlist->currentImage--;
        if (playlist->currentImage < 0)
            playlist->currentImage = playlist->imagesCount - 1;
        scene->setSceneRect(
                playlist->images[playlist->currentImage].get()->boundingRect()); // adjust scene dimension to fit current image
        playlist->images[playlist->currentImage].get()->setVisible(true); // show current image
        notify();
        startSlideshow();
    }
}

void ImageView::subscribe(Observer *o) {
    observers.push_back(o);
}

void ImageView::unsubscribe(Observer *o) {
    observers.remove(o);
}

void ImageView::notify() {
    for(auto itr=observers.begin(); itr!=observers.end(); itr++)
    (*itr)->update();
}
