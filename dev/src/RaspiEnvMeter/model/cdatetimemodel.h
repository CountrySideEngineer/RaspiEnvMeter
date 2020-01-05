#ifndef CDATETIMEMODEL_H
#define CDATETIMEMODEL_H

#include <QObject>
#include "craspienvmetermodelbase.h"
#include <qabstractitemmodel.h>

class CDateTimeModel : public CRaspiEnvMeterModelBase
{
    Q_OBJECT

public:
    enum {
        DATE_TIME_MODEL_ROW_INDEX_AMPM_DISPLAY_CONFIG = 0,
        DATE_TIME_MODEL_ROW_INDEX_AMPM_DISPLAY,
        DATE_TIME_MODEL_ROW_INDEX_HOUR_OF_DAY,
        DATE_TIME_MODEL_ROW_INDEX_MINUTE_OF_DAY,
        DATE_TIME_MODEL_ROW_INDEX_SECOND_OF_MINUTE,
        DATE_TIME_MODEL_ROW_INDEX_MONTH_OF_YEAR,
        DATE_TIME_MODEL_ROW_INDEX_DAY_OF_MONTH,
        DATE_TIME_MODEL_ROW_INDEX_MAX
    };

    explicit CDateTimeModel(QObject* parent = nullptr);
    ~CDateTimeModel() override {}

public:
    int rowCount(const QModelIndex &parent) const override;

    void Update() override;

protected:

};

#endif // CDATETIMEMODEL_H
