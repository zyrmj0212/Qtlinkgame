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
    window->setWindowTitle("lIANLIANKAN");//���ñ���
    window->setGeometry(300,300,600,800);//���ý����С
    window->setFixedSize(800,600);
    //���ñ���
    QPalette pal(window->palette());
    pal.setColor(QPalette::Background, Qt::black);
    window->setAutoFillBackground(true);
    window->setPalette(pal);

    //���ð�ť�����������ư�ť�����Icon
    startButton=new QToolButton();
    startButton->setText("Start");
    startButton->setBaseSize(30,20);
    setButton=new QToolButton();
    setButton->setText("Set");
     setButton->setBaseSize(30,20);
    quitButton=new QToolButton();
    quitButton->setText("Quit");
     quitButton->setBaseSize(30,20);
    //���ô�ֱ����
    vLayout=new QVBoxLayout;
    vLayout->addWidget(startButton);
    vLayout->addWidget(setButton);
    vLayout->addWidget(quitButton);
    vLayout->setSpacing(30);
    vLayout->setContentsMargins(200,200,200,200);

    //���ú��򲼾�
    hLayout=new QHBoxLayout;
    hLayout->addLayout(vLayout,Qt::AlignCenter);
    window->setLayout(hLayout);

    //������ť
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
