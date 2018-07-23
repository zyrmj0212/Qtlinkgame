#include <QDebug>
#include <QSound>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>
#include<QGraphicsDropShadowEffect>
#include "main_game_window.h"
#include "ui_main_game_window.h"



// 游戏主界面
MainGameWindow::MainGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGameWindow)

{
    ui->setupUi(this);
    // 重载eventfilter安装到当前window（其实如果不适用ui文件的话直接可以在window的paintevent里面画）
    level=BASIC;
    keyMusic=true;
    backMusic=true;

    nameDialog=new QDialog(this);

    myMenu =new menu(this);
    if (myMenu->objectName().isEmpty())
        myMenu->setObjectName(QString::fromUtf8("menu"));
    myMenu->setStyleSheet("QWidget#menu{border-image: url(:/back/menu1.jpg)}");
    myMenu->show();
    connect(myMenu,SIGNAL(startplay()),this,SLOT(initGame()));
    connect(myMenu,SIGNAL(setMenuf()),this,SLOT(setMenu()));


    //setMenu
    mySetMenu=new setmenu(this);
    connect(mySetMenu,SIGNAL(backToMenu()),this,SLOT(backMenu1()));
    connect(mySetMenu,SIGNAL(setLevel(int)),this,SLOT(setMyLevel(int)));
    connect(mySetMenu,SIGNAL(keyMusic(bool)),this,SLOT(setKeyMusic(bool)));
    connect(mySetMenu,SIGNAL(backMusic(bool)),this,SLOT(setBackMusic(bool)));
    mySetMenu->hide();

    // 初始化游戏
    //initGame(BASIC);
}

MainGameWindow::~MainGameWindow()
{
    delete myMenu;

    delete ui;
}

void MainGameWindow::setMenu()
{
    myMenu->hide();

    mySetMenu->show();

 }
void MainGameWindow::backMenu1()
{
    mySetMenu->hide();
    myMenu->show();
}
void MainGameWindow::backMenu2()
{
    delete gamePlay;
    show();
    myMenu->show();
}

void MainGameWindow::setKeyMusic(bool mu)
{
    keyMusic=mu;
}
void MainGameWindow::setBackMusic(bool mu)
{
    backMusic=mu;
}

void MainGameWindow::initGame()
{
    // 启动游戏

    hide();

    gamePlay=new game_model2(this,level,keyMusic,backMusic);
    connect(gamePlay,SIGNAL(backToMenu()),this,SLOT(backMenu2()));
    connect(gamePlay,SIGNAL(again()),this,SLOT(again()));
    gamePlay->show();

    //back
}
void MainGameWindow::again()
{
    delete gamePlay;
    initGame();
}

void MainGameWindow::setMyLevel(int arg)
{
    if(arg==0)
    level=BASIC;
    else
        if(arg==1)
            level=MEDIUM;
    else
    if(arg==2)
    level=HARD;
}
