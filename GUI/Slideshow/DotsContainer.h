//
// Container for slideshow dots indicator.
//

#ifndef SLIDESHOWWINDOWS_DOTSCONTAINER_H
#define SLIDESHOWWINDOWS_DOTSCONTAINER_H


#include <QtWidgets>
#include "Slideshow.h"
#include "../../Observer.h"
#include "ImageView.h"

class DotsContainer : public QWidget, public Observer {
public:
    explicit DotsContainer(QWidget* parent=0, ImageView* view=0);
    ~DotsContainer();

    void setImageView(ImageView *imageView) {
        this->imageView = imageView;
        imageView->subscribe(this);
    }

    void setDots(const Slideshow* slideshow, const int &imgNumber);

    void update() override;

private:
    void checkDot(const int& index);
    std::vector<std::shared_ptr<QWidget>> dots;
    ImageView* imageView;
};


#endif //SLIDESHOWWINDOWS_DOTSCONTAINER_H
