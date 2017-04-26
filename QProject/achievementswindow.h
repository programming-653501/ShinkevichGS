#ifndef ACHIEVEMENTSWINDOW_H
#define ACHIEVEMENTSWINDOW_H

#include <QWidget>

namespace Ui
{
class AchievementsWindow;
}

class AchievementsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementsWindow(QWidget *parent = 0);
    ~AchievementsWindow();

public slots:
    void returnToMenu();

private:
    Ui::AchievementsWindow *ui;

    void getAchievements();
};

#endif // ACHIEVEMENTSWINDOW_H
