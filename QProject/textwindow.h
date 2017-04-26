#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QTextStream>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui
{
class TextWindow;
}

class TextWindow : public QWidget
{
    Q_OBJECT

public slots:
    void stayEvent();
    void leaveEvent();

    void answerEvent();

    void showPocketEvent();
    void refuseEvent();

    void submitEvent();
    void apologyEvent();
    void callJerkEvent();

    void killEvent();
    void killRefuseEvent();

    void stayHomeEvent();
    void goToStationEvent();

    void goMetroEvent();
    void goBusEvent();

    void comeEvent();
    void comeRefuseEvent();

    void stayOnStationEvent();
    void enterEvent();

    void familyEvent();
    void tvEvent();

public:
    explicit TextWindow(QWidget *parent = 0);
    ~TextWindow();

    void openSave();

public slots:
    void gameTime();
    void nextFragment();
    void choices();
    void returnToMenu();
    void setAchievement(QString ach);
    void saveGame();

private:
    Ui::TextWindow *ui;

    void playMusic(QString filename);
    void muteMusic();
    QStringList readText(QFile &file);
    void setFragment(int pos);
    void setButtons();
    void addButtons();
    void createButtons();
    void setText(int pos);
    void disconnectButtons();

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QPushButton *choice1;
    QPushButton *choice2;
    QPushButton *choice3;
};

#endif // TEXTWINDOW_H
