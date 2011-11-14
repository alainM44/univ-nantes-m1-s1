DROP TABLE Gestion_etablissement cascade constraints; 

DROP TABLE Gestion_etudiants cascade constraints;

DROP TABLE Cursus_tab cascade constraints; 

DROP TABLE PROMO cascade constraints; 

DROP TYPE CURSUS_TY FORCE;

DROP TYPE ETABLISSEMENT_TY FORCE;

DROP TYPE ETUDIANT_TY FORCE;

DROP TYPE ADRESS_TY FORCE;

DROP TYPE PRENOMS_VA FORCE; 

SET LINESIZE 200

--a
CREATE OR REPLACE type PRENOMS_VA as varray(5) of VARCHAR(25);
/
CREATE OR REPLACE type ADRESS_TY as object(no_rue NUMBER(3), nom_rue VARCHAR(25), code_postal NUMBER(5), ville VARCHAR(25));
/
CREATE OR REPLACE type ETUDIANT_TY as object(id NUMBER(3), nom VARCHAR(25), prenoms PRENOMS_VA, no_secu NUMBER(5),adresse ADRESS_TY,
member function get_first_prenom(prenom VARCHAR) return VARCHAR); -- COMMENT FAIRE METHODES SANS PARAM
/
CREATE OR REPLACE TYPE BODY ETUDIANT_TY as 
member function get_first_prenom(prenom VARCHAR) return VARCHAR is 
       begin
	RETURN self.prenoms(1);
	end;
end;	
/
CREATE OR REPLACE type ETABLISSEMENT_TY as object(id NUMBER(5), nom VARCHAR(25), adresse ADRESS_TY);
/
CREATE OR REPLACE type CURSUS_TY as object(id NUMBER(5), intitule VARCHAR(25),niveau VARCHAR(2));
/


--b

CREATE TABLE Cursus_tab of CURSUS_TY;

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

--On insère 2 fois ? 
INSERT INTO Gestion_etablissement values(1,
					 ETUDIANT_NT(
					 ETUDIANT_TY(1,'RINCE',PRENOMS_VA('RAMIR','ROMAIN'),19054,ADRESS_TY(2,'ruea',7892,'nantes')),
					 ETUDIANT_TY(2,'RINCE2',PRENOMS_VA('RAMIR2'),19054,ADRESS_TY(1,'rue de Marie',44000,'NANTES'))),
					 1 ) ;

INSERT INTO Gestion_etablissement values(2,
					 ETUDIANT_NT(
					 ETUDIANT_TY(1,'MAR',PRENOMS_VA('AL','GILLES'),19054,ADRESS_TY(2,'ruea',7892,'nantes')),
					 ETUDIANT_TY(2,'LUC',PRENOMS_VA('Josephe','Stan'),19054,ADRESS_TY(1,'rue de Marie',44000,'NANTES')),
					 ETUDIANT_TY(2,'BOB',PRENOMS_VA('Josephe','Stan'),19054,ADRESS_TY(1,'rue de Marie',44000,'NANTES'))),
					 3 ) ;


--d -- Etudiant du 1er etablissement et leur 1er nom avec un appel de fonction
SELECT g.id_etablissement, E.nom, E.get_first_prenom('toto')
FROM Gestion_etablissement g ,TABLE(g.liste_etu) E
WHERE g.id_etablissement=2;
--d -- Etablissements avec plus de 3 etudiants  autre methode vu en TD
SELECT g.id_etablissement,count(E.nom) 
FROM Gestion_etablissement g ,TABLE(g.liste_etu) E
GROUP BY g.id_etablissement
HAVING count(E.nom)<3;


--REF
CREATE TABLE PROMO
(Promo_name VARCHAR(25),
promo_cursus REF CURSUS_TY);

INSERT INTO PROMO
select '2011/2012',REF(c)
FROM Cursus_tab c
WHERE id=1;
INSERT INTO PROMO
select '2010/2011',REF(c)
FROM Cursus_tab c
WHERE id=2;



SELECT DEREF (P.promo_cursus) as deref
FROM PROMO P
WHERE Promo_name='2010/2011';

--VALUE MEME AFF QUE DEREF DEBUG
SELECT VALUE(c) as valuee FROM Cursus_tab c
WHERE intitule='ORO';

--WHERE id_etablissement=2;

--REF Vecteur REF
--Table imb| Vecteur REF
--insertion table|vecteur

--heritage