#include "MemberFeesView.h"
#include <iostream>
#include "ListModel.h"
#include "MemberModel.h"
#include "MemberFeesController.h"

MemberFeesView::MemberFeesView(Model *p_model, QWidget *parent, const QString &vName):
    TableView(p_model, parent, vName, "Medlemsavgifter")
{
    addCenter();
    addSouth();
}

MemberFeesView:: ~MemberFeesView()
{

}

void MemberFeesView::addCenter()
{
    table = new Table(QStringList({"Förnamn", "Efteramn", "Födelsedag", "Betalad medlemsavgift"}));
    layout->addWidget(table);
}

void MemberFeesView::render()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    std::set<MemberModel>::const_iterator citerator;

    table->setRowCount(0);
    unsigned int row = 0;
    for(citerator = listModel->cbegin(); citerator != listModel->cend(); ++citerator)
    {
        table->setRowCount(row + 1);
        unsigned int column = 0;
        const MemberModel memberModel = *citerator;

        QTableWidgetItem *firstnameItem = new QTableWidgetItem(memberModel.getFirstname());
        QTableWidgetItem *lastnameItem = new QTableWidgetItem(memberModel.getLastname());
        QTableWidgetItem *birthdateItem = new QTableWidgetItem(memberModel.getBirthdate());
        QTableWidgetItem *memberFeeStatusItem = new QTableWidgetItem("");

        if(memberModel.isMemberFeePayed())
        {
            memberFeeStatusItem->setBackground(Qt::green);
        }
        else
        {
            memberFeeStatusItem->setBackground(Qt::red);
        }

        table->setItem(row, column++, firstnameItem);
        table->setItem(row, column++, lastnameItem);
        table->setItem(row, column++, birthdateItem);
        table->setItem(row, column++, memberFeeStatusItem);

        ++row;
    }
}

void MemberFeesView::addListeners()
{
    MemberFeesController *mController = dynamic_cast<MemberFeesController*>(controller);
    connect(buttonMap["TOGGLE_BUTTON"], &QPushButton::clicked, mController, &MemberFeesController::toggle);
    connect(buttonMap["EXPORT_BUTTON"], &QPushButton::clicked, mController, &MemberFeesController::exportToPdf);
    connect(table, &QTableWidget::itemSelectionChanged, mController, &MemberFeesController::changeSelection);
}

void MemberFeesView::addSouth()
{
    buttonWidget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    buttonWidget->setLayout(gridLayout);

    QPushButton *toggleButton = new QPushButton("Ändra");
    toggleButton->setEnabled(false);
    QPushButton *exportButton = new QPushButton("Exportera");

    gridLayout->addWidget(toggleButton, 0, 0);
    gridLayout->addWidget(exportButton, 0, 1);


    buttonMap["TOGGLE_BUTTON"] = toggleButton;
    buttonMap["EXPORT_BUTTON"] = exportButton;
    layout->addWidget(buttonWidget);
}
