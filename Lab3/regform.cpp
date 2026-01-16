#include "regform.h"
#include "ui_regform.h"

regForm::regForm(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::regForm)
{
    ui->setupUi(this);

    setWindowTitle("Регистрация");
    this->ui->regErrMsg->clear();
}

regForm::~regForm()
{
    delete ui;
}

void regForm::on_regFormBtn_clicked()
{
    QString login = this->ui->regFormL->toPlainText();
    QString pwd = this->ui->regFormP->toPlainText();
    if(login.isEmpty() || pwd.isEmpty()){
        this->ui->regErrMsg->setStyleSheet("color: rgb(255,0,0);");
        this->ui->regErrMsg->setText("Поля Логин или Пароль пусты");
        return;
    } else {
        this->ui->regErrMsg->clear();

        if(DBConnect::regUser(login, pwd)){
            accept();
        } else {
            this->ui->regErrMsg->setStyleSheet("color: rgb(255,0,0);");
            this->ui->regErrMsg->setText("Не удалось создать запись в БД");
        }
    }
}

