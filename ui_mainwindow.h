#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionSearch;
    QAction *actionGet_Stream;
    QWidget *centralwidget;
    QLineEdit *searchTerm;
    QLabel *label;
    QTextEdit *rawText;
    QTextEdit *outputText;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName("actionSearch");
        actionGet_Stream = new QAction(MainWindow);
        actionGet_Stream->setObjectName("actionGet_Stream");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        searchTerm = new QLineEdit(centralwidget);
        searchTerm->setObjectName("searchTerm");
        searchTerm->setGeometry(QRect(100, 10, 141, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 21));
        rawText = new QTextEdit(centralwidget);
        rawText->setObjectName("rawText");
        rawText->setGeometry(QRect(10, 50, 771, 231));
        outputText = new QTextEdit(centralwidget);
        outputText->setObjectName("outputText");
        outputText->setGeometry(QRect(10, 300, 771, 241));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);
        menuFile->addAction(actionSearch);
        menuFile->addAction(actionGet_Stream);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        actionGet_Stream->setText(QCoreApplication::translate("MainWindow", "Get Stream", nullptr));
        searchTerm->setText(QCoreApplication::translate("MainWindow", "classic", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Search Term:", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif  //UI_MAINWINDOW_H
