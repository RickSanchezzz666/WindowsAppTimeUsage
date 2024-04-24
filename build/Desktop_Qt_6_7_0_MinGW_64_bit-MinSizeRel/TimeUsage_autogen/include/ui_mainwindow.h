/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QScrollArea *appsScrollArea;
    QWidget *appsScrollAreaWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_1;
    QLabel *label;
    QFrame *line_4;
    QLabel *appsOutputLabel;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QFrame *line_5;
    QLabel *appsOutputLabel_2;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QFrame *line_6;
    QLabel *appsOutputLabel_3;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QFrame *line_7;
    QLabel *appsOutputLabel_4;
    QFrame *line_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QFrame *line_8;
    QLabel *appsOutputLabel_5;
    QFrame *line_11;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QFrame *line_10;
    QLabel *appsOutputLabel_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 245);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        appsScrollArea = new QScrollArea(centralwidget);
        appsScrollArea->setObjectName("appsScrollArea");
        appsScrollArea->setEnabled(true);
        appsScrollArea->setAutoFillBackground(false);
        appsScrollArea->setStyleSheet(QString::fromUtf8(""));
        appsScrollArea->setWidgetResizable(true);
        appsScrollAreaWidget = new QWidget();
        appsScrollAreaWidget->setObjectName("appsScrollAreaWidget");
        appsScrollAreaWidget->setGeometry(QRect(0, 0, 974, 524));
        horizontalLayout_2 = new QHBoxLayout(appsScrollAreaWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName("verticalLayout_1");
        label = new QLabel(appsScrollAreaWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 20));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_1->addWidget(label);

        line_4 = new QFrame(appsScrollAreaWidget);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_1->addWidget(line_4);

        appsOutputLabel = new QLabel(appsScrollAreaWidget);
        appsOutputLabel->setObjectName("appsOutputLabel");
        appsOutputLabel->setMinimumSize(QSize(0, 0));
        appsOutputLabel->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_1->addWidget(appsOutputLabel);


        horizontalLayout_2->addLayout(verticalLayout_1);

        line = new QFrame(appsScrollAreaWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(appsScrollAreaWidget);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777215, 20));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_2);

        line_5 = new QFrame(appsScrollAreaWidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_5);

        appsOutputLabel_2 = new QLabel(appsScrollAreaWidget);
        appsOutputLabel_2->setObjectName("appsOutputLabel_2");
        appsOutputLabel_2->setMinimumSize(QSize(0, 0));
        appsOutputLabel_2->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel_2->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(appsOutputLabel_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        line_2 = new QFrame(appsScrollAreaWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(appsScrollAreaWidget);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_3);

        line_6 = new QFrame(appsScrollAreaWidget);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_6);

        appsOutputLabel_3 = new QLabel(appsScrollAreaWidget);
        appsOutputLabel_3->setObjectName("appsOutputLabel_3");
        appsOutputLabel_3->setMinimumSize(QSize(0, 0));
        appsOutputLabel_3->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel_3->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel_3->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_3->addWidget(appsOutputLabel_3);


        horizontalLayout_2->addLayout(verticalLayout_3);

        line_3 = new QFrame(appsScrollAreaWidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_4 = new QLabel(appsScrollAreaWidget);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(16777215, 20));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_4);

        line_7 = new QFrame(appsScrollAreaWidget);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_7);

        appsOutputLabel_4 = new QLabel(appsScrollAreaWidget);
        appsOutputLabel_4->setObjectName("appsOutputLabel_4");
        appsOutputLabel_4->setMinimumSize(QSize(0, 0));
        appsOutputLabel_4->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel_4->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel_4->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_4->addWidget(appsOutputLabel_4);


        horizontalLayout_2->addLayout(verticalLayout_4);

        line_9 = new QFrame(appsScrollAreaWidget);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::VLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_9);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_5 = new QLabel(appsScrollAreaWidget);
        label_5->setObjectName("label_5");
        label_5->setMaximumSize(QSize(16777215, 20));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_5);

        line_8 = new QFrame(appsScrollAreaWidget);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::HLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_5->addWidget(line_8);

        appsOutputLabel_5 = new QLabel(appsScrollAreaWidget);
        appsOutputLabel_5->setObjectName("appsOutputLabel_5");
        appsOutputLabel_5->setMinimumSize(QSize(0, 0));
        appsOutputLabel_5->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel_5->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel_5->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_5->addWidget(appsOutputLabel_5);


        horizontalLayout_2->addLayout(verticalLayout_5);

        line_11 = new QFrame(appsScrollAreaWidget);
        line_11->setObjectName("line_11");
        line_11->setFrameShape(QFrame::Shape::VLine);
        line_11->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_11);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_6 = new QLabel(appsScrollAreaWidget);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(16777215, 20));
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_6);

        line_10 = new QFrame(appsScrollAreaWidget);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::Shape::HLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_6->addWidget(line_10);

        appsOutputLabel_6 = new QLabel(appsScrollAreaWidget);
        appsOutputLabel_6->setObjectName("appsOutputLabel_6");
        appsOutputLabel_6->setMinimumSize(QSize(0, 0));
        appsOutputLabel_6->setFocusPolicy(Qt::NoFocus);
        appsOutputLabel_6->setStyleSheet(QString::fromUtf8(""));
        appsOutputLabel_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        appsOutputLabel_6->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_6->addWidget(appsOutputLabel_6);


        horizontalLayout_2->addLayout(verticalLayout_6);

        appsScrollArea->setWidget(appsScrollAreaWidget);

        verticalLayout->addWidget(appsScrollArea);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ApplicationName", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Last Launch Date", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Last Exit Date", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Last Session Time", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Current Session Time", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Total Time Spent (minutes)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
