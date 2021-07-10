#include "hdr/mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile("./SyNet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    QSurfaceFormat fmt;
    fmt.setVersion(3,3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);
    MainWindow w;
    w.show();

    return a.exec();
}
