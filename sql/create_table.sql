CREATE TABLE INSEQNUM(
ID BIGINT PRIMARY KEY NOT NULL
);

CREATE TABLE OUTSEQNUM(
ID BIGSERIAL PRIMARY KEY NOT NULL,
MSG VARCHAR(65535) NOT NULL
);

CREATE TABLE WORLD(
WORLD_ID INT PRIMARY KEY NOT NULL,
STATUS VARCHAR(10) NOT NULL DEFAULT 'OPEN'
);

CREATE TABLE TRUCK(
TRUCK_ID INT NOT NULL,
X INT NOT NULL,
Y INT NOT NULL,
WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),
STATUS VARCHAR(20) NOT NULL DEFAULT 'IDLE',
PRIMARY KEY(TRUCK_ID, WORLD_ID)
);


CREATE TABLE PACKAGE(
PACKAGE_ID BIGINT NOT NULL,
WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),
TRUCK_ID INT NOT NULL REFERENCES TRUCK(TRUCK_ID),
STATUS VARCHAR(20) NOT NULL DEFAULT 'CREATED',
X INT NOT NULL,
Y INT NOT NULL,
PRIMARY KEY(PACKAGE_ID, WORLD_ID)
);

 
CREATE TABLE USERPACKAGE(
USER_ID INT NOT NULL REFERENCES UPS_PROFILE("user_id"),
PACKAGE_ID BIGINT NOT NULL
);

CREATE TABLE PRODUCT{
PRODUCT_ID BIGINT NOT NULL,
PACKAGE_ID BIGINT NOT NULL REFERENCES PACKAGE(PACKAGE_ID),
WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),
DESCRIPTION VARCHAR(100) NOT NULL,
COUNT INT NOT NULL,
PRIMARY KEY(PACKAGE_ID, WORLD_ID, PRODUCT_ID)
}

CREATE TABLE SHIPMENT(
SHIP_ID BIGINT NOT NULL,
PACKAGE_ID BIGINT NOT NULL REFERENCES PACKAGE(PACKAGE_ID),
WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),
PRIMARY KEY(SHIP_ID, WORLD_ID)
);

