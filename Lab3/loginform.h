#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "mainwindow.h"
#include "dbconnect.h"
#include "regform.h"

#include <QDialog>
#include <QString>
#include <QScrollBar>

namespace Ui {
class loginForm;
}

class loginForm : public QDialog
{
    Q_OBJECT

public:
    explicit loginForm(QDialog *parent = nullptr);
    ~loginForm();

    int getUserId() const {return userId;}

private slots:
    void on_loginBtn_clicked();

    void on_regLoginBtn_clicked();

signals:
    void loginSuccess();

private:
    Ui::loginForm *ui;
    int userId = -1;
};

#endif // LOGINFORM_H
