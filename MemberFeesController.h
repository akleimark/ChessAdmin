#ifndef MEMBERFEESCONTROLLER_H
#define MEMBERFEESCONTROLLER_H


#include "MVC.h"
class MemberFeesController : public Controller
{
    Q_OBJECT
    public:
        MemberFeesController(Model *pModel, View *pView);
        virtual void init();
        virtual void updateView();

    private:
        int currentSelectedRow;

    public slots:
        void rowChanged(const int &row, const int &);
        void deselected();
        void toggle();
        void exportToPdf();

};
#endif // MEMBERFEESCONTROLLER_H
