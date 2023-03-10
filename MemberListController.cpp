#include "MemberListController.h"
#include <iostream>
#include "Dialog.h"
#include "MemberModel.h"
#include "ListModel.h"
#include "MemberListView.h"
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include "SettingsModel.h"

MemberListController::MemberListController(Model *pModel, View *pView):
    TableController(pModel, pView)
{

}

void MemberListController::init()
{
    try
    {
        ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
        listModel->getAll();

    }
    catch(std::runtime_error &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void MemberListController::updateView()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    listModel->getAll();
    view->render();
}

void MemberListController::addMember()
{
    std::cout << "add member" << std::endl;
    MemberModel model;
    AddEditMemberDialog *dialog = new AddEditMemberDialog(model);
    dialog->exec();
    updateView();
}
void MemberListController::editMember()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    unsigned int row = *selectedRows.begin();
    MemberModel mModel = listModel->atIndex(row);

    AddEditMemberDialog *dialog = new AddEditMemberDialog(mModel);
    dialog->exec();
    updateView();
}

void MemberListController::deleteMember()
{
    ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    std::cout << "delete" << std::endl;

    for(const unsigned int &index : selectedRows)
    {
        MemberModel mModel = listModel->atIndex(index);
        QMessageBox box(QMessageBox::Warning, "Radering av en medlem", "Vill du ta bort '" + mModel.getFullName() +"' ur databasen?", QMessageBox::Yes|QMessageBox::No);
        int ret = box.exec();
        if(ret == QMessageBox::Yes)
        {
            try
            {
                mModel.remove();
            }
            catch(std::runtime_error &error)
            {
                QMessageBox box(QMessageBox::Warning, "Databasfel", QString::fromStdString(error.what()));
                box.exec();
            }
        }
    }
    updateView();
}

void MemberListController::changeSelection()
{
    selectedRows.clear();
    MemberListView *mView = static_cast<MemberListView*>(view);

    QList<QTableWidgetItem*> list = mView->getTable()->selectedItems();
    for(QTableWidgetItem *item : list)
    {
        selectedRows.insert((item->row()));
    }

    if(selectedRows.size() == 0)
    {      
        mView->activateButton("EDIT_MEMBER_BUTTON", false);
        mView->activateButton("REMOVE_MEMBER_BUTTON", false);
    }
    else if(selectedRows.size() == 1)
    {
        mView->activateButton("EDIT_MEMBER_BUTTON");
        mView->activateButton("REMOVE_MEMBER_BUTTON");
    }

    else
    {
        mView->activateButton("EDIT_MEMBER_BUTTON", false);
        mView->activateButton("REMOVE_MEMBER_BUTTON");
    }
}

void MemberListController::createVSFPage()
{
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);


    //ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
    std::set<MemberModel>::const_iterator citerator;
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName("blankett.pdf");

    QTextDocument doc;
    QString html = "<html><head><link rel='stylesheet' type='text/css' href='styles.css' /></head><body><h1><center>Sammanst??llningsblankett"
            "</center></h1>"
            "<h2><center>Medlemsregistrering " + QString::number(aTime->tm_year + 1900) + "</center></h2>";

    html += "<div style='float:left;margin-top:30px;'><strong>Klubb: </strong>" + SettingsModel::getSetting("clubname");


    doc.setHtml(html);
    doc.print(&printer);
}
