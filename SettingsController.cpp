#include "SettingsController.h"
#include <iostream>
#include "SettingsModel.h"
#include <QMessageBox>

SettingsController::SettingsController(View *pView):
    Controller(nullptr, pView)
{

}


void SettingsController::updateView()
{
    this->view->render();
}

void SettingsController::setClubName(const QString &name)
{
    if(name.length() > 2)
    {
        try
        {
            SettingsModel::saveSetting("clubname", name);
        }
        catch(std::runtime_error &error)
        {
            QMessageBox box(QMessageBox::Warning, "Databasfel", QString::fromStdString(error.what()));
            box.exec();
        }
    }
}

