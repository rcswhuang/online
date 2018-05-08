#include "htemplatewindow.h"
#include "ui_templatewindow.h"

HTemplateWindow::HTemplateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HTemplateWindow)
{
    ui->setupUi(this);
}

HTemplateWindow::~HTemplateWindow()
{
    delete ui;
}
