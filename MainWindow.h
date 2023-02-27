#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MemberListController.h"
#include "MemberListView.h"
#include "MemberModel.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QAction>
#include "ListModel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        const static unsigned int DEFAULT_WIDTH;
        const static unsigned int DEFAULT_HEIGHT;
        QStackedWidget *stackedWidget;
        QWidget *mainWidget;
        QVBoxLayout *mainLayout;

        void addModels();
        void addViews();
        void addControllers();
        void initMVC();
        void addActions();
        void addMenuSystem();
        void showView(View *view) const;

        // QActions
        QAction *quitAction;
        QAction *memberListAction;

        // Models
        ListModel<MemberModel> *memberListModel;

        // Views
        MemberListView *memberListView;

        // Controllers
        MemberListController *memberListController;

    private slots:
        void memberList();

};
#endif // MAINWINDOW_H
