#include "MemberListView.h"
#include "MemberListController.h"
#include "Table.h"
#include <QScrollArea>
#include <QPushButton>
#include <iostream>
#include "ListModel.h"
#include "MemberModel.h"
#include <iostream>

MemberListView::MemberListView(Model *p_model, QWidget *parent, const QString &vName):
    View(p_model, parent, vName)
{
    label = new QLabel("Medlemslista");
    QFont font("Georgia", 16, QFont::Bold);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setFont(font);

    QStringList headers;
    headers << "Name" << "Date" << "Undso";

    table = new Table(QStringList({"Förnamn", "Efteramn", "Födelsedag", "Biologiskt kön", "Gatuadress", "Postnummer", "Postadress", "Telefonnummer", "E-postadress"}));
    layout->addWidget(table);

    addSouth();

}

void MemberListView::render()
{
    std::cout << "Rendering" << std::endl;
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    std::set<MemberModel>::const_iterator citerator;

    unsigned int row = 0;
    for(citerator = listModel->cbegin(); citerator != listModel->cend(); ++citerator)
    {
        table->setRowCount(row + 1);
        unsigned int column = 0;
        const MemberModel memberModel = *citerator;

        QTableWidgetItem *firstnameItem = new QTableWidgetItem(memberModel.getFirstname());
        QTableWidgetItem *lastnameItem = new QTableWidgetItem(memberModel.getLastname());
        QTableWidgetItem *birthdateItem = new QTableWidgetItem(memberModel.getBirthdate());
        QTableWidgetItem *biologicalSexItem = new QTableWidgetItem(memberModel.getBiologicalSex());
        QTableWidgetItem *streetAddressItem = new QTableWidgetItem(memberModel.getStreetAddress());
        QTableWidgetItem *zipCodeItem = new QTableWidgetItem(QString::number(memberModel.getZipCode()));
        QTableWidgetItem *cityItem = new QTableWidgetItem(memberModel.getCity());
        QTableWidgetItem *phoneNumberItem = new QTableWidgetItem(memberModel.getPhoneNumber());
        QTableWidgetItem *emailItem = new QTableWidgetItem(memberModel.getEmailAddress());

        table->setItem(row, column++, firstnameItem);
        table->setItem(row, column++, lastnameItem);
        table->setItem(row, column++, birthdateItem);
        table->setItem(row, column++, biologicalSexItem);
        table->setItem(row, column++, streetAddressItem);
        table->setItem(row, column++, zipCodeItem);
        table->setItem(row, column++, cityItem);
        table->setItem(row, column++, phoneNumberItem);
        table->setItem(row, column++, emailItem);

        ++row;
    }
}

void MemberListView::addListeners()
{
    MemberListController *mController = dynamic_cast<MemberListController*>(controller);
    connect(addMemberButton, &QPushButton::clicked, mController, &MemberListController::addMember);
    connect(editMemberButton, &QPushButton::clicked, mController, &MemberListController::editMember);
    connect(removeMemberButton, &QPushButton::clicked, mController, &MemberListController::deleteMember);
    connect(table, &QTableWidget::cellClicked, mController, &MemberListController::rowChanged);
    connect(table, &QTableWidget::itemSelectionChanged, mController, &MemberListController::deselected);
}

void MemberListView::addSouth()
{
    buttonWidget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    buttonWidget->setLayout(gridLayout);
    addMemberButton = new QPushButton("Lägg till");
    editMemberButton = new QPushButton("Redigera");
    removeMemberButton = new QPushButton("Ta bort");
    editMemberButton->setEnabled(false);
    removeMemberButton->setEnabled(false);

    gridLayout->addWidget(addMemberButton, 0, 0);
    gridLayout->addWidget(editMemberButton, 0, 1);
    gridLayout->addWidget(removeMemberButton, 0, 2);

    layout->addWidget(buttonWidget);


}
