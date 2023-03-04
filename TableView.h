#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "MVC.h"
#include "Table.h"
#include <QLabel>
#include <QPushButton>

class TableView : public View
{
    public:
    virtual ~TableView() {}
    virtual void render() = 0;
    virtual void addListeners() = 0;
    virtual void addCenter() = 0;
    virtual void addSouth() = 0;
    Table* getTable() const { return table; }
    void activateButton(const QString &buttonName, const bool &status = true);

    protected:
        TableView(Model *p_model, QWidget *parent, const QString &vName, const QString &labelText);
        Table *table;
        QLabel *label;
        QWidget *buttonWidget;
        QMap<QString, QPushButton*> buttonMap;

};

#endif // TABLEVIEW_H
