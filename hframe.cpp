#include "hframe.h"

#include <QVBoxLayout>
HFrame::HFrame(QFrame* parent):QFrame(parent)
{
    frameLayout = new QVBoxLayout(this);
    frameLayout->setContentsMargins(2, 2, 2, 2);
    centerLayout = new QVBoxLayout();
    frameLayout->addLayout(centerLayout);
}
