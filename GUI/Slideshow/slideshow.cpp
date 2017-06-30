#include "slideshow.h"
#include "SlideshowDebug/ui_slideshow.h"
#include "Utils.h"

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    connect(ui->browseBtn, &QAbstractButton::clicked, this, &Slideshow::browse); // connect browse button click with browse() function
    connect(ui->dirBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &Slideshow::setPlaylist); // connect changes in comboBox with displayPlaylist() function passing its text

    ui->imageView->setScene(scene); // connect GraphicsView to GraphicsScene
}

Slideshow::~Slideshow() {
    delete ui;
}

void Slideshow::showEvent(QShowEvent *event) {
    ui->imageView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio); // fitInView has to be called after the object shows
}

void Slideshow::resizeEvent(QResizeEvent *event) {
    ui->imageView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio); // fitInView to fit resized window
}

void Slideshow::browse() {
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

void Slideshow::setPlaylist(const QString &text) {
    if(!playlist.images.empty()) { // check if vector was already allocated, if so erase it
        playlist.images.clear();
    }
    qInfo() << "Scanning directory: " + text;
    QFileInfoList imagesList = getImagesInFolder(text); // get images list
    playlist.imagesCount = imagesList.count(); // get number of images in the list
    QListIterator<QFileInfo> itr(imagesList); // iterate images list
    QString imageDir;
    while(itr.hasNext()) {
        imageDir = itr.next().absoluteFilePath(); // get image absolute path
        qInfo() << "Adding file: " + imageDir;
        try {
            playlist.images.push_back(std::make_shared<QGraphicsPixmapItem>(QPixmap(imageDir))); // create a new GraphicsPixmapItem for each file and push it in images vector (smart pointer)
        } catch(std::bad_alloc& e) {
            qCritical() << "Error allocating file " + itr.next().absoluteFilePath();
        } catch(std::exception& e) {
            qCritical() << "Error at file " + itr.next().absoluteFilePath();
            qCritical() << e.what();
        }
    }
}

void Slideshow::displayPlaylist() {
    // display images in GraphicsView
}