//
// Structure containing images and useful information.
//

#ifndef SLIDESHOW_PLAYLIST_H
#define SLIDESHOW_PLAYLIST_H

#include <QtWidgets/QGraphicsPixmapItem>
#include <vector>
#include <memory>

struct Playlist {
    Playlist() : imagesCount(0) {}

    std::vector<std::shared_ptr<QGraphicsPixmapItem>> images; // vector of images in input directory (smart pointer)
    int imagesCount; // number of images in input directory
};

#endif //SLIDESHOW_PLAYLIST_H
