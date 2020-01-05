#include "cdatetimemodel.h"
#include "cdatetime.h"

/**
 * @brief Constructor of  CDateTimeModel class.
 * @param parent    Pointer to object which holds, manages this object.
 */
CDateTimeModel::CDateTimeModel(QObject* parent)
    : CRaspiEnvMeterModelBase(parent)
{}

/**
 * @brief Returns the number of rows under the given parent.
 *        When the parent is valid it means that rowCount is returning the number of children of parent.
 * @param parent    Reference to index of model.
 * @return  The number of rows of the model.
 */
int CDateTimeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return DATE_TIME_MODEL_ROW_INDEX_MAX;
}

/**
 * @brief Update model data.
 */
void CDateTimeModel::Update()
{
    auto model = new CDateTime();
    CRaspiEnvMeterModelBase::Update(DATE_TIME_MODEL_ROW_INDEX_HOUR_OF_DAY, 0, model->GetHour());
    CRaspiEnvMeterModelBase::Update(DATE_TIME_MODEL_ROW_INDEX_MINUTE_OF_DAY, 0, model->GetMinute());
    CRaspiEnvMeterModelBase::Update(DATE_TIME_MODEL_ROW_INDEX_SECOND_OF_MINUTE, 0, model->GetSecond());
    CRaspiEnvMeterModelBase::Update(DATE_TIME_MODEL_ROW_INDEX_MONTH_OF_YEAR, 0, model->GetMonth());
    CRaspiEnvMeterModelBase::Update(DATE_TIME_MODEL_ROW_INDEX_DAY_OF_MONTH, 0, model->GetDayOfMonth());
}
