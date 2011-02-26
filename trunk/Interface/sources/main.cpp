#include <QApplication>

#include "Windows/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    application.setApplicationName("Effex");
    application.setOrganizationName("HEIG-VD");

    MainWindow mainWindow;

    mainWindow.show();

    return application.exec();
}
