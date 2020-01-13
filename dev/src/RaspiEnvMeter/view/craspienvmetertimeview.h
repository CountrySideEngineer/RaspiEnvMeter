#ifndef CRASPIENVMETERTIMEVIEW_H
#define CRASPIENVMETERTIMEVIEW_H

#include "craspienvmeterview.h"

class CRaspiEnvMeterTimeView : public CRaspiEnvMeterView
{
public:
    explicit CRaspiEnvMeterTimeView(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

};

#endif // CRASPIENVMETERTIMEVIEW_H
