/********************************************************************************
** Form generated from reading UI file 'editmodalwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMODALWINDOW_H
#define UI_EDITMODALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editModalWindow
{
public:
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
    QSpacerItem *verticalSpacer_4;
    QPushButton *blacklistEditButton;
    QSpacerItem *verticalSpacer;
    QPushButton *deleteAppButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *editAppButton;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshListButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *editModalWindow)
    {
        if (editModalWindow->objectName().isEmpty())
            editModalWindow->setObjectName("editModalWindow");
        editModalWindow->resize(800, 600);
        editModalWindow->setMinimumSize(QSize(400, 400));
        gridLayout = new QGridLayout(editModalWindow);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        appsScrollArea = new QScrollArea(editModalWindow);
        appsScrollArea->setObjectName("appsScrollArea");
        appsScrollArea->setEnabled(true);
        appsScrollArea->setAutoFillBackground(false);
        appsScrollArea->setStyleSheet(QString::fromUtf8(""));
        appsScrollArea->setWidgetResizable(true);
        appsScrollAreaWidget = new QWidget();
        appsScrollAreaWidget->setObjectName("appsScrollAreaWidget");
        appsScrollAreaWidget->setGeometry(QRect(0, 0, 774, 574));
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
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        line_5 = new QFrame(appsScrollAreaWidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_5);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        blacklistEditButton = new QPushButton(appsScrollAreaWidget);
        blacklistEditButton->setObjectName("blacklistEditButton");
        blacklistEditButton->setMinimumSize(QSize(0, 50));

        verticalLayout_2->addWidget(blacklistEditButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        deleteAppButton = new QPushButton(appsScrollAreaWidget);
        deleteAppButton->setObjectName("deleteAppButton");
        deleteAppButton->setMinimumSize(QSize(0, 50));
        deleteAppButton->setBaseSize(QSize(0, 0));

        verticalLayout_2->addWidget(deleteAppButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        editAppButton = new QPushButton(appsScrollAreaWidget);
        editAppButton->setObjectName("editAppButton");
        editAppButton->setMinimumSize(QSize(0, 50));

        verticalLayout_2->addWidget(editAppButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refreshListButton = new QPushButton(appsScrollAreaWidget);
        refreshListButton->setObjectName("refreshListButton");
        refreshListButton->setMinimumSize(QSize(0, 25));
        refreshListButton->setBaseSize(QSize(0, 0));

        horizontalLayout->addWidget(refreshListButton);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        appsScrollArea->setWidget(appsScrollAreaWidget);

        verticalLayout->addWidget(appsScrollArea);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(editModalWindow);

        QMetaObject::connectSlotsByName(editModalWindow);
    } // setupUi

    void retranslateUi(QDialog *editModalWindow)
    {
        editModalWindow->setWindowTitle(QCoreApplication::translate("editModalWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("editModalWindow", "ApplicationName", nullptr));
        label_2->setText(QCoreApplication::translate("editModalWindow", "Edit info", nullptr));
        blacklistEditButton->setText(QCoreApplication::translate("editModalWindow", "Blacklist edit", nullptr));
        deleteAppButton->setText(QCoreApplication::translate("editModalWindow", "Delete Application from list", nullptr));
        editAppButton->setText(QCoreApplication::translate("editModalWindow", "Edit Application's Name", nullptr));
        refreshListButton->setText(QCoreApplication::translate("editModalWindow", "Refresh Apps List", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editModalWindow: public Ui_editModalWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMODALWINDOW_H
