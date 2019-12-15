/********************************************************************************
** Form generated from reading UI file 'helloqt.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOQT_H
#define UI_HELLOQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloqt
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *helloqt)
    {
        if (helloqt->objectName().isEmpty())
            helloqt->setObjectName(QString::fromUtf8("helloqt"));
        helloqt->resize(235, 131);
        centralWidget = new QWidget(helloqt);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(60, 0, 121, 51));
        helloqt->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(helloqt);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 235, 22));
        helloqt->setMenuBar(menuBar);
        mainToolBar = new QToolBar(helloqt);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        helloqt->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(helloqt);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        helloqt->setStatusBar(statusBar);

        retranslateUi(helloqt);

        QMetaObject::connectSlotsByName(helloqt);
    } // setupUi

    void retranslateUi(QMainWindow *helloqt)
    {
        helloqt->setWindowTitle(QApplication::translate("helloqt", "helloqt", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("helloqt", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hello Qt World!</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class helloqt: public Ui_helloqt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOQT_H
