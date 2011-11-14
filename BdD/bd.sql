DROP TABLE Gestion_etablissement cascade constraints; 

DROP TABLE Gestion_etudiants cascade constraints;

DROP TABLE Cursus_tab cascade constraints; 

DROP TYPE CURSUS_TY FORCE;

DROP TYPE ETABLISSEMENT_TY FORCE;

DROP TYPE ETUDIANT_TY FORCE;

DROP TYPE ADRESS_TY FORCE;

DROP TYPE PRENOMS_VA FORCE; 


--a
CREATE OR REPLACE type PRENOMS_VA as varray(5) of VARCHAR(25);
/
CREATE OR REPLACE type ADRESS_TY as object(no_rue NUMBER(3), nom_rue VARCHAR(25), code_postal NUMBER(5), ville VARCHAR(25));
/
CREATE OR REPLACE type ETUDIANT_TY as object(id NUMBER(3), nom VARCHAR(25), prenoms PRENOMS_VA, no_secu NUMBER(5),adresse ADRESS_TY);
/
CREATE OR REPLACE type ETABLISSEMENT_TY as object(id NUMBER(5), nom VARCHAR(25), adresse ADRESS_TY);
/
CREATE OR REPLACE type CURSUS_TY as object(id NUMBER(5), intitule VARCHAR(25),niveau VARCHAR(2));
/


--b

CREATE TABLE Cursus_tab (Cursus CURSUS_TY);

CREATE TABLE Gestion_etudiants (etudiant ETUDIANT_TY, id_etablissement NUMBER(5), id_cursus NUMBER(5));

CREATE OR REPLACE TYPE Etudiant_NT as table of ETUDIANT_TY;
/

CREATE TABLE Gestion_etablissement  (id_etablissement NUMBER(5), liste_etu ETUDIANT_NT, id_cursus NUMBER) nested table liste_etu store as ETUDIANT_NT_TAB;

INSERT INTO Cursus_Tab values(CURSUS_TY(1,'ALMA','M1'));
/
INSERT INTO Cursus_Tab values(CURSUS_TY(2,'ORO','M1'));
/
INSERT INTO Gestion_etudiants values(
       ETUDIANT_TY(1,'RINCE',PRENOMS_VA('chat', 'blah'),19054,
       ADRESS_TY(1,'rue de Marie',44000,'NANTES')), 1, 1
       );
/
INSERT INTO Gestion_etablissement values(1, ETUDIANT_NT(ETUDIANT_TY(1,'RINCE',PRENOMS_VA('RAMIR'),01-JUN-90,19054,ADRESS_TY(2,'ruea',7892,'nantes'),ETUDIANT_TY(2,'RINCE2',PRENOMS_VA('RAMIR2'),01-JUN-90,19054,ADRESS_TY(1,'rue de Marie',44000,'NANTES')))),1 ) ;
/

--d
SELECT *
FROM Gestion_etablissement g ;

--REF Vecteur REF
--Table imb| Vecteur REF
--insertion table|vecteur
-- creer une methode renvoyant le first d'un VARRAY
--heritage