#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
    public:
        static Database* getInstance();
        void connect(bool status = true);
        void createTables();

    private:
        Database();
        static Database* instance;
        QSqlDatabase *database;
        const static QString DATABASE_ENGINE;
        const static QString DATABASE_HOSTNAME;
        const static QString DATABASE_NAME;
        const static QString DATABASE_USERNAME;
        const static QString DATABASE_PASSWORD;
        const static QString SQL_FILE_PATH;
};

class DatabaseInterface
{
    public:
        DatabaseInterface() {}
        virtual ~DatabaseInterface() {}        
        virtual void save(const bool &createNew) = 0;
        virtual void remove() = 0;       
};

#endif // DATABASE_H
