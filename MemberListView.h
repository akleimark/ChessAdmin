#ifndef MEMBERLISTVIEW_H
#define MEMBERLISTVIEW_H

#include "TableView.h"
#include <iostream>

class MemberListView : public TableView
{
    private:

    public:
        MemberListView(Model *p_model, QWidget *parent, const QString &vName);
        virtual void render();
        virtual void addListeners();
        virtual void addSouth();
        virtual void addCenter();
};

#endif // MEMBERLISTVIEW_H
