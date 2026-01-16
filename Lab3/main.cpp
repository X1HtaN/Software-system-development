#include "loginForm.h"
#include "mainwindow.h"
#include "dbconnect.h"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DBConnect dbcon;
    DBConnect::initDB();

    loginForm lf;
    if(lf.exec() == QDialog::Accepted){
        int userId = lf.getUserId();
        MainWindow mainWindow(userId);
        mainWindow.show();
        return app.exec();
    }

    return EXIT_SUCCESS;
}
