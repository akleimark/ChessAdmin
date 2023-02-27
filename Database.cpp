#include "Database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>

Database* Database::instance = nullptr;
const QString Database::DATABASE_ENGINE = "QMARIADB";
const QString Database::DATABASE_HOSTNAME = "localhost";
const QString Database::DATABASE_NAME = "chessadmin";
const QString Database::DATABASE_USERNAME = "root";
const QString Database::DATABASE_PASSWORD = "Nic19820615klauS";
const QString Database::SQL_FILE_PATH = "/home/anders/Documents/Programming/Projects/C++/ChessAdmin/sqlStatements.sql";

Database::Database()
{
    database = nullptr;
}

Database* Database::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Database();
    }

    return instance;
}

void Database::connect(bool status)
{
    if(database == nullptr)
    {
        database = new QSqlDatabase;
        *database = QSqlDatabase::addDatabase(DATABASE_ENGINE);

        database->setHostName(DATABASE_HOSTNAME);
        database->setDatabaseName(DATABASE_NAME);
        database->setUserName(DATABASE_USERNAME);
        database->setPassword(DATABASE_PASSWORD);
    }

    if(status == true)
    {
        if(!database->isOpen())
        {
            if(!database->open())
            {
                throw std::runtime_error("Det gick inte att ansluta till databasen." + database->lastError().text().toStdString());
            }
            else
            {
                std::cout << "Anslutningen lyckades." << std::endl;
            }
        }
    }
    else
    {
        if(database->isOpen())
        {
            database->close();
        }
    }
}

void Database::createTables()
{
    QStringList sqlStatements;
    QFile inputFile(SQL_FILE_PATH);
    QString sql = "";
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(line.startsWith('#'))
          {
              continue;
          }
          sql.append(line);
          if(line.length() == 0)
          {
              sql = sql.simplified();
              if(sql.length() != 0)
              {
                  sqlStatements.append(sql);
              }
              sql = "";
          }
       }
       inputFile.close();
    }

    for(QString &item : sqlStatements)
    {
        QSqlQuery query;

        if(!query.exec(item))
        {
            std::cout << query.lastError().text().toStdString() << std::endl;
        }        
    }
}
