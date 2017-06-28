#ifndef SLIDESHOWCONTAINER_H
#define SLIDESHOWCONTAINER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPointer>
#include <vector>

namespace Ui {
class Slideshow;
}

class Slideshow : public QWidget
{
    Q_OBJECT

public:
    explicit Slideshow(QWidget *parent = 0);
    ~Slideshow();

    const QPointer<QGraphicsScene>& getScene() const {
        return scene;
    }

    void showEvent(QShowEvent *event); // automatically called when instantiated Slideshow shows
    void resizeEvent(QResizeEvent *event); // automatically called when instantiated Slideshow get resized

private slots:
    void browse();

private:
    Ui::Slideshow *ui;
    QPointer<QGraphicsScene> scene; // GraphicsScene to display images (smart pointer)
    std::vector<QGraphicsPixmapItem> playlist; // vector of images in input directory
    unsigned int imagesCount; // number of images in input directory
};

#endif // SLIDESHOWCONTAINER_H
