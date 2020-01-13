#include "envmeter.h"
#include "ui_envmeter.h"
#include <QDebug>
#include <QTimer>
#include "model/cdatetimemodel.h"
#include "model/cpressuremodel.h"

EnvMeter::EnvMeter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnvMeter)
    , timer_(new QTimer(this))
{
    this->ui->setupUi(this);

    this->ui->AmPmDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_AMPM_DISPLAY);
    this->ui->TimeHourDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_HOUR_OF_DAY);
    this->ui->TimeMinuteDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_MINUTE_OF_HOUR);
    this->ui->TimeSecondDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_SECOND_OF_MINUTE);
    this->ui->DateMonthDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_MONTH_OF_YEAR);
    this->ui->DateDayDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_DAY_OF_MONTH);
    this->ui->PressDisplay->SetModelRowIndex(CPressureModel::PRESSURE_MODE_ROW_INDEX_PRESSURE);

    this->date_time_model_ = new CDateTimeModel(this);
    this->ui->AmPmDisplay->setModel(this->date_time_model_);
    this->ui->TimeHourDisplay->setModel(this->date_time_model_);
    this->ui->TimeMinuteDisplay->setModel(this->date_time_model_);
    this->ui->TimeSecondDisplay->setModel(this->date_time_model_);
    this->ui->DateMonthDisplay->setModel(this->date_time_model_);
    this->ui->DateDayDisplay->setModel(this->date_time_model_);

    this->pressure_model_ = new CPressureModel(this);
    this->ui->PressDisplay->setModel(this->pressure_model_);

    //@Todo:Add code to change view size.
    //Start timer.
    this->timer_->setInterval(100);
    this->timer_->setSingleShot(false);
    connect(this->timer_, SIGNAL(timeout()), this, SLOT(onTimerDispatch()));
    this->timer_->start();
}

EnvMeter::~EnvMeter()
{
    delete this->date_time_model_;

    this->timer_->stop();
    delete this->timer_;

    delete ui;
}

/**
 * @brief Event handler of Qt time dispatch.
 */
void EnvMeter::onTimerDispatch()
{
    this->date_time_model_->Update();
}
