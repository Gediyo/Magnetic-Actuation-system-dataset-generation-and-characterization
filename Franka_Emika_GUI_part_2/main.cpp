#include "mainwindow.h"

#include <QApplication>

// Register the QVector<double> type
Q_DECLARE_METATYPE(QVector<double>)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Register the type with Qt's meta-object system
    qRegisterMetaType<QVector<double>>("QVector<double>");


    MainWindow w;
    w.show();
    return a.exec();
}



