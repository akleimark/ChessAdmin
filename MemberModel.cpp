#include "MemberModel.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

std::set<MemberModel*> MemberModel::container;

MemberModel::MemberModel():
    id(0), firstname(""), lastname(""), birthdate(""), biologicalSex("")
{
    TABLE_NAME = "members";
    id = 0;
    firstname = "";
    lastname = "";
    birthdate = "";
    biologicalSex = "";
    streetAddress = "";
    zipCode = 0;
    city = "";
    phoneNumber = "";
    emailAddress = "";
}

MemberModel::~MemberModel()
{

}

bool MemberModel::checkName(const QString &name) const
{
    const QString ILLEGAL_CHARS = "0123456789";

    for(int i = 0; i < name.length(); i++)
    {
        for(int j = 0; j < ILLEGAL_CHARS.length(); j++)
        {
            if(name[i] == ILLEGAL_CHARS[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool MemberModel::checkPhoneNumber(const QString &number) const
{
    const QString LEGAL_CHARS = "0123456789-";

    for(int i = 0; i < number.length(); i++)
    {
        bool legal = false;
        for(int j = 0; j < LEGAL_CHARS.length(); j++)
        {
            if(number[i] == LEGAL_CHARS[j])
            {
                legal = true;
                break;
            }
        }
        if(!legal)
        {
            return false;
        }
    }
    return true;
}

bool MemberModel::checkNumber(const QString &number) const
{
    const QString LEGAL_CHARS = "0123456789";

    for(int i = 0; i < number.length(); i++)
    {
        bool legal = false;
        for(int j = 0; j < LEGAL_CHARS.length(); j++)
        {
            if(number[i] == LEGAL_CHARS[j])
            {
                legal = true;
                break;
            }
        }
        if(!legal)
        {
            return false;
        }
    }
    return true;
}

bool MemberModel::checkEmailAddress(const QString &address) const
{
    if(address.length() == 0)
    {
        return true;
    }

    if(address.length() < 5)
    {
        return false;
    }

    const QString MANDATORY_CHARS = "@.";
    const QString ILLEGAL_CHARS = "åäö";

    int numberOfAt = 0;
    int numberOfDots = 0;

    for(int i = 0; i < address.length(); i++)
    {
        if(address[i] == '@')
        {
            ++numberOfAt;
        }
        else if(address[i] == '.')
        {
            ++numberOfDots;
        }
        for(int j = 0; j < ILLEGAL_CHARS.length(); j++)
        {
            if(address[i] == ILLEGAL_CHARS[j])
            {
                return false;
            }
        }
    }

    if(numberOfAt == 1 && numberOfDots == 1 && address[0] != '.'  && address[address.length() - 1] != '.' && address[0] != '@'  && address[address.length() - 1] != '@')
    {
        return true;
    }
    return false;
}

void MemberModel::setFullName(const QString &name)
{
    QStringList names = name.split(" ");

    if(names.length() == 0)
    {
        firstname = "";
        lastname = "";
    }
    if(names.length() == 1)
    {
        firstname = names[0];
        lastname = "";
    }
    else if(names.length() == 2)
    {
        firstname = names[0];
        lastname = names[1];
    }
    else
    {
        firstname = names[0];
        lastname = "";

        for(int index = 1; index < names.length(); index++)
        {
            lastname += names[index];
            if(index != names.length() - 1)
            {
                lastname += " ";
            }
        }
    }
}

void MemberModel::setBirthdate(const QString &date)
{
    birthdate = date.mid(0, 10);
}

void MemberModel::setBiologicalSex(const QString &sex)
{    
    biologicalSex = sex;
}

void MemberModel::setPhoneNumber(const QString &number)
{    
    phoneNumber = number;
}

void MemberModel::setEmailAddress(const QString &address)
{
    emailAddress = address;
}

void MemberModel::setStreetAddress(const QString &address)
{
    streetAddress = address;
}

void MemberModel::setCity(const QString &pCity)
{
    city = pCity;
}

QString MemberModel::getBiologicalSex() const
{
    if(biologicalSex == "Male")
    {
        return "Man";
    }
    if(biologicalSex == "Female")
    {
        return "Kvinna";
    }

    return biologicalSex;
}

void MemberModel::validate() const
{
    const QString FULL_NAME = getFullName();
    const QStringList NAMES = FULL_NAME.split(" ");

    if(!checkName(firstname) || !checkName(lastname) || firstname.length() < 2 || lastname.length() < 2 || !(NAMES.length() == 2 || NAMES.length() == 3))
    {
        throw std::invalid_argument("Felaktigt angivet namn.");
    }

    if(!QDate::fromString(birthdate, "yyyy-MM-dd").isValid())
    {
        throw std::invalid_argument("Felaktigt angiven födelsedata.");
    }

    if(!(biologicalSex == "Male" || biologicalSex == "Female"))
    {
        throw std::invalid_argument("Du måste ange biologiskt kön.");
    }

    if(1 < zipCode && zipCode < 9999)
    {
        throw std::invalid_argument("Felaktigt angivet postnummer.");
    }

    if(!checkPhoneNumber(phoneNumber))
    {
        throw std::invalid_argument("Felaktigt angivet telefonnummer.");
    }
    if(!checkName(city) || (city.length() != 0 && city.length() < 2))
    {
        throw std::invalid_argument("Felaktigt angiven postadress.");
    }

    if(!checkEmailAddress(emailAddress))
    {
        throw std::invalid_argument("Felaktigt angiven e-postadress.");
    }
}

void MemberModel::save(const bool &createNew)
{        
    MemberModel *model = MemberModel::find(this);
    // Medlemmen finns ej i databasen.
    if(model == nullptr && createNew)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO members(firstname, lastname, birthdate, biological_sex) values(?, ?, ?, ?)");
        query.addBindValue(firstname);
        query.addBindValue(lastname);
        query.addBindValue(birthdate);
        query.addBindValue(biologicalSex);
        if(!query.exec())
        {
            throw std::runtime_error(query.lastError().text().toStdString());
        }
        query.clear();
        if(!query.exec("SELECT LAST_INSERT_ID();"))
        {
            throw std::runtime_error("Databasfel");
        }

        if(!query.next())
        {
            throw std::runtime_error("Databasfel");
        }
        const unsigned int MEMBER_ID = query.value(0).toUInt();

        // E-post
        query.clear();
        query.prepare("INSERT INTO member_email_data(member_id, email_address) values(?, ?)");
        query.addBindValue(MEMBER_ID);
        query.addBindValue(emailAddress);
        if(!query.exec())
        {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        // Telefon
        query.clear();
        query.prepare("INSERT INTO member_phone_data(member_id, phone_number) values(?, ?)");
        query.addBindValue(MEMBER_ID);
        query.addBindValue(phoneNumber);
        if(!query.exec())
        {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        // Boende
        query.clear();
        query.prepare("INSERT INTO member_living_data(member_id, street_adress, zip_code, city) values(?, ?, ?, ?)");
        query.addBindValue(MEMBER_ID);
        query.addBindValue(streetAddress);
        query.addBindValue(zipCode);
        query.addBindValue(city);
        if(!query.exec())
        {
            throw std::runtime_error(query.lastError().text().toStdString());
        }
    }
    else
    {
        std::cout << "Update" << std::endl;
        std::vector<QString> sql;


        sql.push_back("UPDATE members SET id=" + QString::number(id) + ", firstname='" + firstname + "',lastname='"
                + lastname + "',birthdate='" + birthdate + "', biological_sex='" + biologicalSex + "' where id=" + QString::number(id));
        sql.push_back("UPDATE member_email_data SET email_address='" + emailAddress + "' where member_id=" + QString::number(id));
        sql.push_back("UPDATE member_phone_data SET phone_number='" + phoneNumber + "' where member_id=" + QString::number(id));
        sql.push_back("UPDATE member_living_data SET street_adress='" + streetAddress + "',zip_code=" + QString::number(zipCode) + ",city='" + city + "' where member_id=" + QString::number(id));

        for(QString &sqlStatement : sql)
        {
            QSqlQuery query;
            if(!query.exec(sqlStatement))
            {
                throw std::runtime_error(query.lastError().text().toStdString());
            }
        }
    }
}

void MemberModel::remove()
{
    const QString SQL = "DELETE from members where id=" + QString::number(id);

    QSqlQuery query;
    if(!query.exec(SQL))
    {
        throw std::runtime_error(query.lastError().text().toStdString());
    }
}

bool MemberModel::operator==(const MemberModel &model) const
{
    if(id == model.getId() || phoneNumber == model.getPhoneNumber() || emailAddress == model.getEmailAddress())
    {
        return true;
    }

    return false;
}

bool MemberModel::operator<(const MemberModel &model) const
{
    if(lastname < model.lastname)
    {
        return true;
    }

    if(lastname == model.lastname && firstname < model.firstname)
    {
        return true;
    }

    if(lastname == model.lastname && firstname == model.firstname && birthdate < model.birthdate)
    {
        return true;
    }

    return id < model.id;
}



MemberModel* MemberModel::find(MemberModel *model)
{
    std::set<MemberModel*>::const_iterator citerator;

    for(citerator = MemberModel::cbegin(); citerator != MemberModel::cend(); ++citerator)
    {
        if(**citerator == *model)
        {
            return *citerator;
        }
    }

    return nullptr;
}

std::ostream& operator<<(std::ostream &os, const MemberModel &model)
{
    os << "Id: " << model.getId() << std::endl
       << "Namn: " << model.getFullName().toStdString() << std::endl;

    return os;
}
