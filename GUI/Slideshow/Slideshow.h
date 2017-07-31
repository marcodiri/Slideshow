#ifndef SLIDESHOWCONTAINER_H
#define SLIDESHOWCONTAINER_H

#include <QWidget>
#include "Playlist.h"

namespace Ui {
class Slideshow;
}

class Slideshow : public QWidget {
    Q_OBJECT

public:
    explicit Slideshow(QWidget *parent = 0);
    virtual ~Slideshow() override;

private slots:
    void browse(); // browse disk to select images folder
    void setPlaylist(const QString &text) throw(std::runtime_error); // prepare playlist to be shown

private:
    Ui::Slideshow *ui;
    Playlist playlist; // structure containing images and useful information
    int playerMinDimension; // GraphicsView min dimension useful to resize images
};

#endif // SLIDESHOWCONTAINER_H
