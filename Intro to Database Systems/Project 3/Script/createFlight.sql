-- createFlight.sql
drop table if exists Flight;
CREATE TABLE `Flight` (
  `flightId`        char(12)    NOT NULL,
  `flightNm`        char(5)     NOT NULL,
  `airline`         varchar(20) DEFAULT NULL,
  `orig`            char(3)     NOT NULL,
  `dest`            char(3)     NOT NULL,
  `schedDt`         date        NOT NULL,
  `depTm`           time        DEFAULT NULL,
  `maxSeats`        int(4)      DEFAULT 0,
  `numSeatsSold`    int(4)      DEFAULT 0,
  PRIMARY KEY (`flightId`)
) ;