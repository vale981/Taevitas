/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QLabel *preview_widget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QComboBox *cameraSelector;
    QLabel *label;
    QPushButton *camScanButton;
    QPushButton *directorySelector;
    QGroupBox *recOptions;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *projectName;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QSpinBox *fps_box;
    QCheckBox *saveFrames;
    QPushButton *startButton;
    QPushButton *preview_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(465, 584);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
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
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        gridLayout->addWidget(groupBox_2, 3, 0, 1, 1);

        preview_widget = new QLabel(centralWidget);
        preview_widget->setObjectName(QStringLiteral("preview_widget"));
        preview_widget->setEnabled(false);
        preview_widget->setFrameShape(QFrame::StyledPanel);
        preview_widget->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(preview_widget, 1, 1, 3, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMaximumSize(QSize(190, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setVerticalSpacing(0);
        cameraSelector = new QComboBox(groupBox);
        cameraSelector->setObjectName(QStringLiteral("cameraSelector"));
        cameraSelector->setEditable(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, cameraSelector);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        verticalLayout->addLayout(formLayout);

        camScanButton = new QPushButton(groupBox);
        camScanButton->setObjectName(QStringLiteral("camScanButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(camScanButton->sizePolicy().hasHeightForWidth());
        camScanButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(camScanButton);

        directorySelector = new QPushButton(groupBox);
        directorySelector->setObjectName(QStringLiteral("directorySelector"));
        sizePolicy2.setHeightForWidth(directorySelector->sizePolicy().hasHeightForWidth());
        directorySelector->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(directorySelector);

        recOptions = new QGroupBox(groupBox);
        recOptions->setObjectName(QStringLiteral("recOptions"));
        sizePolicy1.setHeightForWidth(recOptions->sizePolicy().hasHeightForWidth());
        recOptions->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(recOptions);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        projectName = new QLineEdit(recOptions);
        projectName->setObjectName(QStringLiteral("projectName"));
        projectName->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(projectName);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_2 = new QLabel(recOptions);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        fps_box = new QSpinBox(recOptions);
        fps_box->setObjectName(QStringLiteral("fps_box"));
        sizePolicy2.setHeightForWidth(fps_box->sizePolicy().hasHeightForWidth());
        fps_box->setSizePolicy(sizePolicy2);
        fps_box->setValue(18);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, fps_box);


        verticalLayout_4->addLayout(formLayout_2);

        saveFrames = new QCheckBox(recOptions);
        saveFrames->setObjectName(QStringLiteral("saveFrames"));
        saveFrames->setEnabled(true);

        verticalLayout_4->addWidget(saveFrames);

        startButton = new QPushButton(recOptions);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setEnabled(false);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        startButton->setFlat(false);

        verticalLayout_4->addWidget(startButton);

        preview_button = new QPushButton(recOptions);
        preview_button->setObjectName(QStringLiteral("preview_button"));
        sizePolicy2.setHeightForWidth(preview_button->sizePolicy().hasHeightForWidth());
        preview_button->setSizePolicy(sizePolicy2);
        preview_button->setCheckable(true);

        verticalLayout_4->addWidget(preview_button);


        verticalLayout->addWidget(recOptions);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Taevitas", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        preview_widget->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        cameraSelector->setCurrentText(QString());
        label->setText(QApplication::translate("MainWindow", "Camera:", Q_NULLPTR));
        camScanButton->setText(QApplication::translate("MainWindow", "Rescan Cameras", Q_NULLPTR));
        directorySelector->setText(QApplication::translate("MainWindow", "Working Directory", Q_NULLPTR));
        recOptions->setTitle(QApplication::translate("MainWindow", "Recorder Settings", Q_NULLPTR));
        projectName->setPlaceholderText(QApplication::translate("MainWindow", "Project Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "FPS: ", Q_NULLPTR));
        saveFrames->setText(QApplication::translate("MainWindow", "  Save Frames", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        preview_button->setText(QApplication::translate("MainWindow", "Preview Camera", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
