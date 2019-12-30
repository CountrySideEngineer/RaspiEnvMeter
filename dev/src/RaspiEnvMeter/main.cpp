#include "envmeter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnvMeter w;
    w.show();
    return a.exec();
}
