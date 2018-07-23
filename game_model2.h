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
    int xID; // x 坐标
    int yID; // y 坐标
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

    virtual bool eventFilter(QObject *watched, QEvent *event); // 事件过滤

     GameModel *game; // 游戏模型
    GameLevel myLevel;
    int score;//分数
    QString userName;
    IconButton *imageButton[MAX_ROW * MAX_COL]; // 图片button数组
    IconButton *preIcon,*curIcon;
    QTimer *gameTimer; // 游戏计时器
    bool isLinking; // 维持一个连接状态的标志
    QMediaPlayer *audioPlayer; // 音乐播放器
    bool keyMusicg;
    bool backMusicg;
    QString kIconClickedStyle();

    void setKeyMusicg(bool);
    void setBackMusicg(bool);
private slots:

    void onIconButtonPressed(); // icon点击到响应
    void gameTimerEvent(); // 游戏计时回调
    void handleLinkEffect(); // 实现连接效果
    void on_hintBtn_clicked(); // 提示按钮
    void on_robot_btn_clicked(); // 机器人自动刷
    void createGameWithLevel(); // 选中难度开始
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::game_model2 *ui;

signals:
    void backToMenu();
    void again();

};

#endif // GAME_MODEL2_H
