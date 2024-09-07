/********************************************************************************
** Form generated from reading UI file 'calib.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIB_H
#define UI_CALIB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calib
{
public:
    QLineEdit *x_dir;
    QLineEdit *y_dir;
    QLineEdit *z_dir;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushbutton_move;
    QPushButton *pushButton_record;
    QPushButton *pushButton_stop_record;
    QRadioButton *radioButton_record_status;
    QPushButton *pushButton_pauseRecording;
    QPushButton *pushButton_setReference;
    QPushButton *pushButton_start_3D_sweep;
    QPushButton *pushButton_init_pos;
    QPushButton *pushButton_GausstoOrigin;

    void setupUi(QWidget *Calib)
    {
        if (Calib->objectName().isEmpty())
            Calib->setObjectName("Calib");
        Calib->resize(815, 529);
        x_dir = new QLineEdit(Calib);
        x_dir->setObjectName("x_dir");
        x_dir->setGeometry(QRect(150, 70, 113, 20));
        y_dir = new QLineEdit(Calib);
        y_dir->setObjectName("y_dir");
        y_dir->setGeometry(QRect(150, 110, 113, 20));
        z_dir = new QLineEdit(Calib);
        z_dir->setObjectName("z_dir");
        z_dir->setGeometry(QRect(150, 150, 113, 20));
        label = new QLabel(Calib);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 70, 81, 16));
        label_2 = new QLabel(Calib);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 110, 81, 16));
        label_3 = new QLabel(Calib);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 150, 81, 16));
        pushbutton_move = new QPushButton(Calib);
        pushbutton_move->setObjectName("pushbutton_move");
        pushbutton_move->setGeometry(QRect(140, 200, 121, 31));
        pushbutton_move->setAutoDefault(false);
        pushbutton_move->setFlat(false);
        pushButton_record = new QPushButton(Calib);
        pushButton_record->setObjectName("pushButton_record");
        pushButton_record->setGeometry(QRect(580, 70, 121, 23));
        pushButton_stop_record = new QPushButton(Calib);
        pushButton_stop_record->setObjectName("pushButton_stop_record");
        pushButton_stop_record->setGeometry(QRect(580, 110, 121, 23));
        radioButton_record_status = new QRadioButton(Calib);
        radioButton_record_status->setObjectName("radioButton_record_status");
        radioButton_record_status->setEnabled(false);
        radioButton_record_status->setGeometry(QRect(580, 40, 111, 17));
        radioButton_record_status->setCheckable(true);
        pushButton_pauseRecording = new QPushButton(Calib);
        pushButton_pauseRecording->setObjectName("pushButton_pauseRecording");
        pushButton_pauseRecording->setGeometry(QRect(580, 150, 121, 23));
        pushButton_setReference = new QPushButton(Calib);
        pushButton_setReference->setObjectName("pushButton_setReference");
        pushButton_setReference->setGeometry(QRect(340, 70, 141, 31));
        pushButton_start_3D_sweep = new QPushButton(Calib);
        pushButton_start_3D_sweep->setObjectName("pushButton_start_3D_sweep");
        pushButton_start_3D_sweep->setGeometry(QRect(340, 140, 141, 31));
        pushButton_init_pos = new QPushButton(Calib);
        pushButton_init_pos->setObjectName("pushButton_init_pos");
        pushButton_init_pos->setGeometry(QRect(50, 290, 171, 31));
        pushButton_GausstoOrigin = new QPushButton(Calib);
        pushButton_GausstoOrigin->setObjectName("pushButton_GausstoOrigin");
        pushButton_GausstoOrigin->setGeometry(QRect(50, 370, 171, 31));

        retranslateUi(Calib);

        pushbutton_move->setDefault(false);


        QMetaObject::connectSlotsByName(Calib);
    } // setupUi

    void retranslateUi(QWidget *Calib)
    {
        Calib->setWindowTitle(QCoreApplication::translate("Calib", "Form", nullptr));
        label->setText(QCoreApplication::translate("Calib", "X-direction (mm)", nullptr));
        label_2->setText(QCoreApplication::translate("Calib", "y-direction (mm)", nullptr));
        label_3->setText(QCoreApplication::translate("Calib", "z-direction (mm)", nullptr));
        pushbutton_move->setText(QCoreApplication::translate("Calib", "Move", nullptr));
        pushButton_record->setText(QCoreApplication::translate("Calib", "Start recording", nullptr));
        pushButton_stop_record->setText(QCoreApplication::translate("Calib", "Stop recording", nullptr));
        radioButton_record_status->setText(QCoreApplication::translate("Calib", "Recording status", nullptr));
        pushButton_pauseRecording->setText(QCoreApplication::translate("Calib", "Pause recording", nullptr));
        pushButton_setReference->setText(QCoreApplication::translate("Calib", "Set reference position", nullptr));
        pushButton_start_3D_sweep->setText(QCoreApplication::translate("Calib", "Start 3D sweep", nullptr));
        pushButton_init_pos->setText(QCoreApplication::translate("Calib", "Move robot to initial position", nullptr));
        pushButton_GausstoOrigin->setText(QCoreApplication::translate("Calib", "Move Gauss-Probe to Origin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calib: public Ui_Calib {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIB_H
