//
// Structure containing images and useful information.
//

#ifndef SLIDESHOW_PLAYLIST_H
#define SLIDESHOW_PLAYLIST_H

#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QFileInfo>
#include <vector>
#include <memory>

struct Playlist {
    std::vector<std::shared_ptr<QGraphicsPixmapItem>> images {}; // vector of images in input directory (smart pointer)
    QFileInfoList imagesList; // images data
    int currentImage = 0;
    int imagesCount = 0; // number of images in input directory
};

#endif //SLIDESHOW_PLAYLIST_H
