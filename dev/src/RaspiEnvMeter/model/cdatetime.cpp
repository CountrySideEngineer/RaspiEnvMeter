#include "cdatetime.h"
#include <QDate>

/**
 * @brief Constructor of CDateTime class.
 */
CDateTime::CDateTime()
{
    this->Update();
}

/**
 * @brief Update date time.
 */
void CDateTime::Update()
{
    QDateTime dateTime = QDateTime::currentDateTime();

    QTime time = dateTime.time();
    this->hour_ = time.hour();
    this->minute_ = time.minute();
    this->second_ = time.second();

    QDate date = dateTime.date();
    this->month_ = date.month();
    this->dayofMonth_ = date.daysInMonth();
}
