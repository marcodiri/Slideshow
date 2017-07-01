#include "slideshow.h"
#include "SlideshowDebug/ui_slideshow.h"
#include "Utils.h"

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    int playerWidth = ui->imageView->width(), playerHeight = ui->imageView->height();
    playerMinDimension = playerWidth < playerHeight ? playerWidth : playerHeight;

    connect(ui->browseBtn, &QAbstractButton::clicked, this, &Slideshow::browse); // connect browse button click with browse() function
    connect(ui->dirBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &Slideshow::setPlaylist); // connect changes in comboBox with displayPlaylist() function passing its text
    connect(&slideshowTimer.timer, &QTimer::timeout, this, &Slideshow::displayImage); // connect changes in comboBox with displayPlaylist() function passing its text

    ui->imageView->setScene(scene); // connect GraphicsView to GraphicsScene
}

Slideshow::~Slideshow() {
    delete ui;
}

void Slideshow::browse() {
    slideshowTimer.timer.stop(); // stop timer if any
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
    slideshowTimer.timer.stop(); // stop timer if any
    if(!playlist.images.empty()) { // check if vector was already allocated, if so erase it
        playlist.images.clear();
    }
    qInfo() << "Scanning directory: " + text;
    QFileInfoList imagesList = getImagesInFolder(text); // get images list
    playlist.imagesCount = imagesList.count(); // get number of images in the list
    QListIterator<QFileInfo> itr(imagesList); // iterate images list
    QString imageDir;
    QPixmap img;
    while(itr.hasNext()) {
        imageDir = itr.next().absoluteFilePath(); // get image absolute path
        qInfo() << "Adding file: " + imageDir;
        try {
            img = QPixmap(imageDir).scaledToHeight(playerMinDimension);
            if(!img.isNull()) {
                playlist.images.push_back(std::make_shared<QGraphicsPixmapItem>(img)); // create a new GraphicsPixmapItem for each file and push it in images vector (smart pointer)
                playlist.images.back().get()->setVisible(false); // hide every item
            }
            else
                throw (std::runtime_error("Missing file "+imageDir.toStdString()));
        } catch (std::runtime_error& e) {
            qCritical() << e.what();
        } catch(std::bad_alloc& e) {
            qCritical() << "Error allocating file " + imageDir;
        } catch(std::exception& e) {
            qCritical() << "Error at file " + imageDir;
            qCritical() << e.what();
        }
    }
    startSlideshow();
}

void Slideshow::displayImage() {
    // display image in GraphicsView
    playlist.images[playlist.currentImage].get()->setVisible(false); // hide previous image
    setNextImage();
    setSceneRect(playlist.images[playlist.currentImage].get()->boundingRect()); // adjust scene dimension to fit current image
    playlist.images[playlist.currentImage].get()->setVisible(true); // show current image
}

void Slideshow::startSlideshow() {
    scene->clear();
    playlist.currentImage = 0;
    auto firstImg = playlist.images[playlist.currentImage].get();
    for(auto itr=playlist.images.begin(); itr!=playlist.images.end(); itr++)
        scene->addItem((*itr).get());
    setSceneRect(firstImg->boundingRect());
    firstImg->setVisible(true);
    slideshowTimer.timer.start(slideshowTimer.timerInterval);
}

void Slideshow::setNextImage() {
    playlist.currentImage++;
    if(playlist.currentImage >= playlist.imagesCount)
        playlist.currentImage = 0;
}