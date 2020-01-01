#include "envmeter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnvMeter w;
#if defined (BUILD_PC)
    w.setFixedSize(480, 320);
    w.show();
#elif defined (BUILD_RASPI)
    w.showFullScreen();
#else
    w.setFixedSize(480, 320);
    w.show();
#endif
    return a.exec();
}
