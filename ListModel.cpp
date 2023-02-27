#include "ListModel.h"
#include "MemberModel.h"
#include <QSqlQuery>
#include <QVariant>
#include <iostream>


template <>
void ListModel<MemberModel>::getAll()
{
    container.clear();
    const QString SQL = "SELECT "
                        "id, firstname, lastname, birthdate, biological_sex, street_adress, zip_code, city, phone_number, email_address "
                        "FROM members LEFT JOIN member_living_data ON members.id = member_living_data.member_id LEFT JOIN member_phone_data "
                        "ON members.id = member_phone_data.member_id LEFT JOIN member_email_data ON members.id = member_email_data.member_id";
    QSqlQuery query;
    query.exec(SQL);

    while(query.next())
    {
        MemberModel memberModel;
        memberModel.setId(query.value(0).toUInt());
        memberModel.setFirstname(query.value(1).toString());
        memberModel.setLastname(query.value(2).toString());
        memberModel.setBirthdate(query.value(3).toString());
        memberModel.setBiologicalSex(query.value(4).toString());
        memberModel.setStreetAddress(query.value(5).toString());
        memberModel.setZipCode(query.value(6).toUInt());
        memberModel.setCity(query.value(7).toString());
        memberModel.setPhoneNumber(query.value(8).toString());
        memberModel.setEmailAddress(query.value(9).toString());
        container.insert(memberModel);
    }

}

