#include "MVC.h"


View::View(Model *p_model, QWidget *parent, const QString &vName):
    QWidget(parent), model(p_model), viewName(vName)
{
    layout = new QVBoxLayout;
    setLayout(layout);


}
