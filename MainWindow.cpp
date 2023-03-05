#include "MainWindow.h"
#include <QMenuBar>
#include <iostream>
#include "Database.h"
#include <QDebug>

const unsigned int MainWindow::DEFAULT_WIDTH = 500;
const unsigned int MainWindow::DEFAULT_HEIGHT = 500;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Database *database = Database::getInstance();
    try
    {
        database->connect();
    }
    catch(const std::runtime_error &error)
    {
        qDebug() << error.what();
        exit(-1);
    }

    database->createTables();

    stackedWidget = new QStackedWidget;

    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(stackedWidget);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    addActions();
    addMenuSystem();
    addModels();
    addViews();
    addControllers();
    initMVC();

    this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addModels()
{
    memberListModel = new ListModel<MemberModel>;
}

void MainWindow::addViews()
{
    // Vyerna skapas.
    memberListView = new MemberListView(memberListModel, this, "MEMBERLIST_VIEW");
    memberFeesView = new MemberFeesView(memberListModel, this, "MEMBERFEES_VIEW");
    settingsView = new SettingsView(this, "SETTINGS_VIEW");

    // Nu läggs vyerna in i 'stackedWidget'.
    stackedWidget->addWidget(memberListView);
    stackedWidget->addWidget(memberFeesView);
    stackedWidget->addWidget(settingsView);

}
void MainWindow::addControllers()
{
    memberListController = new MemberListController(memberListModel, memberListView);
    memberFeesController = new MemberFeesController(memberListModel, memberFeesView);
    settingsController = new SettingsController(settingsView);
}

void MainWindow::initMVC()
{
     memberListView->addListeners();
     memberFeesView->addListeners();
     settingsView->addListeners();
}

void MainWindow::addActions()
{
    quitAction = new QAction(tr("&Avsluta"), this);
    connect(quitAction, &QAction::triggered, this, &exit);

    memberListAction = new QAction(tr("&Medlemslista"), this);
    connect(memberListAction, &QAction::triggered, this, &MainWindow::memberList);

    memberFeesAction = new QAction(tr("&Medlemsavgifter"), this);
    connect(memberFeesAction, &QAction::triggered, this, &MainWindow::memberFees);

    settingsAction = new QAction(tr("&Inställningar"), this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::settings);

}
void MainWindow::addMenuSystem()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Arkiv"));
    fileMenu->addAction(quitAction);

    QMenu *memberMenu = menuBar()->addMenu(tr("&Medlemskap"));
    memberMenu->addAction(memberListAction);
    memberMenu->addAction(memberFeesAction);

    QMenu *settingsMenu = menuBar()->addMenu(tr("&Inställningar"));
    settingsMenu->addAction(settingsAction);
}

void MainWindow::showView(View *view) const
{
    stackedWidget->setCurrentWidget(view);
}

void MainWindow::memberList()
{
    memberListController->init();
    showView(memberListView);
    memberListController->getView()->render();
}

void MainWindow::memberFees()
{
    memberFeesController->init();
    showView(memberFeesView);
    memberFeesController->getView()->render();
}

void MainWindow::settings()
{
    settingsController->init();
    showView(settingsView);
    settingsController->getView()->render();
}
