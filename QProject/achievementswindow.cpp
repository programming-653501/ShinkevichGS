#include "achievementswindow.h"
#include "ui_achievementswindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

AchievementsWindow::AchievementsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AchievementsWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    getAchievements();

    connect(ui->backButton, &QPushButton::clicked,
	    this, &AchievementsWindow::returnToMenu);
}

AchievementsWindow::~AchievementsWindow()
{
    delete ui;
}

void AchievementsWindow::returnToMenu()
{
    this->close();
    MainWindow *menu = new MainWindow();
    menu->show();
}

void AchievementsWindow::getAchievements()
{
    QFile file("data\\achievements.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	return;

    QTextStream in(&file);
    QStringList achievements;
    while (!in.atEnd())
    {
	QString line = in.readLine();
	achievements.push_back(line);
    }

    for (int i = 0; i < achievements.size(); i++)
    {
	if (achievements.at(i) == "burn")
	{
	    ui->Burn_Ach->setText("Волнистое Барбекю");
	    ui->Burn_Ach->setToolTip("Сгореть в собственной квартире");
	}
	if (achievements.at(i) == "explode")
	{
	    ui->Explode_Ach->setText("Лучше Пешком");
	    ui->Explode_Ach->setToolTip("Погибнуть от взрыва в метро");
	}
	if (achievements.at(i) == "hit")
	{
	    ui->Hit_Ach->setText("Фарш");
	    ui->Hit_Ach->setToolTip("Погибнуть, переходя дорогу");
	}
	if (achievements.at(i) == "sad")
	{
	    ui->Sad_Ach->setText("Губительная нерешительность");
	    ui->Sad_Ach->setToolTip("Совершить суицид");
	}
	if (achievements.at(i) == "trip")
	{
	    ui->Trip_Ach->setText("Вечная дорога");
	    ui->Trip_Ach->setToolTip("Уехать в никуда");
	}
	if (achievements.at(i) == "happy")
	{
	    ui->Happy_Ach->setText("Счастье в неведении");
	    ui->Happy_Ach->setToolTip("Воссоединиться с семьей");
	}
	if (achievements.at(i) == "trueend")
	{
	    ui->TrueEnd_Ach->setText("Вредное ТВ");
	    ui->TrueEnd_Ach->setToolTip("Узнать правду");
	}
    }
}
