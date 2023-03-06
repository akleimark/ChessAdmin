#include "SettingsModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

QString SettingsModel::getSetting(const QString &key)
{
    const QString SQL = "select setting_data from settings where id='" + key + "' limit 1";

    QSqlQuery query;
    if(!query.exec(SQL))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }

    if(query.next())
    {
        return query.value(0).toString();
    }

    return "";

}

void SettingsModel::saveSetting(const QString &key, const QString &value)
{
    QString sql;

    // Inställningen finns ej sedan tidigare.
    if(SettingsModel::getSetting(key) == "")
    {
        sql = "insert into settings values('" + key + "', '" + value + "')";
    }
    else
    {
        sql = "update settings set setting_data='" + value + "' where id='" + key +"'";
    }

    QSqlQuery query;
    if(!query.exec(sql))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }
}
