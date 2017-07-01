#include <QtWidgets/QApplication>
#include "GUI/Slideshow/Slideshow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Slideshow w;
    w.show();
    return a.exec();
}
