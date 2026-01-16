#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "faq.h"

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QRandomGenerator>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_FAQinfo_triggered();

    void on_generateVec_clicked();

    void on_sortVec_clicked();

    void on_saveVec_clicked();

    void on_update_clicked();

private:
    Ui::MainWindow *ui;

    QString vecToString(const QVector<int>& vec);
    QVector<int> strToVec(const QString& str);

    QVector<int> combSort(const QVector<int>& vec);

    QVector<int> currentVector;
    int userId;
};
#endif // MAINWINDOW_H
