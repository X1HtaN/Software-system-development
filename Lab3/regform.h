#ifndef REGFORM_H
#define REGFORM_H

#include "dbconnect.h"

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class regForm;
}

class regForm : public QDialog
{
    Q_OBJECT

public:
    explicit regForm(QDialog *parent = nullptr);
    ~regForm();

private slots:
    void on_regFormBtn_clicked();

private:
    Ui::regForm *ui;
};

#endif // REGFORM_H
