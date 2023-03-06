#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "MVC.h"

class SettingsController : public Controller
{
    Q_OBJECT
    public:
        SettingsController(View *pView);
        virtual ~SettingsController() {}
        virtual void init() {}
        virtual void updateView();

    private:

    public slots:        
        void setClubName(const QString &name);

};

#endif // SETTINGSCONTROLLER_H
