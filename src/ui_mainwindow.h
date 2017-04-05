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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
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
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QComboBox *cameraSelector;
    QLabel *label;
    QFormLayout *formLayout_4;
    QLabel *label_6;
    QComboBox *serialSelector;
    QPushButton *camScanButton;
    QPushButton *serialScanButton;
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
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *statusLabel;
    QWidget *recStats;
    QGridLayout *gridLayout_2;
    QLCDNumber *timeCaptured;
    QLCDNumber *framesCaptured;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *buffer;
    QLabel *label_5;
    QLabel *preview_widget;
    QGroupBox *serialControl;
    QVBoxLayout *verticalLayout_3;
    QPushButton *sRun;
    QPushButton *sHalt;
    QPushButton *sFast;
    QPlainTextEdit *serialMon;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(478, 965);
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
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(190, 409));
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
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cameraSelector->sizePolicy().hasHeightForWidth());
        cameraSelector->setSizePolicy(sizePolicy2);
        cameraSelector->setEditable(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, cameraSelector);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        verticalLayout->addLayout(formLayout);

        formLayout_4 = new QFormLayout();
        formLayout_4->setSpacing(6);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_6);

        serialSelector = new QComboBox(groupBox);
        serialSelector->setObjectName(QStringLiteral("serialSelector"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, serialSelector);


        verticalLayout->addLayout(formLayout_4);

        camScanButton = new QPushButton(groupBox);
        camScanButton->setObjectName(QStringLiteral("camScanButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(camScanButton->sizePolicy().hasHeightForWidth());
        camScanButton->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(camScanButton);

        serialScanButton = new QPushButton(groupBox);
        serialScanButton->setObjectName(QStringLiteral("serialScanButton"));

        verticalLayout->addWidget(serialScanButton);

        directorySelector = new QPushButton(groupBox);
        directorySelector->setObjectName(QStringLiteral("directorySelector"));
        sizePolicy3.setHeightForWidth(directorySelector->sizePolicy().hasHeightForWidth());
        directorySelector->setSizePolicy(sizePolicy3);

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
        sizePolicy3.setHeightForWidth(fps_box->sizePolicy().hasHeightForWidth());
        fps_box->setSizePolicy(sizePolicy3);
        fps_box->setValue(18);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, fps_box);


        verticalLayout_4->addLayout(formLayout_2);

        saveFrames = new QCheckBox(recOptions);
        saveFrames->setObjectName(QStringLiteral("saveFrames"));
        saveFrames->setEnabled(true);

        verticalLayout_4->addWidget(saveFrames, 0, Qt::AlignHCenter);

        startButton = new QPushButton(recOptions);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setEnabled(false);
        sizePolicy3.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy3);
        startButton->setFlat(false);

        verticalLayout_4->addWidget(startButton);

        preview_button = new QPushButton(recOptions);
        preview_button->setObjectName(QStringLiteral("preview_button"));
        sizePolicy3.setHeightForWidth(preview_button->sizePolicy().hasHeightForWidth());
        preview_button->setSizePolicy(sizePolicy3);
        preview_button->setCheckable(true);

        verticalLayout_4->addWidget(preview_button);


        verticalLayout->addWidget(recOptions);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        statusLabel = new QLabel(groupBox_2);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));

        verticalLayout_2->addWidget(statusLabel);

        recStats = new QWidget(groupBox_2);
        recStats->setObjectName(QStringLiteral("recStats"));
        gridLayout_2 = new QGridLayout(recStats);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        timeCaptured = new QLCDNumber(recStats);
        timeCaptured->setObjectName(QStringLiteral("timeCaptured"));

        gridLayout_2->addWidget(timeCaptured, 1, 1, 1, 1);

        framesCaptured = new QLCDNumber(recStats);
        framesCaptured->setObjectName(QStringLiteral("framesCaptured"));

        gridLayout_2->addWidget(framesCaptured, 1, 0, 1, 1);

        label_3 = new QLabel(recStats);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1, Qt::AlignHCenter);

        label_4 = new QLabel(recStats);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 1, 1, 1, Qt::AlignHCenter);

        buffer = new QLCDNumber(recStats);
        buffer->setObjectName(QStringLiteral("buffer"));

        gridLayout_2->addWidget(buffer, 3, 0, 1, 2, Qt::AlignHCenter);

        label_5 = new QLabel(recStats);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 2, Qt::AlignHCenter);


        verticalLayout_2->addWidget(recStats);


        gridLayout->addWidget(groupBox_2, 4, 0, 1, 1);

        preview_widget = new QLabel(centralWidget);
        preview_widget->setObjectName(QStringLiteral("preview_widget"));
        preview_widget->setEnabled(false);
        preview_widget->setFrameShape(QFrame::StyledPanel);
        preview_widget->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(preview_widget, 0, 2, 5, 1);

        serialControl = new QGroupBox(centralWidget);
        serialControl->setObjectName(QStringLiteral("serialControl"));
        verticalLayout_3 = new QVBoxLayout(serialControl);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        sRun = new QPushButton(serialControl);
        sRun->setObjectName(QStringLiteral("sRun"));

        verticalLayout_3->addWidget(sRun);

        sHalt = new QPushButton(serialControl);
        sHalt->setObjectName(QStringLiteral("sHalt"));

        verticalLayout_3->addWidget(sHalt);

        sFast = new QPushButton(serialControl);
        sFast->setObjectName(QStringLiteral("sFast"));

        verticalLayout_3->addWidget(sFast);

        serialMon = new QPlainTextEdit(serialControl);
        serialMon->setObjectName(QStringLiteral("serialMon"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(serialMon->sizePolicy().hasHeightForWidth());
        serialMon->setSizePolicy(sizePolicy4);
        serialMon->setReadOnly(true);

        verticalLayout_3->addWidget(serialMon);


        gridLayout->addWidget(serialControl, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Taevitas", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        cameraSelector->setCurrentText(QString());
        label->setText(QApplication::translate("MainWindow", "Camera:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Serial Port:", Q_NULLPTR));
        camScanButton->setText(QApplication::translate("MainWindow", "Rescan Cameras", Q_NULLPTR));
        serialScanButton->setText(QApplication::translate("MainWindow", "Rescan Serial Ports", Q_NULLPTR));
        directorySelector->setText(QApplication::translate("MainWindow", "Working Directory", Q_NULLPTR));
        recOptions->setTitle(QApplication::translate("MainWindow", "Recorder Settings", Q_NULLPTR));
        projectName->setPlaceholderText(QApplication::translate("MainWindow", "Project Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "FPS: ", Q_NULLPTR));
        saveFrames->setText(QApplication::translate("MainWindow", "  Save Frames", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        preview_button->setText(QApplication::translate("MainWindow", "Preview Camera", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        statusLabel->setText(QApplication::translate("MainWindow", "Waiting.", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Frames", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Minutes", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Buffer", Q_NULLPTR));
        preview_widget->setText(QString());
        serialControl->setTitle(QApplication::translate("MainWindow", "Serial Control", Q_NULLPTR));
        sRun->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        sHalt->setText(QApplication::translate("MainWindow", "Halt", Q_NULLPTR));
        sFast->setText(QApplication::translate("MainWindow", "Fast", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
