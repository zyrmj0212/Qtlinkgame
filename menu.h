#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    virtual ~menu();

signals:
    void startplay();
    //void quitGame();
    void setMenuf();

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_set_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
