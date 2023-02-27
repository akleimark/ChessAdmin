#include "MemberListController.h"
#include <iostream>
#include "Dialog.h"
#include "MemberModel.h"
#include "ListModel.h"
#include "MemberListView.h"
#include <QMessageBox>

MemberListController::MemberListController(Model *pModel, View *pView):
    Controller(pModel, pView), currentSelectedRow(-1)
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
    MemberModel mModel = listModel->atIndex(currentSelectedRow);

    AddEditMemberDialog *dialog = new AddEditMemberDialog(mModel);
    dialog->exec();
}

void MemberListController::deleteMember()
{
    std::cout << "delete" << std::endl;    

    QMessageBox box(QMessageBox::Warning, "Radering av en medlem", "Vill du ta bort medlemmen ur databasen?", QMessageBox::Yes|QMessageBox::No);
    int ret = box.exec();
    if(ret == QMessageBox::Yes)
    {
        ListModel<MemberModel> *listModel = static_cast<ListModel<MemberModel> *>(model);
        MemberModel mModel = listModel->atIndex(currentSelectedRow);
        try
        {
            mModel.remove();
            updateView();
        }
        catch(std::runtime_error &error)
        {
            QMessageBox box(QMessageBox::Warning, "Databasfel", QString::fromStdString(error.what()));
            box.exec();
        }
    }
}

void MemberListController::rowChanged(const int &row, const int &)
{
    currentSelectedRow = row;
}

void MemberListController::deselected()
{
    MemberListView *mView = static_cast<MemberListView*>(view);
    if(mView->isDeselected())
    {
        currentSelectedRow = -1;
        mView->activateButtons(false);
    }
    else
    {
        mView->activateButtons(true);
    }
}


