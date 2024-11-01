#include "amd64states.h"
#include "ui_amd64states.h"

AMD64States::AMD64States(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AMD64States)
{
    ui->setupUi(this);
}

AMD64States::~AMD64States()
{
    delete ui;
}
