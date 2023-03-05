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
#include "MemberFeesView.h"
#include "MemberFeesController.h"
#include "SettingsView.h"
#include "SettingsController.h"

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
        QAction *memberFeesAction;
        QAction *settingsAction;

        // Models
        ListModel<MemberModel> *memberListModel;

        // Views
        MemberListView *memberListView;
        MemberFeesView *memberFeesView;
        SettingsView *settingsView;

        // Controllers
        MemberListController *memberListController;
        MemberFeesController *memberFeesController;
        SettingsController *settingsController;

    private slots:
        void memberList();
        void memberFees();
        void settings();

};
#endif // MAINWINDOW_H
