#include "shoosewindow.h"
#include "ui_shoosewindow.h"

ShooseWindow::ShooseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShooseWindow)
{
    ui->setupUi(this);
}

ShooseWindow::~ShooseWindow()
{
    delete ui;
}



void ShooseWindow::on_realMapButton_clicked()
{
    secWindow = new SecWindow(this);
    secWindow->show();
    this->hide();
}
