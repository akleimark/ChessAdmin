#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>

class Table : public QTableWidget
{
    public:
        Table(const QStringList &columnNames, QWidget *parent = nullptr);

    private:
        const QStringList COLUMN_NAMES;
};

#endif // TABLE_H
