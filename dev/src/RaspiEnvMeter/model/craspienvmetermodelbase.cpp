#include "craspienvmetermodelbase.h"

/**
 * @brief Constructor of CRaspiEnvMeterModelBase class.
 * @param parent    Pointer to object which uses or holds this model object.
 */
CRaspiEnvMeterModelBase::CRaspiEnvMeterModelBase(QObject* parent)
    : QAbstractItemModel(parent)
{
    this->model_data_.clear();
}

/**
 * @brief Returns the index of the item in the model specified by the given row, column and parent index.
 * @param row   Row index of the model.
 * @param column    Column index of the model.
 * @param parent    Reference of the parent object.
 * @return  The index of the item in the model.
 */
QModelIndex CRaspiEnvMeterModelBase::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return QAbstractItemModel::createIndex(row, column);
}

/**
 * @brief Returns the parent of the model item with the given index.
 *        If the item has no parent, an invalid QModelIndex is returned.
 * @param child Unused variable.
 * @return  The parent of the model item with the given index.
 */
QModelIndex CRaspiEnvMeterModelBase::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)

    return QModelIndex();
}

/**
 * @brief Returns the number of rows under the given parent.
 *        When the parent is valid it means that rowCount is returning the number of children of parent.
 * @param parent    Reference to index of model.
 * @return  The number of rows of the model.
 */
int CRaspiEnvMeterModelBase::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 0;
}

/**
 * @brief Returns the number of columns for the children of the given parent.
 * @param parent    Reference to index of model.
 * @return  The number of columns of the model.
 */
int CRaspiEnvMeterModelBase::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 0;
}

/**
 * @brief Returns the data stored under the given role for the item referred to by the index.
 * @param index Reference of QModelIndex object to get model.
 * @param role  Role of model.
 * @return  The data stored under the given role for the item
 */
QVariant CRaspiEnvMeterModelBase::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)

    if (index.isValid()) {
        return this->model_data_[index];
    } else {
        return QVariant();
    }
}

/**
 * @brief Sets the role data for the item at index to value.
 * @param index Index of model to set data.
 * @param value Value to set to model.
 * @param role  Role of value.
 * @return  Returns true if successful; otherwise returns false.
 */
bool CRaspiEnvMeterModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)

    if (index.isValid()) {
        this->model_data_[index] = value;
        emit dataChanged(index, index);

        return true;
    } else {
        return false;
    }
}
