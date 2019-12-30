#ifndef ENVMETER_H
#define ENVMETER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EnvMeter; }
QT_END_NAMESPACE

class EnvMeter : public QMainWindow
{
    Q_OBJECT

public:
    EnvMeter(QWidget *parent = nullptr);
    ~EnvMeter();

private:
    Ui::EnvMeter *ui;
};
#endif // ENVMETER_H
