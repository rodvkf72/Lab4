#include "helloqt.h"
#include "ui_helloqt.h"

helloqt::helloqt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::helloqt)
{
    ui->setupUi(this);
}

helloqt::~helloqt()
{
    delete ui;
}
