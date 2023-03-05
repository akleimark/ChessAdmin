#include "Dialog.h"
#include <iostream>
#include <QLabel>
#include "MemberModel.h"
#include <QDebug>
#include <stdexcept>
#include <iostream>
#include <QMessageBox>

const unsigned int FormDialog::DEFAULT_WIDTH = 500;
const unsigned int FormDialog::DEFAULT_HEIGHT = 500;

FormDialog::FormDialog()
{
    mainWidget = new QWidget;
    dialogLayout = new QVBoxLayout(this);
    this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->setModal(true);
}

void FormDialog::addCenter()
{
    centerPanel = new QWidget;
    leftPanel = new QWidget;
    rightPanel = new QWidget;
    centerLayout = new QHBoxLayout(centerPanel);
    leftLayout = new QVBoxLayout(leftPanel);
    rightLayout = new QVBoxLayout(rightPanel);
    centerLayout->addWidget(leftPanel);
    centerLayout->addWidget(rightPanel);
}

void FormDialog::addSouth()
{
    southPanel = new QWidget;
    gridLayout = new QGridLayout(southPanel);
}

AddEditMemberDialog::AddEditMemberDialog(MemberModel &p_model):
    memberModel(p_model)
{    
    this->addCenter();
    this->addSouth();

    if(p_model.getId() == 0)
    {
        this->setWindowTitle("Lägg till en medlem");
    }
    else
    {
        this->setWindowTitle("Redigera en medlem");
        this->addSavedData();
    }    
}

AddEditMemberDialog:: ~AddEditMemberDialog()
{

}

void AddEditMemberDialog::addCenter()
{
    FormDialog::addCenter();

    //Namn    
    leftLayout->addWidget(new QLabel("Namn: "));
    nameEdit = new QLineEdit;
    nameEdit->setMinimumWidth(200);
    rightLayout->addWidget(nameEdit);

    // Födelsedag
    leftLayout->addWidget(new QLabel("Födelsedag: "));
    birthdayEdit = new QLineEdit;
    birthdayEdit->setMinimumWidth(100);
    birthdayEdit->setMaximumWidth(100);
    rightLayout->addWidget(birthdayEdit);

    // Biologiskt kön
    leftLayout->addWidget(new QLabel("Biologiskt kön: "));
    QWidget *buttongroup = new QWidget;
    maleButton = new QRadioButton("Man");
    femaleButton = new QRadioButton("Kvinna");
    buttongroup->setLayout(new QHBoxLayout);
    buttongroup->layout()->addWidget(maleButton);
    buttongroup->layout()->addWidget(femaleButton);
    rightLayout->addWidget(buttongroup);

    // Gatuadress
    leftLayout->addWidget(new QLabel("Gatuadress: "));
    streetEdit = new QLineEdit;
    streetEdit->setMinimumWidth(200);
    rightLayout->addWidget(streetEdit);

    // Postnummer
    leftLayout->addWidget(new QLabel("Postnummer: "));
    zipEdit = new QLineEdit;
    zipEdit->setMaximumWidth(75);
    rightLayout->addWidget(zipEdit);

    // Postadress
    leftLayout->addWidget(new QLabel("Postadress: "));
    cityEdit = new QLineEdit;
    cityEdit->setMaximumWidth(200);
    rightLayout->addWidget(cityEdit);

    // Telefonnummer
    leftLayout->addWidget(new QLabel("Telefonnummer: "));
    phoneEdit = new QLineEdit;
    phoneEdit->setMaximumWidth(125);
    rightLayout->addWidget(phoneEdit);

    // E-post
    leftLayout->addWidget(new QLabel("E-postadress: "));
    emailEdit = new QLineEdit;
    emailEdit->setMaximumWidth(200);
    rightLayout->addWidget(emailEdit);

    centerLayout->addStretch(1);
    dialogLayout->addWidget(centerPanel);
}

void AddEditMemberDialog::addSouth()
{
    FormDialog::addSouth();

    saveButton = new QPushButton("Spara");
    gridLayout->addWidget(saveButton, 0, 0);
    closeButton = new QPushButton("Stäng");
    gridLayout->addWidget(closeButton, 0, 1);
    gridLayout->setAlignment(Qt::AlignBottom);
    dialogLayout->addWidget(southPanel, Qt::AlignBottom);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    connect(saveButton, &QPushButton::clicked, this, &AddEditMemberDialog::saveMember);
}

void AddEditMemberDialog::saveMember()
{
    memberModel.setFullName(nameEdit->text());
    memberModel.setBirthdate(birthdayEdit->text());
    bool ok = false;
    const unsigned int ZIP = zipEdit->text().toUInt(&ok);
    if(ok)
    {
        memberModel.setZipCode(ZIP);
    }
    memberModel.setPhoneNumber(phoneEdit->text());
    memberModel.setEmailAddress(emailEdit->text());
    memberModel.setStreetAddress(streetEdit->text());
    memberModel.setCity(cityEdit->text());

    if(maleButton->isChecked())
    {
        memberModel.setBiologicalSex("Male");
    }
    else if(femaleButton->isChecked())
    {
        memberModel.setBiologicalSex("Female");
    }

    try
    {
        memberModel.validate();
        memberModel.save(memberModel.getId() == 0);
        this->close();
    }
    catch(const std::invalid_argument &error)
    {
       QMessageBox box(QMessageBox::Warning, "Fel indata", QString::fromStdString(error.what()));
       box.exec();
    }
    catch(std::runtime_error &error)
    {
        QMessageBox box(QMessageBox::Warning, "Databasfel", QString::fromStdString(error.what()));
        box.exec();
    }
}

void AddEditMemberDialog::addSavedData()
{

    nameEdit->setText(memberModel.getFullName());
    birthdayEdit->setText(memberModel.getBirthdate());
    maleButton->setChecked(memberModel.getBiologicalSex() == "Man");
    femaleButton->setChecked(memberModel.getBiologicalSex() == "Kvinna");
    streetEdit->setText(memberModel.getStreetAddress());
    if(memberModel.getZipCode() == 0)
    {
        zipEdit->setText("");
    }
    else
    {
        zipEdit->setText((QString::number(memberModel.getZipCode())));
    }
    cityEdit->setText(memberModel.getCity());
    phoneEdit->setText(memberModel.getPhoneNumber());
    emailEdit->setText(memberModel.getEmailAddress());
}
