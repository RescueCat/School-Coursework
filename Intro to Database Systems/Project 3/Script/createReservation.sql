-- createReservation.sql
drop table if exists `Reservation`;
CREATE TABLE `Reservation` (
  `custNr`          smallint    NOT NULL,
  `flightId`        char(12)    NOT NULL,
  `reqSeatQty`      smallint(2) DEFAULT NULL,
  PRIMARY KEY (`custNr`,`flightId`)
) ;
