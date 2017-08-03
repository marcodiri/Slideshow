//
// Created by Marco on 02/08/2017.
//

#include "ImagePath.h"

ImagePath::ImagePath(QWidget *parent, ImageView *view) : QLabel(parent), imageView(view) {}

ImagePath::~ImagePath() {
    imageView->unsubscribe(this);
}

void ImagePath::setLabelText(const QString &text) {
    setText(text);
}

void ImagePath::update() {
    QString imgPath = imageView->getPlaylist()->imagesList[imageView->getPlaylist()->currentImage].fileName(); // get current image file path
    setLabelText(imgPath);
}
