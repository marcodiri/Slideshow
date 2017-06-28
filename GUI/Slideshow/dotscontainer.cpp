//
// Created by Marco on 27/06/2017.
//

#include "dotscontainer.h"

DotsContainer::DotsContainer(QWidget *parent) : QWidget(parent) {}

DotsContainer::~DotsContainer() {
    for(auto itr = dots.begin(); itr != dots.end(); itr++){
        delete *itr;
        *itr = 0;
    }
}

void DotsContainer::setDots(const Slideshow* slideshow, const int &imgNumber) {
    QHBoxLayout* layout = slideshow->findChild<DotsContainer*>("dotsContainer")->findChild<QHBoxLayout*>("horizontalLayout");
    for(int i=0;i<imgNumber;i++) {
        dots.push_back(new QRadioButton(""));
        layout->insertWidget(i+1,dots[i]);
    }
    auto z = dynamic_cast<QRadioButton*>(dots[0]);
    if(z)
        z->setChecked(true);
}
