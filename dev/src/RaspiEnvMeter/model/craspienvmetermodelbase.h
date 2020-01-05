#ifndef CRASPIENVMETERMODELBASE_H
#define CRASPIENVMETERMODELBASE_H

#include <QObject>
#include <QAbstractItemModel>

class CRaspiEnvMeterModelBase : public QAbstractItemModel
{
public:
    explicit CRaspiEnvMeterModelBase(QObject* parent = nullptr);
    virtual ~CRaspiEnvMeterModelBase() override {}

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual void Update() = 0;

protected:
    template<typename DataType> void Update(int row_index, int col_index, DataType data);

    QMap<QModelIndex, QVariant> model_data_;
};

template<typename DataType>
void CRaspiEnvMeterModelBase::Update(int row_index, int col_index, DataType data)
{
    this->setData(
                this->index(row_index, col_index),
                QVariant(data));
}

#endif // CRASPIENVMETERMODELBASE_H
