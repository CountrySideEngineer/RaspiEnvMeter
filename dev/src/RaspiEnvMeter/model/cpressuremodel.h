#ifndef CPRESSUREMODEL_H
#define CPRESSUREMODEL_H
#include <QObject>
#include "craspienvmetermodelbase.h"
#include <QAbstractItemModel>
#include "adevicebase.h"
#include "cmpl115a1device.h"

class CPressureModel : public CRaspiEnvMeterModelBase
{
    Q_OBJECT

public:
    enum {
        PRESSURE_MODE_ROW_INDEX_PRESSURE = 0,
        PRESSURE_MODE_ROW_INDEX_MAX
    };

    explicit CPressureModel(QObject* parent = nullptr);
    virtual ~CPressureModel() override;

public:
    int rowCount(const QModelIndex &parent) const override;

    void Update() override;

protected:
    CMPL115A1Device* device_;
};

#endif // CPRESSUREMODEL_H
