#ifndef CRASPIHUMIDITYVIEW_H
#define CRASPIHUMIDITYVIEW_H
#include "view/craspienvmeterview.h"


class CRaspiHumidityView : public CRaspiEnvMeterView
{
public:
    explicit CRaspiHumidityView(QWidget* parent = nullptr);

protected slots:
    void dataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;

protected:
    void resizeEvent(QResizeEvent* event) override;

protected:
    int humidity_;
};

#endif // CRASPIHUMIDITYVIEW_H
