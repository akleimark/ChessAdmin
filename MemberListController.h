#ifndef MEMBERLISTCONTROLLER_H
#define MEMBERLISTCONTROLLER_H

#include <QSet>
#include "TableController.h"


class MemberListController : public TableController
{
    Q_OBJECT
    public:
        MemberListController(Model *pModel, View *pView);
        virtual ~MemberListController() {}
        virtual void init();
        virtual void updateView();

    private:

    public slots:
        void addMember();
        void editMember();
        void deleteMember();        
        virtual void changeSelection();
};

#endif // MEMBERLISTCONTROLLER_H
