#ifndef SETMENU_H
#define SETMENU_H

#include <QWidget>

namespace Ui {
class setmenu;
}

class setmenu : public QWidget
{
    Q_OBJECT

public:
    explicit setmenu(QWidget *parent = 0);
    ~setmenu();

signals:
    void backToMenu();
    void setLevel(int);
    void keyMusic(bool);
    void backMusic(bool);
private slots:
    void on_pushButton_clicked();


    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

private:
    Ui::setmenu *ui;
};

#endif // SETMENU_H
