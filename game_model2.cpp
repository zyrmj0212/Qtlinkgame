
#include<QDir>
#include <QDebug>
#include <QSound>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>
#include<QString>
#include<QGraphicsDropShadowEffect>
#include<time.h>
#include "game_model2.h"
#include "ui_game_model2.h"



// --------- ȫ�ֱ��� --------- //
const int kIconSize = 36;
const int kTopMargin = 150;
const int kLeftMargin = 50;

const QString kIconReleasedStyle = "";

//const QString kIconClickedStyle = "background-color: rgba(rand() % 256, rand() % 256, rand() % 256��161)";
const QString kIconHintStyle = "background-color: rgba(255, 237, 243 255)";


const int kGameTimeTotal = 5 * 60 * 1000; // ��ʱ��
const int kGameTimerInterval = 300;
const int kLinkTimerDelay = 700;
const int kChange=10;
// -------------------------- //


game_model2::game_model2(QWidget *parent,GameLevel level,bool a,bool b) :
    QMainWindow(parent),keyMusicg(a),backMusicg(b),
    ui(new Ui::game_model2)
{
    preIcon=NULL;
    curIcon=NULL;
    ui->setupUi(this);
    score=0;
    myLevel=level;
    game = new GameModel;
    game->startGame(myLevel);
    ui->centralwidget->installEventFilter(this);
    // ���button
    for(int i = 0; i < MAX_ROW * MAX_COL; i++)
    {
        imageButton[i] = new IconButton(this);
        imageButton[i]->setGeometry(kLeftMargin + (i % MAX_COL) * kIconSize, kTopMargin + (i / MAX_COL) * kIconSize, kIconSize, kIconSize);
        // ��������
        imageButton[i]->xID = i % MAX_COL;
        imageButton[i]->yID = i / MAX_COL;

        imageButton[i]->show();

        if (game->getGameMap()[i])
        {
            // �з��������ͼƬ
            QPixmap iconPix;
            QString fileString;
            fileString.sprintf(":/%d.jpg", game->getGameMap()[i]);
            iconPix.load(fileString);
            QIcon icon(iconPix);
            imageButton[i]->setIcon(icon);
            imageButton[i]->setIconSize(QSize(kIconSize, kIconSize));

            // ��Ӱ��µ��źŲ�
            connect(imageButton[i], SIGNAL(pressed()), this, SLOT(onIconButtonPressed()));
        }
        else
            imageButton[i]->hide();
    }

    // ������
    ui->timeBar->setMaximum(kGameTimeTotal);
    ui->timeBar->setMinimum(0);
    ui->timeBar->setValue(kGameTimeTotal);

    // ��Ϸ��ʱ��
    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    gameTimer->start(kGameTimerInterval);


    // ����״ֵ̬
    isLinking = false;

    // ���ű�������(QMediaPlayerֻ�ܲ��ž���·���ļ�),ȷ��res�ļ��ڳ���ִ���ļ�Ŀ¼������ǿ���Ŀ¼

    if(backMusicg==true)
    {
        QString str;
        if(myLevel==BASIC)
        str.sprintf(".\\res\\sound\\background%d.mp3",1);
        else
            if(myLevel==MEDIUM)
        str.sprintf(".\\res\\sound\\background%d.mp3",2);
        else
                if(myLevel==HARD)
        str.sprintf(".\\res\\sound\\background%d.mp3",3);
        QDir temDir(str);
        QString absDir = temDir.absolutePath();
        absDir.replace(QString("/"), QString("\\"));
    audioPlayer = new QMediaPlayer(this);
   // QString curDir = QCoreApplication::applicationDirPath(); // ���api��ȡ·���ڲ�ͬϵͳ�²�һ��,mac ����Ҫ��ȡ·��
    //QStringList sections = curDir.split(QRegExp("[/]"));
    //QString musicPath;

    //for (int i = 0; i < sections.size() - 3; i++)
       // musicPath += sections[i] + "/";
//QUrl::fromLocalFile(musicPath + "res/sound/background1.mp3")
    audioPlayer->setMedia(QUrl::fromLocalFile(absDir));
    audioPlayer->setVolume(30);
    audioPlayer->play();
    }



}

game_model2::~game_model2()
{
    delete ui;
}

void game_model2::on_pushButton_clicked()
{
    emit backToMenu();


}


void game_model2::onIconButtonPressed()
{
    // �����ǰ�з��������ӣ����ܵ������
    // ��Ϊ�漰�����ߣ����ܻ�Ҫά�����У��е㸴�ӣ�������ô�򵥴���һ��
    if (isLinking)
    {
        // ������Ч
        if(keyMusicg==true)
        QSound::play(":/res/sound/release.wav");
        return;
    }


    // ��¼��ǰ�����icon
    curIcon = dynamic_cast<IconButton *>(sender());

    //QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    //shadow_effect->setOffset(5, 5);
    //shadow_effect->setColor(QColor(43, 43, 43));
    //shadow_effect->setBlurRadius(8);
    //curIcon->setGraphicsEffect(shadow_effect);
    curIcon->setStyleSheet(kIconClickedStyle());
    curIcon->setIconSize(QSize(kIconSize-kChange,kIconSize-kChange));

    if(!preIcon)
    {
        // ������Ч
                if(keyMusicg==true)
        QSound::play(":/res/sound/select.wav");

        // �������һ��icon
        //curIcon->setStyleSheet(kIconClickedStyle);
        //curIcon->setIconSize(QSize(kIconSize-kChange,kIconSize-kChange));

        preIcon = curIcon;
    }
    else
    {
        if(curIcon != preIcon)
        {
            // �������ͬһ��button�Ͷ����,��������
            //curIcon->setStyleSheet(kIconClickedStyle);
            if(game->linkTwoTiles(preIcon->xID, preIcon->yID, curIcon->xID, curIcon->yID))
            {
                // ��ס��ǰ״̬
                isLinking = true;

                // ������Ч
                        if(keyMusicg==true)
                QSound::play(":/res/sound/pair.wav");

                // �ػ�
                update();

                // �ӳٺ�ʵ������Ч��
                QTimer::singleShot(kLinkTimerDelay, this, SLOT(handleLinkEffect()));
                score+=2;
                QString sco;
                sco.sprintf("Scores:  %d",score);
                ui->label_2->setText(sco);
                // ÿ�μ��һ���Ƿ񽩾�
                if (game->isFrozen())
                   {
                    QMessageBox::information(this, "oops", "dead game!");
                    gameTimer->stop();
                }
                // ����Ƿ�ʤ��
                if (game->isWin())
                 {
                    QMessageBox::information(this, "great", "you win!");
                    gameTimer->stop();
                }
                int *hints = game->getHint();
            }
            else
            {
                // ������Ч
                        if(keyMusicg==true)
                QSound::play(":/res/sound/release.wav");

                // ����ʧ�ܣ��ָ�
                preIcon->setStyleSheet(kIconReleasedStyle);
                curIcon->setStyleSheet(kIconReleasedStyle);
                curIcon->setIconSize(QSize(kIconSize,kIconSize));
                preIcon->setIconSize(QSize(kIconSize,kIconSize));

                // ָ���ÿգ������´ε���ж�
                preIcon = NULL;
                curIcon = NULL;
            }
        }
        else if(curIcon == preIcon)
        {
            // ������Ч

            if(keyMusicg==true)
            QSound::play(":/res/sound/release.wav");

            preIcon->setStyleSheet(kIconReleasedStyle);
            curIcon->setStyleSheet(kIconReleasedStyle);
            curIcon->setIconSize(QSize(kIconSize,kIconSize));
            preIcon->setIconSize(QSize(kIconSize,kIconSize));
            preIcon = NULL;
            curIcon = NULL;
        }
    }
}

void game_model2::handleLinkEffect()
{
    // �����ɹ������ص���������
    game->paintPoints.clear();
    preIcon->hide();
    curIcon->hide();

    preIcon = NULL;
    curIcon = NULL;

    // �ػ�
    update();

    // �ָ�״̬
    isLinking = false;
}

bool game_model2::eventFilter(QObject *watched, QEvent *event)
{
    // �ػ�ʱ����ã������ֶ�����
    if (event->type() == QEvent::Paint)
    {
        QPainter painter(ui->centralwidget);
        QPen pen;
        QColor color(rand() % 256, rand() % 256, rand() % 256);
        pen.setColor(color);
        pen.setWidth(5);
        painter.setPen(pen);

        QString str;
        for (int i = 0; i < game->paintPoints.size(); i++)
        {
            PaintPoint p = game->paintPoints[i];
            str += "x:" + QString::number(p.x) + "y:" + QString::number(p.y) + "->";
        }
//        qDebug() << str;

        // ���Ӹ��㻭�ߣ�ע��qt���ñ�שvector��size�����е����⣬��Ҫ����ת�������������
        for (int i = 0; i < int(game->paintPoints.size()) - 1; i++)
        {
            PaintPoint p1 = game->paintPoints[i];
            PaintPoint p2 = game->paintPoints[i + 1];

            // �õ���button������,ע���Ե������
            QPoint btn_pos1;
            QPoint btn_pos2;

            // p1
            if (p1.x == -1)
            {
                btn_pos1 = imageButton[p1.y * MAX_COL + 0]->pos();
                btn_pos1 = QPoint(btn_pos1.x() - kIconSize, btn_pos1.y());
            }
            else if (p1.x == MAX_COL)
            {
                btn_pos1 = imageButton[p1.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos1 = QPoint(btn_pos1.x() + kIconSize, btn_pos1.y());
            }
            else if (p1.y == -1)
            {
                btn_pos1 = imageButton[0 + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() - kIconSize);
            }
            else if (p1.y == MAX_ROW)
            {
                btn_pos1 = imageButton[(MAX_ROW - 1) * MAX_COL + p1.x]->pos();
                btn_pos1 = QPoint(btn_pos1.x(), btn_pos1.y() + kIconSize);
            }
            else
                btn_pos1 = imageButton[p1.y * MAX_COL + p1.x]->pos();

            // p2
            if (p2.x == -1)
            {
                btn_pos2 = imageButton[p2.y * MAX_COL + 0]->pos();
                btn_pos2 = QPoint(btn_pos2.x() - kIconSize, btn_pos2.y());
            }
            else if (p2.x == MAX_COL)
            {
                btn_pos2 = imageButton[p2.y * MAX_COL + MAX_COL - 1]->pos();
                btn_pos2 = QPoint(btn_pos2.x() + kIconSize, btn_pos2.y());
            }
            else if (p2.y == -1)
            {
                btn_pos2 = imageButton[0 + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() - kIconSize);
            }
            else if (p2.y == MAX_ROW)
            {
                btn_pos2 = imageButton[(MAX_ROW - 1) * MAX_COL + p2.x]->pos();
                btn_pos2 = QPoint(btn_pos2.x(), btn_pos2.y() + kIconSize);
            }
            else
                btn_pos2 = imageButton[p2.y * MAX_COL + p2.x]->pos();



            // ���ĵ�
            QPoint pos1(btn_pos1.x() + kIconSize / 2, btn_pos1.y() + kIconSize / 2);
            QPoint pos2(btn_pos2.x() + kIconSize / 2, btn_pos2.y() + kIconSize / 2);

            painter.drawLine(pos1, pos2);
        }

        return true;
    }
    else
        return QMainWindow::eventFilter(watched, event);
}

void game_model2::gameTimerEvent()
{
    // ��������ʱЧ��
    if(ui->timeBar->value() == 0)
    {
        gameTimer->stop();
        QMessageBox::information(this, "game over", "play again>_<");
    }
    else
    {
        ui->timeBar->setValue(ui->timeBar->value() - kGameTimerInterval);
    }

}

// ��ʾ
void game_model2::on_hintBtn_clicked()
{
    // ��ʼʱ���ܻ����ʾ
    for (int i = 0; i < 4;i++)
        if (game->getHint()[i] == -1)
            return;

    int srcX = game->getHint()[0];
    int srcY = game->getHint()[1];
    int dstX = game->getHint()[2];
    int dstY = game->getHint()[3];

    IconButton *srcIcon = imageButton[srcY * MAX_COL + srcX];
    IconButton *dstIcon = imageButton[dstY * MAX_COL + dstX];
    srcIcon->setStyleSheet(kIconHintStyle);
    dstIcon->setStyleSheet(kIconHintStyle);

    srcIcon->setIconSize(QSize(kIconSize-kChange,kIconSize-kChange));
    dstIcon->setIconSize(QSize(kIconSize-kChange,kIconSize-kChange));
    if(keyMusicg==true)
    QSound::play(":/res/sound/pair.wav");
    //�ӳ�һ��
    QEventLoop eventloop;
    QTimer::singleShot(1000, &eventloop, SLOT(quit()));
    eventloop.exec();
    srcIcon->setIconSize(QSize(kIconSize,kIconSize));
    dstIcon->setIconSize(QSize(kIconSize,kIconSize));

}

void game_model2::on_robot_btn_clicked()
{
    // ��ʼʱ�����Զ���
    for (int i = 0; i < 4;i++)
        if (game->getHint()[i] == -1)
            return;

    while (game->gameStatus == PLAYING)
    {
        // ����������ʾ

        int srcX = game->getHint()[0];
        int srcY = game->getHint()[1];
        int dstX = game->getHint()[2];
        int dstY = game->getHint()[3];

        if(game->linkTwoTiles(srcX, srcY, dstX, dstY))
        {
            // ������Ч
//            QSound::play(":/res/sound/pair.wav");

            // �����ɹ������ص�
            IconButton *icon1 = imageButton[srcY * MAX_COL + srcX];
            IconButton *icon2 = imageButton[dstY * MAX_COL + dstX];

            icon1->hide();
            icon2->hide();

            game->paintPoints.clear();

            // �ػ�
            update();

            // ����Ƿ�ʤ��
            if (game->isWin())
                QMessageBox::information(this, "great", "you win");

            // ÿ�μ��һ���Ƿ񽩾�
            if (game->isFrozen() && game->gameStatus == PLAYING)
                QMessageBox::information(this, "oops", "dead game");



            int *hints = game->getHint();
        }
    }
}

void game_model2::createGameWithLevel()
{
    // ������֮ǰ��
    if (game)
    {
        delete game;
        for (int i = 0;i < MAX_ROW * MAX_COL; i++)
        {
            if (imageButton[i])
               delete imageButton[i];
        }
    }

    // ֹͣ����
    audioPlayer->stop();

    // �ػ�
    update();

   // QAction *actionSender = (QAction *)dynamic_cast<QAction *>(sender());
    //if (actionSender == ui->actionBasic)
    //{
        //initGame(BASIC);
    //}
    //else if (actionSender == ui->actionMedium)
    //{
        //initGame(MEDIUM);
    //}
    //else if (actionSender == ui->actionHard)
    //{
        //initGame(HARD);
   //}

}


QString game_model2::kIconClickedStyle()
{
    QString color;
    srand((unsigned)time(NULL));
    int r=rand()%255;
    int g=rand()%255;
    int b=rand()%255;

    color.sprintf("background-color: rgba(%d,%d,%d,161)",r, g, b);
    return color;

}



void game_model2::on_pushButton_2_clicked()
{
    emit again();
}
