/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Dec 10 17:49:29 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QWidget *centralwidget;
    QDockWidget *widgetVisualEffect;
    QWidget *contentVisualEffect;
    QScrollArea *viewer;
    QWidget *viewerImageWidget;
    QLabel *labelFrameSeconde;
    QSlider *sliderFrameSeconde;
    QDockWidget *widgetImport;
    QWidget *contentImport;
    QTabWidget *tabWidget;
    QWidget *photos;
    QWidget *importPhoto;
    QWidget *importSons;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ImportButton;
    QPushButton *newFileButton;
    QPushButton *deleteButton;
    QDockWidget *widgetFlux;
    QWidget *contentFlux;
    QDockWidget *widgetEffect;
    QWidget *contentEffect;
    QDockWidget *widgetTimeline;
    QWidget *contentTimeline;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuControl;
    QMenu *menuTimeline;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(882, 640);
        MainWindow->setIconSize(QSize(25, 25));
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("nouveau.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("ouvrir.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widgetVisualEffect = new QDockWidget(centralwidget);
        widgetVisualEffect->setObjectName(QString::fromUtf8("widgetVisualEffect"));
        widgetVisualEffect->setGeometry(QRect(230, 0, 291, 300));
        widgetVisualEffect->setAcceptDrops(false);
        widgetVisualEffect->setAllowedAreas(Qt::NoDockWidgetArea);
        contentVisualEffect = new QWidget();
        contentVisualEffect->setObjectName(QString::fromUtf8("contentVisualEffect"));
        contentVisualEffect->setEnabled(true);
        contentVisualEffect->setMouseTracking(false);
        contentVisualEffect->setAcceptDrops(false);
        viewer = new QScrollArea(contentVisualEffect);
        viewer->setObjectName(QString::fromUtf8("viewer"));
        viewer->setGeometry(QRect(20, 10, 261, 201));
        viewer->setWidgetResizable(true);
        viewerImageWidget = new QWidget();
        viewerImageWidget->setObjectName(QString::fromUtf8("viewerImageWidget"));
        viewerImageWidget->setGeometry(QRect(0, 0, 259, 199));
        viewer->setWidget(viewerImageWidget);
        labelFrameSeconde = new QLabel(contentVisualEffect);
        labelFrameSeconde->setObjectName(QString::fromUtf8("labelFrameSeconde"));
        labelFrameSeconde->setGeometry(QRect(20, 220, 201, 17));
        sliderFrameSeconde = new QSlider(contentVisualEffect);
        sliderFrameSeconde->setObjectName(QString::fromUtf8("sliderFrameSeconde"));
        sliderFrameSeconde->setGeometry(QRect(30, 240, 141, 20));
        sliderFrameSeconde->setOrientation(Qt::Horizontal);
        widgetVisualEffect->setWidget(contentVisualEffect);
        widgetImport = new QDockWidget(centralwidget);
        widgetImport->setObjectName(QString::fromUtf8("widgetImport"));
        widgetImport->setGeometry(QRect(0, -3, 231, 621));
        widgetImport->setMinimumSize(QSize(79, 300));
        widgetImport->setAcceptDrops(false);
        widgetImport->setFloating(false);
        widgetImport->setAllowedAreas(Qt::NoDockWidgetArea);
        contentImport = new QWidget();
        contentImport->setObjectName(QString::fromUtf8("contentImport"));
        tabWidget = new QTabWidget(contentImport);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 231, 251));
        photos = new QWidget();
        photos->setObjectName(QString::fromUtf8("photos"));
        tabWidget->addTab(photos, QString());
        importPhoto = new QWidget();
        importPhoto->setObjectName(QString::fromUtf8("importPhoto"));
        tabWidget->addTab(importPhoto, QString());
        importSons = new QWidget();
        importSons->setObjectName(QString::fromUtf8("importSons"));
        tabWidget->addTab(importSons, QString());
        layoutWidget = new QWidget(contentImport);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 248, 231, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ImportButton = new QPushButton(layoutWidget);
        ImportButton->setObjectName(QString::fromUtf8("ImportButton"));
        ImportButton->setIconSize(QSize(13, 13));

        horizontalLayout->addWidget(ImportButton);

        newFileButton = new QPushButton(layoutWidget);
        newFileButton->setObjectName(QString::fromUtf8("newFileButton"));

        horizontalLayout->addWidget(newFileButton);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        horizontalLayout->addWidget(deleteButton);

        widgetImport->setWidget(contentImport);
        widgetFlux = new QDockWidget(centralwidget);
        widgetFlux->setObjectName(QString::fromUtf8("widgetFlux"));
        widgetFlux->setGeometry(QRect(520, 0, 361, 300));
        widgetFlux->setAcceptDrops(false);
        widgetFlux->setAllowedAreas(Qt::NoDockWidgetArea);
        contentFlux = new QWidget();
        contentFlux->setObjectName(QString::fromUtf8("contentFlux"));
        widgetFlux->setWidget(contentFlux);
        widgetEffect = new QDockWidget(centralwidget);
        widgetEffect->setObjectName(QString::fromUtf8("widgetEffect"));
        widgetEffect->setGeometry(QRect(0, 300, 161, 241));
        contentEffect = new QWidget();
        contentEffect->setObjectName(QString::fromUtf8("contentEffect"));
        widgetEffect->setWidget(contentEffect);
        widgetTimeline = new QDockWidget(centralwidget);
        widgetTimeline->setObjectName(QString::fromUtf8("widgetTimeline"));
        widgetTimeline->setGeometry(QRect(160, 300, 721, 231));
        contentTimeline = new QWidget();
        contentTimeline->setObjectName(QString::fromUtf8("contentTimeline"));
        widgetTimeline->setWidget(contentTimeline);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 882, 25));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuControl = new QMenu(menubar);
        menuControl->setObjectName(QString::fromUtf8("menuControl"));
        menuTimeline = new QMenu(menubar);
        menuTimeline->setObjectName(QString::fromUtf8("menuTimeline"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuControl->menuAction());
        menubar->addAction(menuTimeline->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        labelFrameSeconde->setText(QApplication::translate("MainWindow", "Nombre de frame / seconde : ", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(photos), QApplication::translate("MainWindow", "Photos", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(importPhoto), QApplication::translate("MainWindow", "Images importees", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(importSons), QApplication::translate("MainWindow", "Sons", 0, QApplication::UnicodeUTF8));
        ImportButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        newFileButton->setText(QApplication::translate("MainWindow", "New File", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuControl->setTitle(QApplication::translate("MainWindow", "Control", 0, QApplication::UnicodeUTF8));
        menuTimeline->setTitle(QApplication::translate("MainWindow", "Timeline", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
