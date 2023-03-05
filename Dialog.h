#ifndef DIALOG_H
#define DIALOG_H

#include "MVC.h"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include "MemberModel.h"

class FormDialog : public QDialog
{
    Q_OBJECT

    public:
        FormDialog();
        virtual ~FormDialog() {}
        virtual void addCenter();
        virtual void addSouth();

    protected:        
        QWidget *mainWidget;
        QVBoxLayout *dialogLayout;
        QWidget * centerPanel;
        QWidget *leftPanel;
        QWidget *rightPanel;
        QHBoxLayout *centerLayout;
        QVBoxLayout *leftLayout;
        QVBoxLayout *rightLayout;
        QWidget *southPanel;
        QGridLayout *gridLayout;

    private:
        const static unsigned int DEFAULT_WIDTH;
        const static unsigned int DEFAULT_HEIGHT;
};

class AddEditMemberDialog : public FormDialog
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
