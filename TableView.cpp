#include "TableView.h"

TableView::TableView(Model *p_model, QWidget *parent, const QString &vName, const QString &labelText):
    View(p_model, parent, vName)
{
    label = new QLabel(labelText);
    QFont font("Georgia", 16, QFont::Bold);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setFont(font);    
}


void TableView::activateButton(const QString &buttonName, const bool &status)
{
    QPushButton *button = nullptr;
    button = buttonMap[buttonName];

    if(button == nullptr)
    {
        throw std::invalid_argument("Felaktigt namn på knapp");
    }

    button->setEnabled(status);
}

