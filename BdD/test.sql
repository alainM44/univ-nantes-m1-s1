DROP TABLE Dim_Date CASCADE CONSTRAINT;
DROP TABLE Dim_Trajet  CASCADE CONSTRAINT;
DROP TABLE Dim_Ligne CASCADE CONSTRAINT;
DROP TABLE Dim_Personne CASCADE CONSTRAINT;
DROP TABLE Fait_Station CASCADE CONSTRAINT;
/* source /etc/profile
 sqlplus admi9@cienetdb */
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
INSERT INTO Dim_Trajet  VALUES (8,'Petit-Port','Commerce',17,6);
INSERT INTO Dim_Trajet  VALUES (9,'Rene Cassin','Commerce',2,3);
INSERT INTO Dim_Trajet  VALUES (10,'Manufacture','Duchesse-Anne',2,3);
INSERT INTO Dim_Trajet  VALUES (11,'Gare-Maritime','Chantier-Naval',1,2);
INSERT INTO Dim_Trajet  VALUES (12,'Bonne-Garde','Bourdonières',15,8);
INSERT INTO Dim_Trajet  VALUES (13,'Landreau','Moutonnerie',7,10);
INSERT INTO Dim_Trajet  VALUES (14,'Pin sec','Manufacture',9,12);
INSERT INTO Dim_Trajet  VALUES (15,'Egalité','Jamet',6,5);
INSERT INTO Dim_Trajet  VALUES (16,'Rond point de Vannes','Stade SNUC',2,3);
INSERT INTO Dim_Trajet  VALUES (17,'Michelet','Casimir Perrier',1,2);
INSERT INTO Dim_Trajet  VALUES (18,'Lemoine','Tortiere',15,8);
INSERT INTO Dim_Trajet  VALUES (19,'Bd de Doulon','Mitrie',7,10);
INSERT INTO Dim_Trajet  VALUES (20,'Joncours','Solidarité',9,12);
INSERT INTO Dim_Trajet  VALUES (21,'Mairie Chantenay','Cabrol',6,5);
INSERT INTO Dim_Trajet  VALUES (22,'Rond point de Vannes','Stade SNUC',2,3);
INSERT INTO Dim_Trajet  VALUES (23,'Michelet','Solidarité',1,2);
INSERT INTO Dim_Trajet  VALUES (24,'Lemoine','Tortiere',15,8);
INSERT INTO Dim_Trajet  VALUES (25,'Bd de Doulon','Solidarité',7,10);
INSERT INTO Dim_Trajet  VALUES (26,'Joncours','Mairie de Chanteany',9,12);
INSERT INTO Dim_Trajet  VALUES (27,'Mairie Chantenay','Janvraie',6,5);


INSERT INTO Dim_Ligne  VALUES (1,2,'Tram','Orvault','PontRousseau');
INSERT INTO Dim_Ligne  VALUES (2,2,'Tram','PontRousseau','Orvault');
INSERT INTO Dim_Ligne  VALUES (3,1,'Tram','Beaugoire','François-Mitterand');
INSERT INTO Dim_Ligne  VALUES (4,1,'Tram','François-Mitterand','Beaugoire');
INSERT INTO Dim_Ligne  VALUES (5,4,'BusWay','Porte-de-Vertou','Fosch-Cathedrale');
INSERT INTO Dim_Ligne  VALUES (6,4,'BusWay','Fosch-Cathedrale','Porte-de-Vertou');
INSERT INTO Dim_Ligne  VALUES (7,11,'Bus','Tertre','Jules Verne');
INSERT INTO Dim_Ligne  VALUES (8,11,'Bus','Jules Verne','Tertre');
INSERT INTO Dim_Ligne  VALUES (9,70,'Bus','Gare-de-Chantenay','BD-de-Doulon');
INSERT INTO Dim_Ligne  VALUES (10,70,'Bus','BD-de-Doulon','Gare-de-Chantenay');


INSERT INTO Dim_Personne VALUES (1,'Rince','Romain',22,'M','Annuel','Celibataire');
INSERT INTO Dim_Personne VALUES (2,'Robert','Dupont',48,'M','Mensuel','Marié');
INSERT INTO Dim_Personne VALUES (3,'Margarette','de Cherade de Mombron',56,'F','Hebdomadaire','Marié');
INSERT INTO Dim_Personne VALUES (4,'Thom','York',36,'M','Ticket','Marié');
INSERT INTO Dim_Personne VALUES (5,'Johny','Depp',40,'M','Ticket','Marié');
INSERT INTO Dim_Personne VALUES (6,'Michel','Boissineau',60,'M','Annuel','Marié');
INSERT INTO Dim_Personne VALUES (7,'Harry','Potter',20,'M','Mensuel','Celibataire');
INSERT INTO Dim_Personne VALUES (8,'Micheal','Jordan',50,'M','Hebdomadaire','Marié');
INSERT INTO Dim_Personne VALUES (9,'Amadeous','Mozart',60,'M','Ticket','Celibataire');
INSERT INTO Dim_Personne VALUES (10,'Brad','Pitt',47,'M','Mensuel','Marié');



/* 10 trajets de Romain  */

INSERT INTO Fait_Station VALUES (1,1,1,1,'Michelet'); 
INSERT INTO Fait_Station VALUES (2,2,2,1,'Michelet');
INSERT INTO Fait_Station VALUES (3,3,1,1,'Michelet'); 
INSERT INTO Fait_Station VALUES (4,4,2,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (5,5,2,1,'Michelet'); 
INSERT INTO Fait_Station VALUES (6,6,2,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (7,7,1,1,'Michelet');
INSERT INTO Fait_Station VALUES (8,8,1,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (9,9,1,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (10,10,2,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (9,10,1,1,'Commerce'); 


/* 1 trajet  INSERT INTO Dim_Trajet  VALUES (9,'Rene Cassin','Commerce',2,3); */
INSERT INTO Fait_Station VALUES (10,9,1,1,'René Cassin'); 
INSERT INTO Fait_Station VALUES (11,9,2,1,'Faculté');
INSERT INTO Fait_Station VALUES (12,9,1,1,'Michelet'); 
INSERT INTO Fait_Station VALUES (13,9,2,1,'Petit Port'); 
INSERT INTO Fait_Station VALUES (14,9,2,1,'Michelet'); 
INSERT INTO Fait_Station VALUES (15,9,1,1,'50 Otage'); 
INSERT INTO Fait_Station VALUES (16,9,1,1,'Michelet');
INSERT INTO Fait_Station VALUES (17,9,1,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,9,1,1,'Place du cirque'); 
INSERT INTO Fait_Station VALUES (19,9,2,1,'Commerce'); 
INSERT INTO Fait_Station VALUES (20,9,1,1,'petit port'); 




/* même heure 10trajets 10personnes */
INSERT INTO Fait_Station VALUES (18,1,1,1,'50 otages'); 
INSERT INTO Fait_Station VALUES (18,2,2,2,'Place du cirque');
INSERT INTO Fait_Station VALUES (18,3,4,3,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,4,5,4,'Tripode'); 
INSERT INTO Fait_Station VALUES (18,5,1,5,'Place du cirque'); 
INSERT INTO Fait_Station VALUES (18,6,1,6,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,7,1,7,'Place du cirque');
INSERT INTO Fait_Station VALUES (18,8,1,8,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,9,1,10,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,10,1,9,'Commerce'); 

/* 11 Ligne  */
INSERT INTO Fait_Station VALUES (16,1,10,1,'50 otages'); 
INSERT INTO Fait_Station VALUES (17,2,10,2,'Place du cirque');
INSERT INTO Fait_Station VALUES (19,3,10,3,'Commerce'); 
INSERT INTO Fait_Station VALUES (20,4,10,4,'Tripode'); 
INSERT INTO Fait_Station VALUES (18,5,10,5,'Place du cirque'); 
INSERT INTO Fait_Station VALUES (18,6,10,6,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,7,10,7,'Place du cirque');
INSERT INTO Fait_Station VALUES (17,8,10,8,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,9,10,9,'Commerce'); 
INSERT INTO Fait_Station VALUES (18,10,10,10,'Commerce'); 


-- REQUETES

--1 Nombre de stations traversées en 1 journée;

SELECT Station , count(*)
FROM Fait_Station F, Dim_Date DD
WHERE DD.Clef_Date=18 and F.Clef_Date=DD.Clef_Date
GROUP BY Station;