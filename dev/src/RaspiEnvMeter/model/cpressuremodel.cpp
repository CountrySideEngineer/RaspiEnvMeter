#include "cpressuremodel.h"
#include "cmpl115a1device.h"
#include "util/util.h"

/**
 * @brief Constructor of CPressureModel object.
 * @param parent    Pointer to object which holds, manages this object.
 */
CPressureModel::CPressureModel(QObject* parent) : CRaspiEnvMeterModelBase (parent)
{
    this->device_ = new CMPL115A1Device();
    this->device_->Initialize();
    this->device_->UpdateCoeff();
    this->device_->Update();
}

/**
 * @brief Destructor of CPressureModel class.
 */
CPressureModel::~CPressureModel()
{
    Util::SAFE_RELEASE_DATA(&this->device_);
}

/**
 * @brief Returns the number of row.
 * @param parent    Pointer to parent object.
 * @return  The number of row.
 */
int CPressureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)


    return PRESSURE_MODE_ROW_INDEX_MAX;
}

/**
 * @brief Update data and notify model data.
 */
void CPressureModel::Update()
{
    assert(nullptr != this->device_);

    this->device_->Update();
    float press_kPa = this->device_->GetFloat();
    float press_hPa = Util::kPaTohPa(press_kPa);
    int press = Util::float2int(press_hPa);
    CRaspiEnvMeterModelBase::Update(PRESSURE_MODE_ROW_INDEX_PRESSURE, 0, press);
}
