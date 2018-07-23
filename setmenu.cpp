#include "setmenu.h"
#include "ui_setmenu.h"

setmenu::setmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setmenu)
{
    ui->setupUi(this);
    //ÉèÖÃ±³¾°
    //QPixmap bgImages(":/back/menu.jpg");
   // QPalette bgPalette = palette();
    //bgPalette.setBrush(QPalette::Background,bgImages);
   // this->setPalette(bgPalette);
}

setmenu::~setmenu()
{
    delete ui;
}

void setmenu::on_pushButton_clicked()
{
    emit backToMenu();
}



void setmenu::on_comboBox_currentIndexChanged(int index)
{
    emit setLevel(index);
}


void setmenu::on_checkBox_2_clicked(bool checked)
{

    emit keyMusic(checked);
}

void setmenu::on_checkBox_clicked(bool checked)
{
    emit backMusic(checked);
}
