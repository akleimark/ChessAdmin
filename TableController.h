#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "MVC.h"
#include <QSet>

class TableController : public Controller
{
    Q_OBJECT
    protected:
        TableController(Model *pModel, View *pView);
        virtual ~TableController() {}
        QSet<unsigned int>selectedRows;

    public:
        virtual void init() = 0;
        virtual void updateView() = 0;


    public slots:

        virtual void changeSelection() = 0;
};


#endif // TABLECONTROLLER_H
