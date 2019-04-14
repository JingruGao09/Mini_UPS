CREATE TABLE WORLD(
WORLD_ID INT PRIMARY KEY NOT NULL,
STATUS VARCHAR(10) NOT NULL DEFAULT 'OPEN'
);

CREATE TABLE PACKAGE(
PACKAGE_ID INT PRIMARY KEY NOT NULL,
USER_ID INT NOT NULL REFERENCES UPS_PROFILE("user_id"),
WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),
TRUCK_ID INT NOT NULL REFERENCES TRUCK(TRUCK_ID),
STATUS VARCHAR(20) NOT NULL DEFAULT 'UNPACKED',
X INT NOT NULL,
Y INT NOT NULL
);


CREATE TABLE TRUCK(
TRUCK_ID INT PRIMARY KEY NOT NULL,
X INT NOT NULL,
Y INT NOT NULL,
STATUS VARCHAR(20) NOT NULL DEFAULT 'IDLE'
);


CREATE TABLE SHIPMENT(
SHIP_ID SERIAL PRIMARY KEY NOT NULL,
PACKAGE_ID INT NOT NULL REFERENCES PACKAGE(PACKAGE_ID),
STATUS VARCHAR(50) NOT NULL DEFAULT 'CREATED'
);

