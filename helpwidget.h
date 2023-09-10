#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFontDatabase>

class HelpWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel text;

    QPushButton returnMenu;

    QVBoxLayout mainLayout;
public:
    HelpWidget(QWidget *parent = nullptr);
};

#endif // HELPWIDGET_H
