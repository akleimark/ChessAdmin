#ifndef MEMBERLISTCONTROLLER_H
#define MEMBERLISTCONTROLLER_H


#include "MVC.h"
class MemberListController : public Controller
{
    Q_OBJECT
    public:
        MemberListController(Model *pModel, View *pView);
        virtual void init();
        virtual void updateView();

    private:
        int currentSelectedRow;

    public slots:
        void addMember();
        void editMember();
        void deleteMember();
        void rowChanged(const int &row, const int &);
        void deselected();
};

#endif // MEMBERLISTCONTROLLER_H
