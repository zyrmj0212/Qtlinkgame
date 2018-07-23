#ifndef MAIN_GAME_WINDOW_H
#define MAIN_GAME_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>

#include"menu.h"
#include"setmenu.h"
#include"game_model2.h"

namespace Ui {
class MainGameWindow;
}

// 继承自button，存储坐标值


class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainGameWindow(QWidget *parent = 0);
    virtual ~MainGameWindow();


private:
    Ui::MainGameWindow *ui;

    menu *myMenu;
    setmenu *mySetMenu;
    game_model2 *gamePlay;
    GameLevel level;
    bool keyMusic;
    bool backMusic;
    QDialog * nameDialog;
    QString userName;

private slots:

    void initGame(); // 初始化游戏
    void setMenu();
    void backMenu1();
    void backMenu2();
    void setMyLevel(int);
    void setKeyMusic(bool);
    void setBackMusic(bool);
    void again();
};

#endif // MAIN_GAME_WINDOW_H
