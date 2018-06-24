show databases;

CREATE DATABASE smartDB;

USE smartDB;

CREATE TABLE log (
    id INT(20) AUTO_INCREMENT,
    logType VARCHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE city(
	id INT(20) AUTO_INCREMENT,
    cityName VARCHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE street(
	id INT(20) AUTO_INCREMENT,
    streetName VARCHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE location(
	id INT(20) AUTO_INCREMENT,
    uid INT(20),
    city INT(20)   REFERENCES city(id),
    street INT(20) REFERENCES street(id),
    PRIMARY KEY (id)
);

ALTER TABLE location
	ADD FOREIGN KEY (city) REFERENCES city(id),
    ADD FOREIGN KEY (street) REFERENCES street(id);

CREATE TABLE deviceType
(
	id INT(20) AUTO_INCREMENT,
    deviceType VARCHAR(30) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE devices
(
	id  	INT(20) AUTO_INCREMENT,
	uid 	VARCHAR(30) NOT NULL,
	dType 	INT(20)   REFERENCES deviceType(id),
    room	INT(20)	  NOT NULL,
    floor	INT(20)	  NOT NULL,
    location INT(20)  REFERENCES location(id),
    log		INT(20)	  REFERENCES log(id),
    config	VARCHAR(30) NOT NULL,
    
    PRIMARY KEY (id)
);

ALTER TABLE devices
	ADD FOREIGN KEY (dType) 	REFERENCES deviceType(id),
    ADD FOREIGN KEY (location) 	REFERENCES location(id),
    ADD FOREIGN KEY (log) 		REFERENCES log(id);

CREATE TABLE registrar
(
	
);
