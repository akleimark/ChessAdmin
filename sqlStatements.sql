# Drop

#DROP TABLE member_email_data

#DROP TABLE member_phone_data

#DROP TABLE member_living_data

#DROP TABLE member_fees

#DROP TABLE members

# Creation
CREATE TABLE IF NOT EXISTS    members(
        id              INT             PRIMARY KEY     AUTO_INCREMENT
    ,   firstname       VARCHAR(1024)   NOT NULL
    ,   lastname        VARCHAR(1024)   NOT NULL
    ,   birthdate       DATETIME        NOT NULL
    ,   biological_sex  VARCHAR(8)      NOT NULL
)Engine=innoDB

CREATE  TABLE  IF NOT EXISTS   member_living_data(
        member_id       INTEGER         PRIMARY KEY
    ,   street_adress   VARCHAR(1024)   NOT NULL
    ,   zip_code        INTEGER         NOT NULL
    ,   city            VARCHAR(1024)   NOT NULL
)Engine=innoDB

CREATE  TABLE  IF NOT EXISTS  member_phone_data(
        member_id       INTEGER         PRIMARY KEY
    ,   phone_number    VARCHAR(1024)   NOT NULL
)Engine=innoDB

CREATE  TABLE  IF NOT EXISTS  member_email_data(
        member_id       INTEGER        PRIMARY KEY
    ,   email_address   VARCHAR(1024)   NOT NULL
)Engine=innoDB

CREATE  TABLE  IF NOT EXISTS  member_fees(
        member_id       INTEGER        PRIMARY KEY
    ,   status          INT            NOT NULL DEFAULT 0
)Engine=innoDB

CREATE TABLE IF NOT EXISTS settings (
        id              VARCHAR(1024) PRIMARY KEY
    ,   setting_data    VARCHAR(1024) NOT NULL
)Engine=innoDB


# Foreign keys

#ALTER TABLE member_living_data ADD FOREIGN KEY (member_id) REFERENCES members(id) ON DELETE CASCADE ON UPDATE CASCADE

#ALTER TABLE member_phone_data ADD FOREIGN KEY(member_id) REFERENCES members(id) ON DELETE CASCADE ON UPDATE CASCADE

#ALTER TABLE member_email_data ADD FOREIGN KEY(member_id) REFERENCES members(id) ON DELETE CASCADE ON UPDATE CASCADE

#ALTER TABLE member_fees ADD FOREIGN KEY(member_id) REFERENCES members(id) ON DELETE CASCADE ON UPDATE CASCADE

