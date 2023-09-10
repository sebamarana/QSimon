#include "optionswidget.h"
#include "mainwindow.h"

OptionsWidget::OptionsWidget(QWidget * parent) : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setMinimumSize(500,500);

    speed = 700;

    //Buttons defaults
    up = new UpButton();
    down = new DownButton();
    right = new RightButton();
    left = new LeftButton();

    up->setDefaultColors();
    down->setDefaultColors();
    right->setDefaultColors();
    left->setDefaultColors();

    up->setSound(":/sounds/Sounds/Up.wav");
    down->setSound(":/sounds/Sounds/Down.wav");
    right->setSound(":/sounds/Sounds/Right.wav");
    left->setSound(":/sounds/Sounds/Left.wav");

    Buttons.push_back(*up);
    Buttons.push_back(*down);
    Buttons.push_back(*right);
    Buttons.push_back(*left);
    //-----------------------------

    //Layout and settings

    //Font Settings
    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);

    // Labels
    buttonsLabel.setText("Select Color Combo");
    buttonsLabel.setFont(QFont(pretty));
    buttonsLabel.setStyleSheet("color: white; font-size:17px;");

    difficultyLabel.setText("Select Difficulty");
    difficultyLabel.setFont(QFont(pretty));
    difficultyLabel.setStyleSheet("color: white; font-size:17px;");

    //Button

    returnMenu.setText("RETURN");
    returnMenu.setFont(QFont(pretty));
    returnMenu.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(50,205,50,1.000);} QPushButton:hover{background:rgba(0,100,0,1.000);}");
    returnMenu.setCursor(Qt::PointingHandCursor);
    returnMenu.setFixedSize(200, 50);

    //CheckBoxes

    buttons.setParent(this);
    difficulties.setParent(this);

    button1Box.setText("Normal");
    button1Box.setFont(QFont(pretty));
    button1Box.setStyleSheet("color: white; font-size:22px;");

    button2Box.setText("Neon");
    button2Box.setFont(QFont(pretty));
    button2Box.setStyleSheet("color: white; font-size:22px;");

    button3Box.setText("Mono");
    button3Box.setFont(QFont(pretty));
    button3Box.setStyleSheet("color: white; font-size:22px;");

    buttons.addButton(&button1Box,1);
    buttons.addButton(&button2Box,2);
    buttons.addButton(&button3Box,3);

    button1Box.setChecked(true);

    difficulty1Box.setText("Easy");
    difficulty1Box.setFont(QFont(pretty));
    difficulty1Box.setStyleSheet("color: white; font-size:22px;");

    difficulty2Box.setText("Normal");
    difficulty2Box.setFont(QFont(pretty));
    difficulty2Box.setStyleSheet("color: white; font-size:22px;");

    difficulty3Box.setText("Hard");
    difficulty3Box.setFont(QFont(pretty));
    difficulty3Box.setStyleSheet("color: white; font-size:22px;");

    difficulties.addButton(&difficulty1Box,1);
    difficulties.addButton(&difficulty2Box,2);
    difficulties.addButton(&difficulty3Box,3);

    difficulty2Box.setChecked(true);

    //Layouts
    firstVLayout.setAlignment(Qt::AlignLeft);
    secondVLayout.setAlignment(Qt::AlignLeft);

    firstVLayout.addWidget(&buttonsLabel,0,Qt::AlignLeft);
    firstVLayout.addWidget(&button1Box,0,Qt::AlignCenter);
    firstVLayout.addWidget(&button2Box,0,Qt::AlignCenter);
    firstVLayout.addWidget(&button3Box,0,Qt::AlignCenter);

    secondVLayout.addWidget(&difficultyLabel,0,Qt::AlignCenter);
    secondVLayout.addWidget(&difficulty1Box,0,Qt::AlignCenter);
    secondVLayout.addWidget(&difficulty2Box,0,Qt::AlignCenter);
    secondVLayout.addWidget(&difficulty3Box,0,Qt::AlignCenter);

    mainHLayout.addLayout(&firstVLayout,0);
    mainHLayout.addSpacing(10);
    mainHLayout.addLayout(&secondVLayout,0);

    mainVLayout.addLayout(&mainHLayout,0);
    mainVLayout.addSpacing(50);
    mainVLayout.addWidget(&returnMenu,0,Qt::AlignCenter);
    mainVLayout.setAlignment(Qt::AlignCenter);

    this->setLayout(&mainVLayout);

    //-----------------------------
    connect(&returnMenu, &QPushButton::clicked, qobject_cast<MainWindow*>(this->parent()), &MainWindow::showMenu);
    connect(&this->difficulties, SIGNAL(idClicked(int)), this, SLOT(setDiff(int)));
    connect(&this->buttons, SIGNAL(idClicked(int)), this, SLOT(setButtons(int)));
}

OptionsWidget::~OptionsWidget()
{
    Buttons.clean();
}

MovesContainer OptionsWidget::getButtons()
{
    return Buttons;
}

int OptionsWidget::getDifficulty()
{
    return speed;
}

void OptionsWidget::setButtons(int sel)
{
    switch (sel) {
    case 1:
        up->setDefaultColors();
        down->setDefaultColors();
        right->setDefaultColors();
        left->setDefaultColors();
        break;
    case 2:
        up->setActiveColor("#FFA1F5");
        down->setActiveColor("#BC7AF9");
        right->setActiveColor("#F8FF95");
        left->setActiveColor("#A6FF96");
        up->setColor("#800073");
        down->setColor("#4f0792");
        right->setColor("#778000");
        left->setColor("#138000");
        break;
    case 3:
        up->setActiveColor("#ffffff");
        down->setActiveColor("#ffffff");
        right->setActiveColor("#ffffff");
        left->setActiveColor("#ffffff");
        up->setColor("#666666");
        down->setColor("#666666");
        right->setColor("#666666");
        left->setColor("#666666");
        break;
    default:
        break;
    }
}

void OptionsWidget::setDiff(int sel)
{
    switch (sel) {
    case 1:
        speed = 1200;
        break;
    case 2:
        speed = 700;
        break;
    case 3:
        speed = 400;
        break;
    default:
        break;
    }
}

