#ifndef MEMBERFEESVIEW_H
#define MEMBERFEESVIEW_H

#include "TableView.h"

class MemberFeesView : public TableView
{
    private:


    public:
        MemberFeesView(Model *p_model, QWidget *parent, const QString &vName);
        virtual ~MemberFeesView();
        virtual void render();
        virtual void addListeners();
        virtual void addCenter();
        virtual void addSouth();
        void activateButtons(bool status) { buttonMap["TOGGLE_BUTTON"]->setEnabled(status); }
        Table* getTableWidget() const { return table; }

};

#endif // MEMBERFEESVIEW_H
