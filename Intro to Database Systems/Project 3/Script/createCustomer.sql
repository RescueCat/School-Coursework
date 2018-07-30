-- createCustomer.sql
drop table if exists Customer;
CREATE TABLE `Customer` (
  `custNr`          smallint    NOT NULL,
  `name`            varchar(30) DEFAULT NULL,
  `preferAirline`   varchar(20) DEFAULT NULL, 
  `birthDt`         date        DEFAULT NULL,
  `gender`          char(1)     DEFAULT 'U',  
  PRIMARY KEY (`custNr`)
) ;
