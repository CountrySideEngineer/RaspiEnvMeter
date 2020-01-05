#include "craspienvmetertimeview.h"

CRaspiEnvMeterTimeView::CRaspiEnvMeterTimeView(QWidget* parent)
    : CRaspiEnvMeterView(parent)
{
    this->item_view_ = new QLabel();
    this->item_view_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->item_view_->resize(100, 100);
    this->item_view_->setFrameShape(Shape::Box);
    this->item_view_->setText(tr("aaaa"));
}
