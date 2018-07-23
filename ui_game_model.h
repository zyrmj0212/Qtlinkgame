/********************************************************************************
** Form generated from reading UI file 'game_model.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_MODEL_H
#define UI_GAME_MODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_model
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *game_model)
    {
        if (game_model->objectName().isEmpty())
            game_model->setObjectName(QStringLiteral("game_model"));
        game_model->resize(320, 240);
        menubar = new QMenuBar(game_model);
        menubar->setObjectName(QStringLiteral("menubar"));
        game_model->setMenuBar(menubar);
        centralwidget = new QWidget(game_model);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        game_model->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(game_model);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        game_model->setStatusBar(statusbar);

        retranslateUi(game_model);

        QMetaObject::connectSlotsByName(game_model);
    } // setupUi

    void retranslateUi(QMainWindow *game_model)
    {
        game_model->setWindowTitle(QApplication::translate("game_model", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class game_model: public Ui_game_model {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_MODEL_H
