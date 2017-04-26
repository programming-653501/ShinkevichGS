#include "textwindow.h"
#include "ui_textwindow.h"

#include "mainwindow.h"


int minutes;
int seconds;

int position;
QStringList text;

int trueEnd;

TextWindow::TextWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);

    minutes = 0;
    seconds = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
	    this, &TextWindow::gameTime);

    timer->start(1000);

    playMusic("sounds\\Creepy Hollow.mp3");

    ui->setupUi(this);

    ui->saveLabel->hide();
    ui->timeLabel->setText(QString::number(minutes) + " мин, " + QString::number(seconds) + " сек");


    connect(ui->quitButton, &QPushButton::clicked,
	    this, &TextWindow::returnToMenu);

    connect(ui->quitButton, &QPushButton::clicked,
	    this, &TextWindow::saveGame);

    connect(ui->nextButton, &QPushButton::clicked,
	    this, &TextWindow::nextFragment);

    connect(ui->nextButton, &QPushButton::clicked,
	    this, &TextWindow::choices);

    connect(ui->nextButton, &QPushButton::clicked,
	    ui->saveLabel, &QLabel::hide);

    connect(ui->saveButton, &QPushButton::clicked,
	    this, &TextWindow::saveGame);

    connect(ui->soundButton, &QPushButton::clicked,
	    this, &TextWindow::muteMusic);


    createButtons();
    addButtons();
    setButtons();


    QString filename = ":/text/scenario.txt";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
	returnToMenu();
	return;
    }

    text = readText(file);


    position = 0;
    setFragment(position);

    trueEnd = 0;
}

TextWindow::~TextWindow()
{
    delete ui;
}

void TextWindow::playMusic(QString filename)
{
    playlist = new QMediaPlaylist;

    playlist->addMedia(QUrl::fromLocalFile(filename));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer;

    player->setPlaylist(playlist);

    player->play();
}

void TextWindow::muteMusic()
{
    if (player->volume() > 0)
    {
	player->setVolume(0);
	ui->soundButton->setText("Музыка: ВЫКЛ");
    }
    else
    {
	player->setVolume(100);
	ui->soundButton->setText("Музыка: ВКЛ");
    }
}

void TextWindow::saveGame()
{
    QFile file("data\\save.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
	ui->saveLabel->setText("Ошибка!");
	ui->saveLabel->show();
	return;
    }

    QTextStream stream(&file);
    stream << position - 1 << "\n" << trueEnd;
    ui->saveLabel->show();
}

void TextWindow::openSave()
{
    QFile file("data\\save.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
	returnToMenu();
	return;
    }

    QTextStream stream(&file);
    stream >> position >> trueEnd;
    ui->textBrowser->setText("Загружено...");
}

void TextWindow::gameTime()
{
    if (seconds == 60)
    {
	seconds = 0;
	minutes++;
    }
    ui->timeLabel->setText(QString::number(minutes) + " мин, " + QString::number(seconds) + " сек");
    seconds++;
}

void TextWindow::returnToMenu()
{
    player->stop();
    this->close();
    MainWindow *menu = new MainWindow();
    menu->show();
}

QStringList TextWindow::readText(QFile &file)
{
    QTextStream in(&file);
    QString fragment;

    while (!in.atEnd())
	fragment = in.readAll();

    QStringList text;
    text = fragment.split("\n\n", QString::SkipEmptyParts);

    return text;
}

void TextWindow::setAchievement(QString ach)
{
    QFile file("data\\achievements.dat");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
	return;

    QTextStream stream(&file);
    bool exist = false;
    while (!stream.atEnd())
    {
	QString line = stream.readLine();
	if (line == ach)
	{
	    exist = true;
	    break;
	}
    }
    if (!exist)
	stream << ach << "\n";
}

void TextWindow::nextFragment()
{
    setFragment(position + 1);
    position++;
}

void TextWindow::setFragment(int pos)
{
    ui->textBrowser->setText(text.at(pos));
}

void TextWindow::setText(int pos)
{
    setFragment(pos);
    position = pos;
}

void TextWindow::addButtons()
{
    ui->decisionsLayout->addWidget(choice1);
    ui->decisionsLayout->addWidget(choice2);
    ui->decisionsLayout->addWidget(choice3);
}

void TextWindow::createButtons()
{
    choice1 = new QPushButton();
    choice2 = new QPushButton();
    choice3 = new QPushButton();

    choice1->setStyleSheet("QPushButton { border-style: solid;"
			   "border-radius: 0px;"
			   "background-color: rgb(170, 0, 0); "
			   "font-weight: bold; }"
			   "QPushButton:hover{ background-color: red; }");

    choice2->setStyleSheet("QPushButton { border-style: solid;"
			   "border-radius: 0px;"
			   "background-color: rgb(170, 0, 0);"
			   "font-weight: bold; }"
			   "QPushButton:hover{ background-color: red; }");

    choice3->setStyleSheet("QPushButton { border-style: solid;"
			   "border-radius: 0px;"
			   "background-color: rgb(170, 0, 0);"
			   "font-weight: bold; }"
			   "QPushButton:hover{ background-color: red; }");

    connect(choice1, &QPushButton::clicked,
	    this, &TextWindow::choices);

    connect(choice2, &QPushButton::clicked,
	    this, &TextWindow::choices);

    connect(choice3, &QPushButton::clicked,
	    this, &TextWindow::choices);
}

void TextWindow::setButtons()
{
    choice1->hide();
    choice2->hide();
    choice3->hide();
    ui->nextButton->show();
}

void TextWindow::disconnectButtons()
{
    disconnect(choice1, &QPushButton::clicked, 0, 0);
    disconnect(choice2, &QPushButton::clicked, 0, 0);
    disconnect(choice3, &QPushButton::clicked, 0, 0);
}

void TextWindow::choices()
{
    if (position == 6)
    {
	ui->nextButton->hide();

	choice1->setText("Остаться");
	choice2->setText("Уйти");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::stayEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::leaveEvent);
    }

    if (position == 15)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Не знаю");
	choice2->setText("Нет");
	choice3->setText("Отстань от меня");

	choice1->show();
	choice2->show();
	choice3->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::answerEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::answerEvent);

	connect(choice3, &QPushButton::clicked,
		this, &TextWindow::answerEvent);
    }

    if (position == 25)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Показать содержимое карманов");
	choice2->setText("Отказать");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::showPocketEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::refuseEvent);
    }

    if (position == 53)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Смириться");
	choice2->setText("Просить прощения");
	choice3->setText("Обозвать му***ом");

	choice1->show();
	choice2->show();
	choice3->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::submitEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::apologyEvent);

	connect(choice3, &QPushButton::clicked,
		this, &TextWindow::callJerkEvent);
    }

    if (position == 56 || position == 60)
	setText(67);

    if (position == 83)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Снять маску");
	choice2->setText("Отказать");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::killEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::killRefuseEvent);
    }

    if (position == 87)
	setText(94);

    if (position == 119)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("...я остался.");
	choice2->setText("...я пошел.");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::stayHomeEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::goToStationEvent);
    }

    if (position == 132)
    {
	ui->textBrowser->setText("Достижение: Волнистое Барбекю");
	setAchievement("burn");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 134)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Метро");
	choice2->setText("Автобус");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::goMetroEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::goBusEvent);
    }

    if (position == 145)
    {
	ui->textBrowser->setText("Достижение: Лучше Пешком");
	setAchievement("explode");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 151)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Зайти к подруге");
	choice2->setText("Отказать");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::comeEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::comeRefuseEvent);
    }

    if (position == 158)
    {
	ui->textBrowser->setText("Достижение: Фарш");
	setAchievement("hit");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 164)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Остаться");
	choice2->setText("Сесть в травмай");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::stayOnStationEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::enterEvent);
    }

    if (position == 169)
    {
	ui->textBrowser->setText("Достижение: Губительная Нерешительность");
	setAchievement("sad");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 172 && trueEnd == 8)
	setText(181);

    if (position == 181 && trueEnd != 8)
    {
	ui->textBrowser->setText("Достижение: Вечная Дорога");
	setAchievement("trip");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 189)
    {
	disconnectButtons();

	ui->nextButton->hide();

	choice1->setText("Пообщаться с семьей");
	choice2->setText("Посмотреть телевизор");

	choice1->show();
	choice2->show();

	connect(choice1, &QPushButton::clicked,
		this, &TextWindow::familyEvent);

	connect(choice2, &QPushButton::clicked,
		this, &TextWindow::tvEvent);
    }

    if (position == 193)
    {
	ui->textBrowser->setText("Достижение: Счастье в Неведении");
	setAchievement("happy");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }

    if (position == 199)
    {
	ui->textBrowser->setText("Достижение: Вредное ТВ");
	setAchievement("trueend");
	connect(ui->nextButton, &QPushButton::clicked,
		this, &TextWindow::returnToMenu);
    }
}

void TextWindow::stayEvent()
{
    trueEnd++;
    setText(7);
    setButtons();
}

void TextWindow::leaveEvent()
{
    setText(10);
    setButtons();
}

void TextWindow::answerEvent()
{
    setText(16);
    setButtons();
}

void TextWindow::showPocketEvent()
{
    setText(26);
    setButtons();
    trueEnd++;
}

void TextWindow::refuseEvent()
{
    setText(29);
    setButtons();
}

void TextWindow::submitEvent()
{
    setText(54);
    setButtons();
}

void TextWindow::apologyEvent()
{
    setText(56);
    setButtons();
}

void TextWindow::callJerkEvent()
{
    trueEnd++;
    setText(60);
    setButtons();
}

void TextWindow::killEvent()
{
    setText(84);
    setButtons();
}

void TextWindow::killRefuseEvent()
{
    trueEnd++;
    setText(87);
    setButtons();
}

void TextWindow::stayHomeEvent()
{
    setText(120);
    setButtons();
}

void TextWindow::goToStationEvent()
{
    trueEnd++;
    setText(132);
    setButtons();
}

void TextWindow::goMetroEvent()
{
    setText(135);
    setButtons();
}

void TextWindow::goBusEvent()
{
    trueEnd++;
    setText(145);
    setButtons();
}

void TextWindow::comeEvent()
{
    setText(152);
    setButtons();
}

void TextWindow::comeRefuseEvent()
{
    trueEnd++;
    setText(158);
    setButtons();
}

void TextWindow::stayOnStationEvent()
{
    setText(165);
    setButtons();
}

void TextWindow::enterEvent()
{
    trueEnd++;
    setText(169);
    setButtons();
}

void TextWindow::familyEvent()
{
    setText(190);
    setButtons();
}

void TextWindow::tvEvent()
{
    setText(193);
    setButtons();
}
