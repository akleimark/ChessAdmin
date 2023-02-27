#ifndef MEMBERLISTVIEW_H
#define MEMBERLISTVIEW_H

#include <QLabel>
#include "MVC.h"
#include <QPushButton>
#include "Table.h"
#include <iostream>

class MemberListView : public View
{
    private:
        Table *table;
        QLabel *label;
        QWidget *buttonWidget;
        QPushButton *addMemberButton;
        QPushButton *editMemberButton;
        QPushButton *removeMemberButton;

    public:
        MemberListView(Model *p_model, QWidget *parent, const QString &vName);
        virtual void render();
        virtual void addListeners();
        void addSouth();
        bool isDeselected() const { return table->selectedItems().size() == 0; }
        void activateButtons(bool status) { editMemberButton->setEnabled(status); removeMemberButton->setEnabled(status); }
};

#endif // MEMBERLISTVIEW_H
