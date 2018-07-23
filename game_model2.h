#ifndef GAME_MODEL2_H
#define GAME_MODEL2_H

#include <QMainWindow>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include "game_model.h"
#include"menu.h"
#include"setmenu.h"


struct IconButton : QPushButton
{
public:
    IconButton(QWidget *parent = Q_NULLPTR) :
        QPushButton(parent),
        xID(-1),
        yID(-1)
    {
    }
    int xID; // x ����
    int yID; // y ����
};
namespace Ui {
class game_model2;
}

class game_model2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit game_model2(QWidget *parent = 0,GameLevel level=BASIC,bool a=true,bool b=true);
    ~game_model2();

    virtual bool eventFilter(QObject *watched, QEvent *event); // �¼�����

     GameModel *game; // ��Ϸģ��
    GameLevel myLevel;
    int score;//����
    QString userName;
    IconButton *imageButton[MAX_ROW * MAX_COL]; // ͼƬbutton����
    IconButton *preIcon,*curIcon;
    QTimer *gameTimer; // ��Ϸ��ʱ��
    bool isLinking; // ά��һ������״̬�ı�־
    QMediaPlayer *audioPlayer; // ���ֲ�����
    bool keyMusicg;
    bool backMusicg;
    QString kIconClickedStyle();

    void setKeyMusicg(bool);
    void setBackMusicg(bool);
private slots:

    void onIconButtonPressed(); // icon�������Ӧ
    void gameTimerEvent(); // ��Ϸ��ʱ�ص�
    void handleLinkEffect(); // ʵ������Ч��
    void on_hintBtn_clicked(); // ��ʾ��ť
    void on_robot_btn_clicked(); // �������Զ�ˢ
    void createGameWithLevel(); // ѡ���Ѷȿ�ʼ
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::game_model2 *ui;

signals:
    void backToMenu();
    void again();

};

#endif // GAME_MODEL2_H
