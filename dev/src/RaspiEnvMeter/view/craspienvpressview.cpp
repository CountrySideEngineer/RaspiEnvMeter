#include "craspienvpressview.h"
#include <QDebug>

/**
 * @brief Constructor of CRaspiEnvPressView class
 * @param parent    Pointer to parent object.
 */
CRaspiEnvPressView::CRaspiEnvPressView(QWidget* parent)
    : CRaspiEnvMeterView (parent)
{
    this->item_view_ = new QLabel(this);
    this->item_view_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void CRaspiEnvPressView::resizeEvent(QResizeEvent *event)
{
    qDebug() << tr("CRaspiEnvPressView::resizeEvent(QResizeEvent *event) called");

    QAbstractItemView::resizeEvent(event);
    this->item_view_->resize(this->size().width(), this->size().height());
}
