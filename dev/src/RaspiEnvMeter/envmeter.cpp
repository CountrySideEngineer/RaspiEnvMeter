#include "envmeter.h"
#include "ui_envmeter.h"
#include <QDebug>
#include <QTimer>
#include "model/cdatetimemodel.h"
#include "model/cpressuremodel.h"
#include "util/util.h"

EnvMeter::EnvMeter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnvMeter)
    , timer_100ms_(new QTimer(this))
    , timer_10sec_(new QTimer(this))
{
    this->ui->setupUi(this);

    this->ui->AmPmDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_AMPM_DISPLAY);
    this->ui->TimeHourDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_HOUR_OF_DAY);
    this->ui->TimeMinuteDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_MINUTE_OF_HOUR);
    this->ui->TimeSecondDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_SECOND_OF_MINUTE);
    this->ui->DateMonthDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_MONTH_OF_YEAR);
    this->ui->DateDayDisplay->SetModelRowIndex(CDateTimeModel::DATE_TIME_MODEL_ROW_INDEX_DAY_OF_MONTH);
    this->ui->PressDisplay->SetModelRowIndex(CPressureModel::PRESSURE_MODE_ROW_INDEX_PRESSURE);
    this->ui->TemperatureDisplay->SetModelRowIndex(CTemperatureModel::MODEL_ROW_INDEX_TEMPERATURE_PART);

    this->date_time_model_ = new CDateTimeModel(this);
    this->ui->AmPmDisplay->setModel(this->date_time_model_);
    this->ui->TimeHourDisplay->setModel(this->date_time_model_);
    this->ui->TimeMinuteDisplay->setModel(this->date_time_model_);
    this->ui->TimeSecondDisplay->setModel(this->date_time_model_);
    this->ui->DateMonthDisplay->setModel(this->date_time_model_);
    this->ui->DateDayDisplay->setModel(this->date_time_model_);

    this->pressure_model_ = new CPressureModel(this);
    this->ui->PressDisplay->setModel(this->pressure_model_);

    this->temperature_model_ = new CTemperatureModel(this);
    this->ui->TemperatureDisplay->setModel(this->temperature_model_);

    //@Todo:Add code to change view size.

    //Setup timer dispatch each 100msec.
    this->timer_100ms_->setInterval(100);
    this->timer_100ms_->setSingleShot(false);
    connect(this->timer_100ms_, SIGNAL(timeout()), this, SLOT(onTimerDispatch_100msec()));

    this->timer_10sec_->setInterval(4 * 1000); //10 second.
    this->timer_10sec_->setSingleShot(false);
    connect(this->timer_10sec_, SIGNAL(timeout()), this, SLOT(onTimerDispatch_10sec()));

    //Start timer.
    this->timer_100ms_->start();
    this->timer_10sec_->start();
}

EnvMeter::~EnvMeter()
{
    delete this->date_time_model_;

    this->timer_100ms_->stop();
    Util::SAFE_RELEASE_DATA(&(this->timer_100ms_));

    this->timer_10sec_->stop();
    Util::SAFE_RELEASE_DATA(&(this->timer_10sec_));

    delete ui;
}

/**
 * @brief Event handler of Qt time dispatch.
 */
void EnvMeter::onTimerDispatch_100msec()
{
    this->date_time_model_->Update();
}

/**
 * @brief Event handler of Qt time dispatch.
 */
void EnvMeter::onTimerDispatch_10sec()
{
    this->pressure_model_->Update();
    this->temperature_model_->Update();
}

