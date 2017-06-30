//
// Utility functions.
//

#ifndef SLIDESHOW_UTILS_H
#define SLIDESHOW_UTILS_H

#include <QtCore/QDir>

// retrieve images in the given folder and return a list of them
const QFileInfoList getImagesInFolder(const QString &dir) {
    QDir directory(dir);
    return directory.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.bmp" << "*.xpm", QDir::NoDotAndDotDot|QDir::Files); // get number of images in folder
}

#endif //SLIDESHOW_UTILS_H
