#include "Slideshow.h"
#include "ui_slideshow.h"
#include "Utils.h"

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow)
{
    ui->setupUi(this);
    int playerWidth = ui->imageView->width(), playerHeight = ui->imageView->height();
    playerMinDimension = (playerWidth < playerHeight ? playerWidth : playerHeight)-2; // -2 not to count the borders
    ui->dotsContainer->setEnabled(false); // disable the indicators checkbox, enable if you want to change image clicking on the indicators (not implemented yet)
    ui->dotsContainer->setImageView(ui->imageView); // setup Observer
    ui->imgPath->setImageView(ui->imageView); // setup Observer

    connect(ui->browseBtn, &QAbstractButton::clicked, this, &Slideshow::browse); // connect browse button click with browse() function
    connect(ui->dirBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &Slideshow::setPlaylist); // connect changes in comboBox with displayPlaylist() function passing its text
    connect(ui->moveBtnForward, &QAbstractButton::clicked, ui->imageView, &ImageView::showNextImage); // connect moveForward button with the imageView
    connect(ui->moveBtnBackward, &QAbstractButton::clicked, ui->imageView, &ImageView::showPreviousImage); // connect moveBackward button with the imageView
}

Slideshow::~Slideshow() {
    delete ui;
}

void Slideshow::browse() {
    ui->imageView->stopSlideshow(); // stop slideshow if running // FIXME: resume if directory is empty and a slideshow was running
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Choose images directory"), QDir::homePath()));
    if(getImagesInFolder(directory).count()) { // check for empty directory
        if (!directory.isEmpty()) {
            if (ui->dirBox->findText(directory) == -1) // check if directory was already present in comboBox
                ui->dirBox->addItem(directory);
            ui->dirBox->setCurrentIndex(ui->dirBox->findText(directory));
        }
    } else {
        QMessageBox::information(
                this,
                tr("Slideshow"),
                tr("Directory does not contain images and was not added."));
    }
}

void Slideshow::setPlaylist(const QString &text) throw(std::runtime_error) {
    ui->imageView->stopSlideshow(); // stop slideshow if running
    if(!playlist.images.empty()) { // check if vector was already allocated, if so clear it
        playlist.images.clear();
    }
    qInfo() << "Scanning directory: " + text;
    playlist.imagesList = getImagesInFolder(text); // get images list
    QListIterator<QFileInfo> itr(playlist.imagesList); // iterate images list
    QString imageDir;
    QPixmap img;
    while(itr.hasNext()) {
        imageDir = itr.next().absoluteFilePath(); // get image absolute path
        qInfo() << "Adding file: " + imageDir;
        try {
            img = QPixmap(imageDir).scaledToHeight(playerMinDimension);
            if(!img.isNull()) {
                playlist.images.push_back(std::make_shared<QGraphicsPixmapItem>(img)); // create a new GraphicsPixmapItem for each file and push it in images vector (smart pointer)
                playlist.images.back()->setVisible(false); // hide every item
            }
            else
                "Missing file "+imageDir.toStdString()+" or image is too large";
        } catch(std::bad_alloc& e) {
            qCritical() << "Error allocating file " + imageDir;
        } catch(std::exception& e) {
            qCritical() << "Error at file " + imageDir;
            qCritical() << e.what();
        }
    }
    playlist.imagesCount = playlist.images.size(); // get number of images in the list
    ui->imgCount->setText((QString::number(playlist.imagesCount)));

    ui->dotsContainer->setDots(this, playlist.imagesCount); // set image indicators
    try {
        ui->imageView->startSlideshow(&playlist);
    } catch (std::invalid_argument& e) {
        qDebug() << e.what();
    }
}
