//
// Container for slideshow dots indicator.
//

#include "dotscontainer.h"

DotsContainer::DotsContainer(QWidget *parent) : QWidget(parent) {}

DotsContainer::~DotsContainer() {
}

void DotsContainer::setDots(const Slideshow* slideshow, const int &imgNumber) {
    dots.clear();
    QHBoxLayout* layout = slideshow->findChild<DotsContainer*>("dotsContainer")->findChild<QHBoxLayout*>("horizontalLayout");
    for(int i=0;i<imgNumber;i++) {
        dots.push_back(std::make_shared<QRadioButton>(""));
        layout->insertWidget(i+1,dots[i].get());
    }
    QRadioButton* firstDot = dynamic_cast<QRadioButton*>(dots[0].get());
    if(firstDot)
        firstDot->setChecked(true);
}
