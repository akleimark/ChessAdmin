#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include "MVC.h"
#include <QPushButton>
#include <QLineEdit>

class SettingsView : public View
{
    private:
        void addCenter();           

        QWidget *mainWidget;
        QWidget * centerPanel;
        QWidget *leftPanel;
        QWidget *rightPanel;
        QHBoxLayout *centerLayout;
        QVBoxLayout *leftLayout;
        QVBoxLayout *rightLayout;

        QLineEdit *clubNameEdit;

    public:
        SettingsView(QWidget *parent, const QString &vName);
        virtual ~SettingsView();
        virtual void render();
        virtual void addListeners();

};
#endif // SETTINGSVIEW_H
