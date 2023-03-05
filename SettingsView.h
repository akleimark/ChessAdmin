#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include "MVC.h"
#include <QPushButton>

class SettingsView : public View
{
    private:
        void addCenter();
        void addSouth();
        QPushButton *saveButton;
        QPushButton *resetButton;

        QWidget *mainWidget;
        QWidget * centerPanel;
        QWidget *leftPanel;
        QWidget *rightPanel;
        QHBoxLayout *centerLayout;
        QVBoxLayout *leftLayout;
        QVBoxLayout *rightLayout;

    public:
        SettingsView(QWidget *parent, const QString &vName);
        virtual ~SettingsView();
        virtual void render();
        virtual void addListeners();

};
#endif // SETTINGSVIEW_H
