#ifndef MEMBERFEESVIEW_H
#define MEMBERFEESVIEW_H

#include "Table.h"
#include <QLabel>
#include "MVC.h"
#include <QPushButton>

class MemberFeesView : public View
{
    private:
        Table *table;
        QLabel *label;
        QWidget *buttonWidget;
        QPushButton *toggleButton;
        QPushButton *exportButton;

    public:
        MemberFeesView(Model *p_model, QWidget *parent, const QString &vName);
        virtual ~MemberFeesView();
        virtual void render();
        virtual void addListeners();
        void addSouth();
        bool isDeselected() const { return table->selectedItems().size() == 0; }
        void activateButtons(bool status) { toggleButton->setEnabled(status); }
        Table* getTableWidget() const { return table; }

};

#endif // MEMBERFEESVIEW_H
