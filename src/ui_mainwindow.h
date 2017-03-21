/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *recOptions;
    QVBoxLayout *verticalLayout;
    QLineEdit *projectName;
    QPushButton *pushButton;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *fps_box;
    QCheckBox *checkBox;
    QPushButton *preview_button;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QComboBox *cameraSelector;
    QLabel *label;
    QPushButton *camScanButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QLabel *preview_widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(180, 374);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        recOptions = new QFrame(centralWidget);
        recOptions->setObjectName(QStringLiteral("recOptions"));
        recOptions->setEnabled(true);
        sizePolicy.setHeightForWidth(recOptions->sizePolicy().hasHeightForWidth());
        recOptions->setSizePolicy(sizePolicy);
        recOptions->setFrameShape(QFrame::StyledPanel);
        recOptions->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(recOptions);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        projectName = new QLineEdit(recOptions);
        projectName->setObjectName(QStringLiteral("projectName"));
        projectName->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(projectName);

        pushButton = new QPushButton(recOptions);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFlat(false);

        verticalLayout->addWidget(pushButton);

        frame_3 = new QFrame(recOptions);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(134, 48));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        fps_box = new QSpinBox(frame_3);
        fps_box->setObjectName(QStringLiteral("fps_box"));
        fps_box->setValue(18);

        horizontalLayout->addWidget(fps_box);


        verticalLayout->addWidget(frame_3);

        checkBox = new QCheckBox(recOptions);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        preview_button = new QPushButton(recOptions);
        preview_button->setObjectName(QStringLiteral("preview_button"));
        preview_button->setCheckable(true);

        verticalLayout->addWidget(preview_button);


        gridLayout->addWidget(recOptions, 1, 0, 1, 1);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cameraSelector = new QComboBox(frame_2);
        cameraSelector->setObjectName(QStringLiteral("cameraSelector"));
        cameraSelector->setEditable(false);

        gridLayout_2->addWidget(cameraSelector, 0, 1, 1, 1);

        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        camScanButton = new QPushButton(frame_2);
        camScanButton->setObjectName(QStringLiteral("camScanButton"));

        gridLayout_2->addWidget(camScanButton, 1, 0, 1, 2);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 2, 0, 1, 2);


        gridLayout->addWidget(frame_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        preview_widget = new QLabel(centralWidget);
        preview_widget->setObjectName(QStringLiteral("preview_widget"));

        gridLayout->addWidget(preview_widget, 0, 1, 2, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Taevitas", Q_NULLPTR));
        projectName->setPlaceholderText(QApplication::translate("MainWindow", "Project Name", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "FPS: ", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "  Save Frames", Q_NULLPTR));
        preview_button->setText(QApplication::translate("MainWindow", "Preview Camera", Q_NULLPTR));
        cameraSelector->setCurrentText(QString());
        label->setText(QApplication::translate("MainWindow", "Camera:", Q_NULLPTR));
        camScanButton->setText(QApplication::translate("MainWindow", "Rescan Cameras", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Output Folder", Q_NULLPTR));
        preview_widget->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
