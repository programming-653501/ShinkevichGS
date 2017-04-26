#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startGame();
    void closeGame();
    void showAchievements();
    void continueGame();

private:
    Ui::MainWindow *ui;

    void clearSave();
};

#endif // MAINWINDOW_H
