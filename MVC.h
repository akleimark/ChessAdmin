#ifndef MVC_H
#define MVC_H

#include "qboxlayout.h"
#include "qwidget.h"
#include <set>
#include <string>

class Controller;
class View;
class Model
{
    public:
    QString getTableName() const { return TABLE_NAME; }

    protected:
        Model() {}
        virtual ~Model() {}
        QString TABLE_NAME;
};

class View : public QWidget
{
    public:

        View(Model *p_model, QWidget *parent, const QString &vName);
        virtual ~View() {}
        virtual void render() = 0;
        virtual void addListeners() = 0;
        bool operator<(const View &view) const {return viewName < view.viewName; }
        void setController(Controller *c) { controller = c; }

    protected:
        Model *model;
        const QString viewName;
        Controller *controller;
        QVBoxLayout *layout;
};

class Controller: public QObject
{
    Q_OBJECT

    protected:
        Model *model;
        View *view;
        Controller(Model *pModel, View *pView):
            model(pModel), view(pView) { view->setController(this); }

    public:
        Model* getModel() const { return model; }
        View* getView() const { return view; }
        virtual void init() = 0;
        virtual void updateView() = 0;
};

#endif // MVC_H
