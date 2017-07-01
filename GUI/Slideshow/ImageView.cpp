#include "ImageView.h"

ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(parent))
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

void ImageView::startSlideshow(Playlist& playlist) {
    setPlaylist(&playlist);
    scene->clear();
    playlist.currentImage = 0;
    auto firstImg = playlist.images[playlist.currentImage].get();
    for(auto itr=playlist.images.begin(); itr!=playlist.images.end(); itr++)
        scene->addItem((*itr).get());
    scene->setSceneRect(firstImg->boundingRect());
    firstImg->setVisible(true);
    notify();
    slideshowTimer.timer.start(slideshowTimer.timerInterval);
}

void ImageView::setNextImage() const {
    playlist->currentImage++;
    if(playlist->currentImage >= playlist->imagesCount)
        playlist->currentImage = 0;
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
