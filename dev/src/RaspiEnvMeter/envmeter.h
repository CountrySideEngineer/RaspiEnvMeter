#ifndef ENVMETER_H
#define ENVMETER_H

#include <QMainWindow>
#include "model/cdatetimemodel.h"
#include "model/cpressuremodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EnvMeter; }
QT_END_NAMESPACE

class EnvMeter : public QMainWindow
{
    Q_OBJECT

public:
    EnvMeter(QWidget *parent = nullptr);
    ~EnvMeter();

protected slots:
    void onTimerDispatch();

private:
    Ui::EnvMeter *ui;

    QTimer* timer_;
    CDateTimeModel* date_time_model_;
    CPressureModel* pressure_model_;
};
#endif // ENVMETER_H
