#include "slideshow.h"
#include "SlideshowDebug/ui_slideshow.h"

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    connect(ui->browseBtn, &QAbstractButton::clicked, this, &Slideshow::browse); // connect browse button click with browse function
}

Slideshow::~Slideshow()
{
    delete ui;
}

void Slideshow::showEvent(QShowEvent *event) {
    ui->imageView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio); // fitInView has to be called after the object shows
}

void Slideshow::resizeEvent(QResizeEvent *event) {
    ui->imageView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio); // fitInView to fit resized window
}

void Slideshow::browse() {
    // browse disk to select images folder
}
