#include"game.h"
#include<main_game_window.cpp>
game::game(){

}
game::~game()
{

}
void game::setMenu()
{
    window=new QWidget;
    window->setWindowTitle("lIANLIANKAN");//设置标题
    window->setGeometry(300,300,600,800);//设置界面大小
    window->setFixedSize(800,600);
    //设置背景
    QPalette pal(window->palette());
    pal.setColor(QPalette::Background, Qt::black);
    window->setAutoFillBackground(true);
    window->setPalette(pal);

    //设置按钮——后续绘制按钮后添加Icon
    startButton=new QToolButton();
    startButton->setText("Start");
    startButton->setBaseSize(30,20);
    setButton=new QToolButton();
    setButton->setText("Set");
     setButton->setBaseSize(30,20);
    quitButton=new QToolButton();
    quitButton->setText("Quit");
     quitButton->setBaseSize(30,20);
    //设置垂直布局
    vLayout=new QVBoxLayout;
    vLayout->addWidget(startButton);
    vLayout->addWidget(setButton);
    vLayout->addWidget(quitButton);
    vLayout->setSpacing(30);
    vLayout->setContentsMargins(200,200,200,200);

    //设置横向布局
    hLayout=new QHBoxLayout;
    hLayout->addLayout(vLayout,Qt::AlignCenter);
    window->setLayout(hLayout);

    //关联按钮
    connect(startButton,SIGNAL(clicked()),this,SLOT(setGame()));
    connect(quitButton,SIGNAL(clicked(bool)),this,SLOT(QuitGame()));


    window->show();
}
void game::del_Menu()
{
    delete startButton;
    delete setButton;
    delete quitButton;
    delete hLayout;
    delete vLayout;
    delete window;
}

void game::setGame(){

    MainGameWindow gameWindow(window);
    window->hide();
    gameWindow.setVisible(true);
    gameWindow.show();
}
void game::QuitGame(){}
