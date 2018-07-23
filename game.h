#ifndef GAME_H
#define GAME_H

#include<QToolButton>
#include<QVBoxLayout>
#include<QHBoxLayout>

//#include<button.cpp>
//------------ȫ�ֱ���------------
const int MAX_W=20;
const int MAX_H=15;






//game��
class game:public QObject
{
    Q_OBJECT
private:
    QWidget * window;
public:
    game();
    ~game();
    //���˵�
    void setMenu();
    void del_Menu();

    //���˵���ť
    QToolButton *startButton;
    QToolButton *setButton;
    QToolButton *quitButton;

    //���˵�����
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    
    //ͼ�����ݵ�ͼ
    int map[MAX_W][MAX_H];
public slots:
    void setGame();
    void QuitGame();
};

#endif // GAME_H
