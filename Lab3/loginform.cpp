#include "loginform.h"
#include "ui_loginform.h"

loginForm::loginForm(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::loginForm)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");

    this->ui->loginLForm->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->loginPForm->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->loginerr->setText("");
}

loginForm::~loginForm()
{
    delete ui;
}

void loginForm::on_loginBtn_clicked()
{
    QString login = this->ui->loginLForm->toPlainText();
    QString pwd = this->ui->loginPForm->toPlainText();

    if(login.isEmpty() || pwd.isEmpty()){
        this->ui->loginerr->setStyleSheet("color: rgb(255,0,0);");
        this->ui->loginerr->setText("Поля Логин или Пароль пусты");
        return;
    } else {
        this->ui->loginerr->clear();
    }
    if(login.size() > 30 || pwd.size() > 30){
        this->ui->loginerr->setStyleSheet("color: rgb(255,0,0);");
        this->ui->loginerr->setText("Поля не могут содержать больше 30 символов");
        return;
    } else {
        this->ui->loginerr->clear();
    }

    if(DBConnect::authUser(login, pwd, userId)){
        emit loginSuccess();
        accept();
    } else {
        this->ui->loginerr->setStyleSheet("color: rgb(255,0,0);");
        this->ui->loginerr->setText("Неверный Логин или Пароль");
    }
}


void loginForm::on_regLoginBtn_clicked()
{
    regForm rf(this);
    rf.exec();
}

