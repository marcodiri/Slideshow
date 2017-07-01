//
// Container for slideshow dots indicator.
//

#include "DotsContainer.h"

DotsContainer::DotsContainer(QWidget *parent, ImageView* view) : QWidget(parent), imageView(view) {}

DotsContainer::~DotsContainer() {
    imageView->unsubscribe(this);
}

void DotsContainer::setDots(const Slideshow* slideshow, const int &imgNumber) {
    dots.clear();
    QHBoxLayout* layout = slideshow->findChild<DotsContainer*>("dotsContainer")->findChild<QHBoxLayout*>("horizontalLayout");
    for(int i=0;i<imgNumber;i++) {
        dots.push_back(std::make_shared<QRadioButton>(""));
        layout->insertWidget(i+1,dots[i].get());
    }
}

void DotsContainer::checkDot(const int &index) {
    QRadioButton* dot = dynamic_cast<QRadioButton*>(dots[index].get());
    if(dot)
        dot->setChecked(true);
}

void DotsContainer::update() {
    checkDot(imageView->getCurrentImage());
}
