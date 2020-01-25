#include "craspienvmetertimeview.h"
#include <QDebug>

/**
 * @brief Constructor of CRaspiEnvMeterTimeView class.
 * @param parent    Pointer to parent object.
 */
CRaspiEnvMeterTimeView::CRaspiEnvMeterTimeView(QWidget* parent)
    : CRaspiEnvMeterView(parent)
{
    this->item_view_ = new QLabel(this);
    this->item_view_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

/**
 * @brief Event handler of resize event.
 * @param event Event parameter.
 */
void CRaspiEnvMeterTimeView::resizeEvent(QResizeEvent *event)
{
    qDebug() << tr("CRaspiEnvMeterTimeView::resizeEvent(QResizeEvent *event) called");

    QAbstractItemView::resizeEvent(event);
    this->item_view_->resize(this->size().width(), this->size().height());
}

void CRaspiEnvMeterTimeView::dataChanged(const QModelIndex &topLeft,
                                         const QModelIndex &bottomRight,
                                         const QVector<int> &roles)
{
    assert(nullptr != this->model());
    assert(nullptr != this->item_view_);

    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    int index = topLeft.row();
    if (index == this->model_row_index_) {
        int value = this->model()->data(topLeft).toInt();
        QString value_to_show = QString("%L1").arg(value, 2, 10, QChar('0'));
        this->item_view_->setText(value_to_show);
    } else {
        //Nothing todo!
    }
}
