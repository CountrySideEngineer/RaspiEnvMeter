#include "envmeter.h"
#include "ui_envmeter.h"

EnvMeter::EnvMeter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EnvMeter)
{
    ui->setupUi(this);
}

EnvMeter::~EnvMeter()
{
    delete ui;
}

