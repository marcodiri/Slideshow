//
// Created by Marco on 30/06/2017.
//

#ifndef SLIDESHOW_SLIDESHOWTIMER_H
#define SLIDESHOW_SLIDESHOWTIMER_H

#include <QtCore/QBasicTimer>

struct SlideshowTimer {
    explicit SlideshowTimer(int t=5000) : timerInteval(t) {}

    QBasicTimer timer;
    int timerInteval;
};

#endif //SLIDESHOW_SLIDESHOWTIMER_H
