DROP TYPE CURSUS_TY;
DROP TYPE ETABLISSEMENT_TY;
DROP TYPE ETUDIANT_TY;
DROP TYPE ADRESS_TY;

CREATE OR REPLACE type ADRESS_TY as object(no_rue NUMBER(3), nom_rue VARCHAR(25), code_postal NUMBER(5), ville VARCHAR(25));

CREATE OR REPLACE type ETUDIANT_TY as object(id NUMBER(3), nom VARCHAR(25), prenoms VARCHAR(25), date_naiss DATE, no_secu NUMBER(5),adresse ADRESS_TY);

CREATE OR REPLACE type ETABLISSEMENT_TY as object(id NUMBER(5), nom VARCHAR(25), adresse ADRESS_TY);

CREATE OR REPLACE type CURSUS_TY as object(id NUMBER(5), intitule VARCHAR(25),niveau VARCHAR(2));




CREATE TABLE Cursus_tab (Cursus CURSUS_TY);
CREATE TABLE Gestion_etudiants (etudiant ETUDIANT_TY, id_etablissement NUMBER(5), id_cursus NUMBER(5));

CREATE TABLE Gestion_etablissement  (ETABLISSEMENT_, id_etablissement NUMBER(5), id_cursus NUMBER(5));


INSERT INTO Cursus_Tab values(CURSUS_TY(1,'ALMA','M1'));
INSERT INTO Cursus_Tab values(CURSUS_TY(2,'ORO','M1'));

INSERT INTO Gestion_etudiants values(
       ETUDIANT_TY(1,'RINCE','RAMIR',01-JUN-90,19054572,
       ADRESS_TY(1,'rue de Marie',44000,NANTES)
       );

/
