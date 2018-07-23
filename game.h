#ifndef GAME_H
#define GAME_H

#include<QToolButton>
#include<QVBoxLayout>
#include<QHBoxLayout>

//#include<button.cpp>
//------------全局变量------------
const int MAX_W=20;
const int MAX_H=15;






//game类
class game:public QObject
{
    Q_OBJECT
private:
    QWidget * window;
public:
    game();
    ~game();
    //主菜单
    void setMenu();
    void del_Menu();

    //主菜单按钮
    QToolButton *startButton;
    QToolButton *setButton;
    QToolButton *quitButton;

    //主菜单布局
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    
    //图形数据地图
    int map[MAX_W][MAX_H];
public slots:
    void setGame();
    void QuitGame();
};

#endif // GAME_H
