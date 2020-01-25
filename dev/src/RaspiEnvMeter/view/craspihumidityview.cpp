#include "craspihumidityview.h"
#include <QDebug>

/**
 * @brief Constructor of CRaspiHumidityView widget class.
 * @param parent    Pointer to the parental object holds this.
 */
CRaspiHumidityView::CRaspiHumidityView(QWidget* parent)
    : CRaspiEnvMeterView (parent)
    , humidity_(0)
{
    this->item_view_ = new QLabel(this);
    this->item_view_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void CRaspiHumidityView::resizeEvent(QResizeEvent *event)
{
    qDebug() << tr("CRaspiEnvPressView::resizeEvent(QResizeEvent *event) called");

    QAbstractItemView::resizeEvent(event);
    this->item_view_->resize(this->size().width(), this->size().height());
}

/**
 * @brief Event handler of changing the value of model.
 * @param topLeft   Index of model.
 * @param bottomRight   Not used.
 * @param roles Not used.
 */
void CRaspiHumidityView::dataChanged(const QModelIndex &topLeft,
                                         const QModelIndex &bottomRight,
                                         const QVector<int> &roles)
{
    assert(nullptr != this->model());
    assert(nullptr != this->item_view_);

    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    if (topLeft.row() == this->model_row_index_) {
        this->humidity_ = this->model()->data(topLeft).toInt();
        this->item_view_->setText(QString("%L1").arg(this->humidity_));
    }
}
