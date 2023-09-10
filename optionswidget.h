#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H


#include <QWidget>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QObject>
#include <QFontDatabase>
#include <QCheckBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QApplication>
#include "Objects/movescontainer.h"
#include "Objects/upbutton.h"
#include "Objects/downbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/leftbutton.h"

class OptionsWidget : public QWidget
{
    Q_OBJECT
private:
    // For the colors
    UpButton * up;
    DownButton * down;
    RightButton * right;
    LeftButton * left;
    MovesContainer Buttons;
    // Difficulty
    int speed;

    //Labels
    QLabel buttonsLabel, difficultyLabel;

    //Color Selector
    QColorDialog col;

    //CheckBox
    QCheckBox button1Box, button2Box, button3Box,
              difficulty1Box, difficulty2Box, difficulty3Box;

    //Buttons and groups
    QPushButton returnMenu;
    QButtonGroup buttons, difficulties;

    //Layouts
    QVBoxLayout mainVLayout, firstVLayout, secondVLayout;
    QHBoxLayout mainHLayout;
public:
    explicit OptionsWidget(QWidget *parent = nullptr);
    ~OptionsWidget();

    MovesContainer getButtons();
    int getDifficulty();
private slots:
    void setButtons(int sel);
    void setDiff(int sel);
};

#endif // OPTIONSWIDGET_H
