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
