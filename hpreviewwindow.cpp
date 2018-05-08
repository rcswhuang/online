#include "hoperorderwindow.h"
#include "ui_operorderwindow.h"

HOperorderWindow::HOperorderWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operorderWindow)
{
    ui->setupUi(this);
}

HOperorderWindow::~HOperorderWindow()
{
    delete ui;
}
