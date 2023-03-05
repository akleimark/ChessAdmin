#include "SettingsView.h"
#include <QLabel>

SettingsView::SettingsView(QWidget *parent, const QString &vName):
    View(nullptr, parent, vName)
{
    QLabel *label = new QLabel("Inställningar");
    QFont font("Georgia", 16, QFont::Bold);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setFont(font);

    addCenter();
    addSouth();

}

SettingsView:: ~SettingsView()
{

}

void SettingsView::addCenter()
{
    centerPanel = new QWidget;
    leftPanel = new QWidget;
    rightPanel = new QWidget;
    centerLayout = new QHBoxLayout(centerPanel);
    leftLayout = new QVBoxLayout(leftPanel);
    rightLayout = new QVBoxLayout(rightPanel);
    centerLayout->addWidget(leftPanel);
    centerLayout->addWidget(rightPanel);

    layout->addStretch(1);
}

void SettingsView::addSouth()
{
    QWidget *buttonWidget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    buttonWidget->setLayout(gridLayout);
    saveButton = new QPushButton("Redigera");
    resetButton = new QPushButton("Återställ");

    gridLayout->addWidget(saveButton, 0, 0);
    gridLayout->addWidget(resetButton, 0, 1);

    layout->addWidget(buttonWidget);
}



void SettingsView::render()
{

}

void SettingsView::addListeners()
{

}
