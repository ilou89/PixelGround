#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *app = MainWindow::getInstance();
    app->show();
    return a.exec();
}
