#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include "Database.h"
#include "MVC.h"
#include <QMap>
#include <QDate>
#include "Misc.h"

class MemberModel : public Model, public DatabaseInterface, public Validate
{
    public:
        MemberModel();
        virtual ~MemberModel();
        //MemberModel(const MemberModel &model);
        void setId(const unsigned int &p_id) { id = p_id; }
        unsigned int getId() const { return id; }
        void setFirstname(const QString &name) { firstname = name; }
        QString getFirstname() const { return firstname; }
        void setLastname(const QString &name) { lastname = name; }
        QString getLastname() const { return lastname; }
        void setFullName(const QString &name);
        QString getFullName() const { return firstname + " " + lastname; }
        void setBirthdate(const QString &date);
        QString getBirthdate() const { return birthdate; }
        void setBiologicalSex(const QString &sex);
        QString getBiologicalSex() const;
        QString getStreetAddress() const { return streetAddress; }
        void setStreetAddress(const QString &number);
        unsigned int getZipCode() const { return zipCode; }
        void setZipCode(const unsigned int &zip) { zipCode = zip; }
        QString getCity() const { return city; }
        void setCity(const QString &pCity);
        QString getPhoneNumber() const { return phoneNumber; }
        void setPhoneNumber(const QString &number);
        QString getEmailAddress() const { return emailAddress; }
        void setEmailAddress(const QString &address);
        bool isMemberFeePayed() const { return payedMemberFee; }
        void setMemberFeeStatus(const bool &status) { payedMemberFee = status; }
        virtual void save(const bool &createNew);
        virtual void remove();
        static MemberModel* find(MemberModel *model);
        static std::set<MemberModel*>::const_iterator cbegin() { return container.cbegin(); }
        static std::set<MemberModel*>::const_iterator cend() { return container.cend(); }
        bool operator==(const MemberModel &model) const;
        bool operator<(const MemberModel &model) const;        
        virtual void validate() const;

    private:
        unsigned int id;
        QString firstname;
        QString lastname;
        QString birthdate;
        QString biologicalSex;
        QString streetAddress;
        unsigned int zipCode;
        QString city;
        QString phoneNumber;
        QString emailAddress;
        bool payedMemberFee;


        static std::set<MemberModel*> container;
        bool checkName(const QString &name) const;
        bool checkNumber(const QString &number) const;
        bool checkPhoneNumber(const QString &number) const;
        bool checkEmailAddress(const QString &address) const;
};

std::ostream& operator<<(std::ostream &os, const MemberModel &model);
//bool operator<(const MemberModel* m1, const MemberModel* m2);

#endif // MEMBERMODEL_H
