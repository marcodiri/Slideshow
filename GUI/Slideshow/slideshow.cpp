#include "slideshow.h"
#include "SlideshowDebug/ui_slideshow.h"

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow),
    scene(new QGraphicsScene(this)), imagesCount(0)
{
    ui->setupUi(this);
    connect(ui->browseBtn, &QAbstractButton::clicked, this, &Slideshow::browse); // connect browse button click with browse() function

    ui->imageView->setScene(scene); // connect GraphicsView to GraphicsScene
}

Slideshow::~Slideshow()
{
    // delete vector
    for(auto itr=playlist.begin(); itr!=playlist.end(); itr++){
        delete *itr;
        *itr = 0;
    }

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
    QDir directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Choose images directory"), QDir::homePath()));
    QString directoryS = directory.absolutePath();
    imagesCount = directory.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.bmp" << "*.xpm", QDir::NoDotAndDotDot|QDir::Files).count(); // get number of images in folder
    if(imagesCount) { // check for empty directory
        if (!directoryS.isEmpty()) {
            if (ui->dirBox->findText(directoryS) == -1) // check if directory was already present in comboBox
                ui->dirBox->addItem(directoryS);
            ui->dirBox->setCurrentIndex(ui->dirBox->findText(directoryS));
        }
    } else {
        QMessageBox::information(
                this,
                tr("Slideshow"),
                tr("Directory does not contain images and was not added."));
    }
}