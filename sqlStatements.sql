# Drop

DROP TABLE member_email_data

DROP TABLE member_phone_data

DROP TABLE member_living_data

DROP TABLE members

# Creation
CREATE TABLE    members(
        id              INT             PRIMARY KEY     AUTO_INCREMENT
    ,   firstname       VARCHAR(1024)   NOT NULL
    ,   lastname        VARCHAR(1024)   NOT NULL
    ,   birthdate       DATETIME        NOT NULL
    ,   biological_sex  VARCHAR(8)      NOT NULL
)Engine=innoDB

CREATE  TABLE   member_living_data(
        member_id       INTEGER         PRIMARY KEY
    ,   street_adress   VARCHAR(1024)   NOT NULL
    ,   zip_code        INTEGER         NOT NULL
    ,   city            VARCHAR(1024)   NOT NULL
)Engine=innoDB

CREATE  TABLE   member_phone_data(
        member_id       INTEGER         PRIMARY KEY
    ,   phone_number    VARCHAR(1024)   NOT NULL
)Engine=innoDB

CREATE  TABLE   member_email_data(
        member_id       INTEGER        PRIMARY KEY
    ,   email_address   VARCHAR(1024)   NOT NULL
)Engine=innoDB


# Foreign keys





