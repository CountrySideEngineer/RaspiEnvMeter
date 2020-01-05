#ifndef CDATETIME_H
#define CDATETIME_H
#include "QString"

/**
 * @class   Class to hold date data, for example, hour in a day and the format.
 * @brief The CDateTime class
 */
class CDateTime
{
public:
    explicit CDateTime();
    ~CDateTime() {}

public:
    void    Update();
    int GetHour() { return this->hour_; }
    int GetMinute() { return this->minute_; }
    int GetSecond() { return this->second_; }
    int GetMonth() { return this->month_; }
    int GetDayOfMonth() { return this->dayofMonth_; }

protected:
    QString time_sytem_;
    int hour_;
    int minute_;
    int second_;
    int month_;
    int dayofMonth_;
};

#endif // CDATETIME_H
