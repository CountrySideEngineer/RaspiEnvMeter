#ifndef CRASPITEMPERATUREVIEW_H
#define CRASPITEMPERATUREVIEW_H
#include "craspienvmetertimeview.h"


class CRaspiTemperatureView : public CRaspiEnvMeterView
{
public:
    CRaspiTemperatureView(QWidget* parent = nullptr);

protected slots:
    void dataChanged(const QModelIndex &topLegft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;

protected:
    void resizeEvent(QResizeEvent* event) override;

protected:
    int32_t int_part_;
    uint32_t dec_part_;
    QString value_to_show_;
};

#endif // CRASPITEMPERATUREVIEW_H
