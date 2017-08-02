//
// Created by Marco on 02/08/2017.
//

#ifndef SLIDESHOW_IMAGEDIR_H
#define SLIDESHOW_IMAGEDIR_H


#include <QtWidgets/QLabel>
#include "../../Observer.h"
#include "ImageView.h"

class ImagePath : public QLabel, public Observer {
public:
    explicit ImagePath(QWidget* parent=nullptr, ImageView* view=nullptr);
    virtual ~ImagePath() override;

    void setImageView(ImageView *imageView) {
        this->imageView = imageView;
        imageView->subscribe(this);
    }

    void setLabelText(const QString& text); // change this label text

    void update() override;

private:
    ImageView* imageView;
};


#endif //SLIDESHOW_IMAGEDIR_H
