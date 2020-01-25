#include "craspitemperatureview.h"
#include "model/ctemperaturemodel.h"
#include <QDebug>

CRaspiTemperatureView::CRaspiTemperatureView(QWidget* parent)
    : CRaspiEnvMeterView (parent)
    , int_part_(0)
    , dec_part_(0)
    , value_to_show_(tr("0.0"))
{
    this->item_view_ = new QLabel(this);
    this->item_view_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

/**
 * @brief Event handler of resize event.
 * @param event Event parameter.
 */
void CRaspiTemperatureView::resizeEvent(QResizeEvent *event)
{
    qDebug() << tr("CRaspiTemperatureView::resizeEvent(QResizeEvent *event) called");

    QAbstractItemView::resizeEvent(event);
    this->item_view_->resize(this->size().width(), this->size().height());
}

/**
 * @brief Event handler of changing data in model.
 * @param topLeft   Model index.
 * @param bottomRight   Not in use.
 * @param roles Not in use.
 */
void CRaspiTemperatureView::dataChanged(const QModelIndex &topLeft,
                                        const QModelIndex &bottomRight,
                                        const QVector<int> &roles)
{
    assert(nullptr != this->model());
    assert(nullptr != this->item_view_);

    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    if (topLeft.row() == this->model_row_index_) {
        if (topLeft.column() == CTemperatureModel::MODEL_COL_INDEX_TEMPERATURE_INT_PART) {
            this->int_part_ = this->model()->data(topLeft).toInt();
        } else if (topLeft.column() == CTemperatureModel::MODEL_COL_INDEX_TEMPERATURE_DEC_PART) {
            /*
             * To avoid the value being update to 2 time every update the temperature,
             * the value is update only when the decimal part value is update.
             */
            this->dec_part_ = this->model()->data(topLeft).toUInt();

            this->value_to_show_ =
                    QString("%L1").arg(this->int_part_) +
                    "." +
                    QString("%L1").arg(this->dec_part_, 2, 10, QChar('0'));
            qDebug() << tr("temp_value = ") << this->value_to_show_ << endl;
        }
    }
    this->item_view_->setText(this->value_to_show_);
}
