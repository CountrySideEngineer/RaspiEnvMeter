#include "ctemperaturemodel.h"
#include "util/util.h"

#define DHT11_PIN   (21)    //No.21 GPIO pin.

/**
 * @brief Constructor of CTemperatureModel.
 * @param parent    Pointer to parent.
 */
CTemperatureModel::CTemperatureModel(QObject* parent)
    : CRaspiEnvMeterModelBase(parent)
{
    this->device_ = new CDHT11Device(DHT11_PIN, APart::PART_PIN_DIRECTION_OUTPUT);
    this->device_->Initialize();
    this->device_->Update();
}

/**
 * @brief Destructor of CTemperatureModel.
 */
CTemperatureModel::~CTemperatureModel()
{
    Util::SAFE_RELEASE_DATA(&(this->device_));
}

/**
 * @brief Returns the number of row.
 * @param parent
 * @return
 */
int CTemperatureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return MODEL_ROW_INDEX_MAX;
}

/**
 * @brief Update value of model.
 */
void CTemperatureModel::Update()
{
    printf("void CTemperatureModel::Update() called\r\n");

    assert(nullptr != this->device_);

    this->device_->Update();

    int16_t temperature_int_part = this->device_->GetTemperature_Integer();
    int16_t temperature_dec_part = this->device_->GetTemperature_Decimal();
    uint32_t humidity = this->device_->GetHumidity();

    CRaspiEnvMeterModelBase::Update(
                MODEL_ROW_INDEX_TEMPERATURE_PART, MODEL_COL_INDEX_TEMPERATURE_INT_PART,
                temperature_int_part);
    CRaspiEnvMeterModelBase::Update(
                MODEL_ROW_INDEX_TEMPERATURE_PART, MODEL_COL_INDEX_TEMPERATURE_DEC_PART,
                temperature_dec_part);
    CRaspiEnvMeterModelBase::Update(MODEL_ROW_INDEX_HUMIDITY, 0 , humidity);
}
