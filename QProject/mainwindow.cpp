#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textwindow.h"
#include "achievementswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->newGameButton, &QPushButton::clicked,
	    this, &MainWindow::startGame);

    connect(ui->quitButton, &QPushButton::clicked,
	    this, &MainWindow::closeGame);

    connect(ui->achievementsButton, &QPushButton::clicked,
	    this, &MainWindow::showAchievements);

    connect(ui->continueButton, &QPushButton::clicked,
	    this, &MainWindow::continueGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    clearSave();
    this->close();
    TextWindow *t_window = new TextWindow();
    t_window->show();
}

void MainWindow::closeGame()
{
    this->close();
}

void MainWindow::showAchievements()
{
    this->close();
    AchievementsWindow *a_window = new AchievementsWindow();
    a_window->show();
}

void MainWindow::continueGame()
{
    this->close();
    TextWindow *t_window = new TextWindow();
    t_window->openSave();
    t_window->show();
}

void MainWindow::clearSave()
{
    QFile file("data\\save.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	return;

    QTextStream stream(&file);
    stream << 0 << "\n" << 0;
}
