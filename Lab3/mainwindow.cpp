#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int userId, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_update_clicked();
    setWindowTitle("Лабораторная 3");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FAQinfo_triggered()
{
    FAQ faq(this);
    faq.exec();
}

QVector<int> MainWindow::combSort(const QVector<int> &vec){
    QVector<int> result_vec = vec;
    int step = result_vec.size();
    bool flag = false;
    while (step > 1 || flag) {
        if (step > 1) {
            step = step * 4 / 5;
        }
        flag = false;
        int i = 0;
        while (i + step < result_vec.size()) {
            if (result_vec[i] > result_vec[i + step]) {
                flag = true;
                qSwap(result_vec[i], result_vec[i + step]);
            }
            i += step;
        }
    }

    return result_vec;
}

QString MainWindow::vecToString(const QVector<int>& vec)
{
    QStringList list;
    for (int v : vec)
        list << QString::number(v);
    return list.join(" ");
}

QVector<int> MainWindow::strToVec(const QString& str)
{
    QVector<int> vec;
    QString cleaned = str;
    cleaned.replace(",", " ");
    QStringList list = cleaned.split(" ", Qt::SkipEmptyParts);
    for (const QString& s : list)
        vec.append(s.toInt());
    return vec;
}



void MainWindow::on_generateVec_clicked()
{
    currentVector.clear();
    int size = QRandomGenerator::global()->bounded(2, 20);
    for (int i = 0; i < size; ++i)
        currentVector.append(QRandomGenerator::global()->bounded(-1000, 1000));

    this->ui->vecScreen->setText(vecToString(currentVector));
    this->ui->vecScreen->raise();
    this->ui->mainStatus->setStyleSheet("color: green;");
    this->ui->mainStatus->setText("Массив успешно создан");
}


void MainWindow::on_sortVec_clicked()
{
    if (this->ui->vecScreen->text().isEmpty()) {
        this->ui->mainStatus->raise();
        this->ui->mainStatus->setStyleSheet("color: red");
        this->ui->mainStatus->setText("Массив не задан");
        return;
    }
    for(auto el : this->ui->vecScreen->text()){
        if(!el.isDigit() && el != ' '){
            this->ui->mainStatus->raise();
            this->ui->mainStatus->setStyleSheet("color: red");
            this->ui->mainStatus->setText("Массив некорректен");
            return;
        }
    }

    currentVector = strToVec(this->ui->vecScreen->text());
    QVector<int> sorted = combSort(currentVector);

    this->ui->vecScreen->setText(vecToString(sorted));
    this->ui->mainStatus->raise();
    this->ui->mainStatus->setStyleSheet("color: green");
    this->ui->mainStatus->setText("Массив успешно отсортирован");
}


void MainWindow::on_saveVec_clicked()
{
    QString text = this->ui->vecScreen->text();
    qDebug() << "input text =" << text;
    currentVector = strToVec(text);
    qDebug() << "parsed =" << currentVector;

    if (currentVector.isEmpty()) {
        this->ui->mainStatus->raise();
        this->ui->mainStatus->setStyleSheet("color: red");
        this->ui->mainStatus->setText("Массив не задан");
        return;
    }
    for(auto el : this->ui->vecScreen->text()){
        if(!el.isDigit() && el != ' '){
            this->ui->mainStatus->raise();
            this->ui->mainStatus->setStyleSheet("color: red");
            this->ui->mainStatus->setText("Массив некорректен");
            return;
        }
    }

    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("main.db");
    db.open();
    QSqlQuery query(db);
    query.prepare("INSERT INTO arrays(user_id, array) VALUES(:uid, :arr)");
    query.bindValue(":uid", userId);
    query.bindValue(":arr", vecToString(currentVector));

    if (!query.exec()) {
        this->ui->mainStatus->raise();
        this->ui->mainStatus->setStyleSheet("color: red");
        this->ui->mainStatus->setText("Не удалось создать запись");
        return;
    }

    this->ui->mainStatus->raise();
    this->ui->mainStatus->setStyleSheet("color: green");
    this->ui->mainStatus->setText("Массив успешно записан");

    on_update_clicked();
}


void MainWindow::on_update_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("main.db");
    QSqlQueryModel* model = new QSqlQueryModel(this->ui->allVec);
    model->setQuery("SELECT array FROM arrays WHERE user_id = " + QString::number(userId), db);
    this->ui->allVec->setModel(model);
}

