/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <DownloadView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter_3;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTextEdit *textEdit_2;
    QLabel *label_3;
    QTextEdit *textEdit_3;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    DownloadView *downloadingView;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QTextEdit *logEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QTextEdit *errorLogEdit;
    QWidget *tab2;
    QGridLayout *gridLayout_2;
    DownloadView *downloadedView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(931, 526);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(9, -1, -1, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        textEdit_2 = new QTextEdit(groupBox);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        verticalLayout->addWidget(textEdit_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        textEdit_3 = new QTextEdit(groupBox);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));

        verticalLayout->addWidget(textEdit_3);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        splitter_3->addWidget(frame);
        tabWidget = new QTabWidget(splitter_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout = new QGridLayout(tab1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(tab1);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        downloadingView = new DownloadView(splitter_2);
        downloadingView->setObjectName(QStringLiteral("downloadingView"));
        splitter_2->addWidget(downloadingView);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        logEdit = new QTextEdit(layoutWidget);
        logEdit->setObjectName(QStringLiteral("logEdit"));
        logEdit->setReadOnly(true);

        verticalLayout_2->addWidget(logEdit);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        errorLogEdit = new QTextEdit(layoutWidget1);
        errorLogEdit->setObjectName(QStringLiteral("errorLogEdit"));
        errorLogEdit->setReadOnly(true);

        verticalLayout_3->addWidget(errorLogEdit);

        splitter->addWidget(layoutWidget1);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        gridLayout_2 = new QGridLayout(tab2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        downloadedView = new DownloadView(tab2);
        downloadedView->setObjectName(QStringLiteral("downloadedView"));

        gridLayout_2->addWidget(downloadedView, 0, 0, 1, 1);

        tabWidget->addTab(tab2, QString());
        splitter_3->addWidget(tabWidget);

        gridLayout_3->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 931, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Regexp", 0));
        label->setText(QApplication::translate("MainWindow", "Page Url:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Image Url:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Next Page:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Download log:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Download error log:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Downloading", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Downloaded", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
