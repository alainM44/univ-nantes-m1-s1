DROP TABLE Dim_Date CASCADE CONSTRAINT;
DROP TABLE Dim_Trajet  CASCADE CONSTRAINT;
DROP TABLE Dim_Ligne CASCADE CONSTRAINT;
DROP TABLE Dim_Personne CASCADE CONSTRAINT;
DROP TABLE Fait_Station CASCADE CONSTRAINT;

/* afficher les tables select * from tab; */

CREATE TABLE Dim_Date 
       (Clef_Date integer   NOT NULL PRIMARY KEY,
       Annee  integer,
       Mois integer check (Mois < 13 and Mois >0 ),
       Jour integer check (Jour < 31 and Jour >0 ),
       Periode_horaire integer    check (Periode_horaire < 7 and Periode_Horaire >0 ) -- Tranche de 4h : ex 1 -> 0.. 4 -> 
);
CREATE TABLE Dim_Trajet 
       (Clef_Trajet integer  NOT NULL PRIMARY KEY,
       P_depart VARCHAR(30), 
       P_arrivee VARCHAR(30),
       Longueur integer,
       Duree integer
);

CREATE TABLE Dim_Ligne(
       Clef_Ligne integer  NOT NULL PRIMARY KEY,
       Numero integer,
       Type_ligne   VARCHAR(30),
       Depart  VARCHAR(60),
       Terminus  VARCHAR(60)
);
CREATE TABLE Dim_Personne(
       Clef_Personne integer  NOT NULL PRIMARY KEY,
       Nom  VARCHAR(30),
       Prenom  VARCHAR(30),
       Age integer,
       Sexe Char(1),
       Mode_payement VARCHAR(30),
       Situation_familliale VARCHAR(30)
);

CREATE TABLE Fait_Station(
       Clef_Date integer NOT NULL REFERENCES Dim_Date (Clef_Date),
       Clef_Trajet integer NOT NULL REFERENCES Dim_Trajet (Clef_Trajet),
       Clef_Ligne integer     NOT NULL  REFERENCES Dim_Ligne (Clef_Ligne),
       Clef_Personne integer    NOT NULL REFERENCES Dim_Personne (Clef_Personne),
       Station VARCHAR(30),
       CONSTRAINT CP_Station PRIMARY KEY (Clef_Date,Clef_Trajet,Clef_Ligne,Clef_Personne,Station)
);

--INSERTIONS DE TUPLES
-- afficher de date SELECT * from Dim_Date;I
INSERT INTO Dim_Date  VALUES (1,2005,2,12,1);
INSERT INTO Dim_Date  VALUES (2,2007,4,25,2);
INSERT INTO Dim_Date  VALUES (3,2010,6,25,3);
INSERT INTO Dim_Date  VALUES (4,2010,7,2,1);
INSERT INTO Dim_Date  VALUES (5,2011,3,8,2);
INSERT INTO Dim_Date  VALUES (6,2011,1,7,3);
INSERT INTO Dim_Date  VALUES (7,2011,9,25,4);
INSERT INTO Dim_Date  VALUES (8,2011,11,25,5);
INSERT INTO Dim_Date  VALUES (9,2012,11,25,6);
INSERT INTO Dim_Date  VALUES (10,2012,11,25,6);
INSERT INTO Dim_Date  VALUES (11,2005,11,12,1);
INSERT INTO Dim_Date  VALUES (12,2007,11,25,2);
INSERT INTO Dim_Date  VALUES (13,2010,11,25,3);
INSERT INTO Dim_Date  VALUES (14,2010,11,25,1);
INSERT INTO Dim_Date  VALUES (15,2011,11,25,1);
INSERT INTO Dim_Date  VALUES (16,2011,11,25,2);
INSERT INTO Dim_Date  VALUES (17,2011,11,25,3);
INSERT INTO Dim_Date  VALUES (18,2011,11,25,4);
INSERT INTO Dim_Date  VALUES (19,2012,11,25,5);
INSERT INTO Dim_Date  VALUES (20,2012,11,25,6);



-- INSERT INTO Dim_Date  VALUES (10,2012,11,25,6); ne marche pas contrainte violée


INSERT INTO Dim_Trajet  VALUES (1,'St Mihiel','Commerce',5,20);
INSERT INTO Dim_Trajet  VALUES (2,'Commerce','Mediatheque',6,3);
INSERT INTO Dim_Trajet  VALUES (3,'Mediatheque','Commerce',6,3);
INSERT INTO Dim_Trajet  VALUES (4,'Joliverie','Tripode',10,4);
INSERT INTO Dim_Trajet  VALUES (5,'50 otages','Commerce',4,2);
INSERT INTO Dim_Trajet  VALUES (6,'Place du cirque','Commerce',2,1);
INSERT INTO Dim_Trajet  VALUES (7,'Faculté','Commerce',20,7);
INSERT INTO Dim_Trajet  VALUES (7,'Petit-Port','Commerce',17,6);



INSERT INTO Dim_Ligne  VALUES (1,2,'Tram','Orvault','PontRousseau');
INSERT INTO Dim_Ligne  VALUES (2,2,'Tram','PontRousseau','Orvault');
INSERT INTO Dim_Ligne  VALUES (3,1,'Tram','Beaugoire','François-Mitterand');
INSERT INTO Dim_Ligne  VALUES (4,1,'Tram','François-Mitterand','Beaugoire');
INSERT INTO Dim_Ligne  VALUES (5,4,'Tram','Porte de Vertou','Fosch Cathedrale');
INSERT INTO Dim_Ligne  VALUES (6,11,'Bus','Tertre','Jules Verne');


INSERT INTO Dim_Personne VALUES (1,'Rince','Romain',22,'M','Annuel','Celibataire');
INSERT INTO Dim_Personne VALUES (2,'Robert','Dupont',48,'M','Mensuel','Marié');
INSERT INTO Dim_Personne VALUES (3,'Margarette','de Cherade de Mombron',56,'F','Hebdomadaire','Mariée');

INSERT INTO Fait_Station VALUES (1,4,5,3,'Tripode'); 
INSERT INTO Fait_Station VALUES (20,5,2,2,'Place du cirque');
INSERT INTO Fait_Station VALUES (19,3,4,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,3,4,1,'Commerce'); 










--CREATE TABLE Fait_Station(
  --     Clef_Date integer NOT NULL REFERENCES Dim_Date (Clef_Date),
    --   Clef_Trajet integer NOT NULL REFERENCES Dim_Trajet (Clef_Trajet),
      -- Clef_Ligne integer     NOT NULL  REFERENCES Dim_Ligne (Clef_Ligne),
      -- Clef_Personne integer    NOT NULL REFERENCES Dim_Personne (Clef_Personne),
      -- Station VARCHAR(30),
      -- CONSTRAINT CP_Station PRIMARY KEY (Clef_Date,Clef_Trajet,Clef_Ligne,Clef_Personne)
--);
