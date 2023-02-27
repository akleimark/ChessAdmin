#ifndef DIALOG_H
#define DIALOG_H

#include "MVC.h"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include "MemberModel.h"


class Dialog : public QDialog
{
    Q_OBJECT

    public:
        Dialog();
        virtual ~Dialog() {}
        virtual void addCenter() = 0;
        virtual void addSouth() = 0;

    protected:        
        QWidget *mainWidget;
        QVBoxLayout *dialogLayout;

    private:
        const static unsigned int DEFAULT_WIDTH;
        const static unsigned int DEFAULT_HEIGHT;

};

class AddEditMemberDialog : public Dialog
{
    Q_OBJECT

    public:
        AddEditMemberDialog(MemberModel &p_model);
        virtual ~AddEditMemberDialog();
        virtual void addCenter();
        virtual void addSouth();
        void addSavedData();

    private:
        MemberModel memberModel;
        QPushButton *saveButton;
        QPushButton *closeButton;

        QLineEdit *nameEdit;
        QLineEdit *birthdayEdit;
        QLineEdit *streetEdit;
        QLineEdit *zipEdit;
        QLineEdit *cityEdit;
        QLineEdit *phoneEdit;
        QLineEdit *emailEdit;

        QRadioButton *maleButton;
        QRadioButton *femaleButton;

    private slots:
        void saveMember();

};


#endif // DIALOG_H
