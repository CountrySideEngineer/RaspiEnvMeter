#ifndef CTEMPERATUREMODEL_H
#define CTEMPERATUREMODEL_H
#include <QObject>
#include "craspienvmetermodelbase.h"
#include "QAbstractItemModel"
#include "adevicebase.h"
#include "cdht11device.h"

class CTemperatureModel : public CRaspiEnvMeterModelBase
{
    Q_OBJECT

public:
    enum {
        MODEL_ROW_INDEX_TEMPERATURE_PART = 0,
        MODEL_ROW_INDEX_HUMIDITY,
        MODEL_ROW_INDEX_MAX
    };
    enum {
        MODEL_COL_INDEX_TEMPERATURE_INT_PART = 0,
        MODEL_COL_INDEX_TEMPERATURE_DEC_PART,
        MODEL_COL_INDEX_TEMPERATURE_MAX
    };

public:
    explicit CTemperatureModel(QObject* parent = nullptr);
    virtual ~CTemperatureModel() override;

public:
    int rowCount(const QModelIndex &parent) const override;
    void Update() override;

protected:
    CDHT11Device* device_;
};

#endif // CTEMPERATUREMODEL_H
