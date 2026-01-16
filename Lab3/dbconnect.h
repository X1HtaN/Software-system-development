#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>

class DBConnect
{
public:
    DBConnect();
    static void initDB();
    static bool regUser(const QString& username, const QString& pwd);
    static bool authUser(const QString& username, const QString& pwd, int& userId);
private:
    static QString hashPwd(const QString& pwd);
};

#endif // DBCONNECT_H
