//
// Created by Marco on 01/07/2017.
//

#ifndef SLIDESHOW_SUBJECT_H
#define SLIDESHOW_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
    virtual void notify() = 0;
};

#endif //SLIDESHOW_SUBJECT_H
