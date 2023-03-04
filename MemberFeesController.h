#ifndef MEMBERFEESCONTROLLER_H
#define MEMBERFEESCONTROLLER_H

#include "TableController.h"
#include "MVC.h"

class MemberFeesController : public TableController
{
    Q_OBJECT
    public:
        MemberFeesController(Model *pModel, View *pView);
        virtual void init();
        virtual void updateView();

    private:        

    public slots:
        virtual void changeSelection();
        void toggle();
        void exportToPdf();

};
#endif // MEMBERFEESCONTROLLER_H
