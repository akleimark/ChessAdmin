#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include "MVC.h"

class SettingsModel : public Model
{
    public:

        virtual ~SettingsModel() {}
        static QString getSetting(const QString &key);
        static void saveSetting(const QString &key, const QString &value);

    private:
        SettingsModel() {}
};

#endif // SETTINGSMODEL_H
