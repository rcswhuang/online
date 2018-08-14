#include "hrehearsalframe.h"
#include "ui_operorderwindow.h"

HRehearsalFrame::HRehearsalFrame(QWidget *parent) :
    HFrame(parent),
    ui(new Ui::operorderWindow)
{
    ui->setupUi(this);
}

HRehearsalFrame::~HRehearsalFrame()
{
    delete ui;
}
