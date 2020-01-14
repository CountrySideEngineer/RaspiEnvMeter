#ifndef CRASPIENVPRESSVIEW_H
#define CRASPIENVPRESSVIEW_H
#include "craspienvmeterview.h"

class CRaspiEnvPressView : public CRaspiEnvMeterView
{
public:
    explicit CRaspiEnvPressView(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

};

#endif // CRASPIENVPRESSVIEW_H
