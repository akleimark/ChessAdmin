#include "SettingsView.h"
#include <QLabel>
#include "SettingsController.h"
#include "SettingsModel.h"

SettingsView::SettingsView(QWidget *parent, const QString &vName):
    View(nullptr, parent, vName)
{
    QLabel *label = new QLabel("Inställningar");
    QFont font("Georgia", 16, QFont::Bold);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setFont(font);

    addCenter();
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

    leftLayout->addWidget(new QLabel("Klubbnamn: "));
    clubNameEdit = new QLineEdit;
    clubNameEdit->setMaximumWidth(200);
    rightLayout->addWidget(clubNameEdit);

    layout->addWidget(centerPanel);
    layout->addStretch(1);
}


void SettingsView::render()
{
    clubNameEdit->setText(SettingsModel::getSetting("clubname"));
}

void SettingsView::addListeners()
{
    SettingsController *sController = static_cast<SettingsController*>(controller);
    connect(clubNameEdit, &QLineEdit::textEdited, sController, &SettingsController::setClubName);

}
