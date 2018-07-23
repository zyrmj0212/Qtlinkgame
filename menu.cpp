#include "menu.h"
#include "ui_menu.h"

#include<QMessageBox>
#include<QPixmap>
#include<QPalette>
#include <QBitmap>
#include<QBrush>
menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

  //  QPixmap bgImages(":/back/menu1.jpg");
       // QPalette bgPalette = palette();
       // bgPalette.setBrush(QPalette::Background,bgImages);
       // this->setPalette(bgPalette);
}
menu::~menu()
{
    delete ui;
}


void menu::on_pushButton_start_clicked()
{
    emit startplay();
    hide();
}

//пе╨е

void menu::on_pushButton_quit_clicked()
{
    int ret=QMessageBox::warning(this,tr("WARNING"),tr("Do you really want to quit?"),QMessageBox::Abort);
    if(ret==QMessageBox::Abort)
    QApplication::exit(0);
}

void menu::on_pushButton_set_clicked()
{
    emit setMenuf();
}

