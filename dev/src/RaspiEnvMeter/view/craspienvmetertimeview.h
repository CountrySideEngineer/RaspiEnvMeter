#ifndef CRASPIENVMETERTIMEVIEW_H
#define CRASPIENVMETERTIMEVIEW_H

#include "craspienvmeterview.h"

class CRaspiEnvMeterTimeView : public CRaspiEnvMeterView
{
public:
    explicit CRaspiEnvMeterTimeView(QWidget* parent = nullptr);

protected slots:
    void dataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // CRASPIENVMETERTIMEVIEW_H
