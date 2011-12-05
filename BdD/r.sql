
DROP TABLE Etudiant_tab;
DROP TABLE Personnel_tab;
DROP TABLE Cursus_tab;
DROP TABLE GroupeTD_tab;
DROP TABLE GroupeTP_tab;
DROP TABLE UE_tab;


DROP TYPE Etudiant_REF_NT FORCE;
DROP TYPE Cursus_TY FORCE;
DROP TYPE UE_TY FORCE;
DROP TYPE Etudiant_TY FORCE;
DROP TYPE Titulaire_TY FORCE;
DROP TYPE Vacataire_TY FORCE;
DROP TYPE Personnel_REF_VA FORCE;
DROP TYPE Personnel_TY FORCE;
DROP TYPE GroupeTD_TY FORCE;
DROP TYPE GroupeTP_TY FORCE;
DROP TYPE Cursus_REF_NT FORCE;
DROP TYPE GroupeTD_REF_NT FORCE;
DROP TYPE GroupeTP_REF_NT FORCE;
-- Mémo pour le login
-- source /etc/profile
-- sqlplus admi9@cienetdb 
-- afficher les tables select * from tab; 



-- cascade constraints;

--1TD
--11TP =2/3TD
--1CM=1.5TD



CREATE OR REPLACE TYPE Personnel_TY as object (nom VARCHAR(25),prenom VARCHAR(25),equipe VARCHAR(25),  
member function volume_horaire_EquiTD return NUMBER) not final;
/

CREATE OR REPLACE TYPE BODY Personnel_TY as 
member function volume_horaire_EquiTD return NUMBER is 
      begin
-- 1TP = 2/3 TD, et 1CM = 1,5 TD.
	RETURN 1;
	end;
end;	
/
CREATE OR REPLACE type Personnel_REF_VA as varray(2) of REF Personnel_TY;--pour les TP
/

CREATE OR REPLACE TYPE UE_TY as object (intitule VARCHAR(25),id_code VARCHAR(25),nb_seance_CM NUMBER ,nb_seance_TD NUMBER,nb_seance_TP NUMBER, responsable_CM ref Personnel_TY);
/

CREATE OR REPLACE TYPE Titulaire_TY under Personnel_TY ();
/

CREATE OR REPLACE TYPE Vacataire_TY under Personnel_TY ();
/

CREATE OR REPLACE TYPE UE_REF_NT as table of REF UE_TY;
/

CREATE OR REPLACE TYPE GroupeTD_TY as object (id NUMBER, placelimite NUMBER);
/

CREATE OR REPLACE TYPE GroupeTD_REF_NT as table of REF GroupeTD_TY;
/

CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),id_code VARCHAR(25), niveau VARCHAR(25),responsable REF Personnel_TY, liste_tds GroupeTD_REF_NT,
member function volume_horaire return NUMBER)
/

CREATE OR REPLACE TYPE BODY Cursus_TY as 
member function volume_horaire return NUMBER is 
      begin
	RETURN 1;
	end;
end;	
/


CREATE OR REPLACE TYPE Etudiant_TY as object (nom VARCHAR(25),prenom VARCHAR(25), num_etu VARCHAR(25));
/

CREATE TYPE Etudiant_REF_NT  AS TABLE OF REF Etudiant_TY;
/


CREATE OR REPLACE TYPE GroupeTP_TY as object (id NUMBER,responsables Personnel_REF_VA, liste_etu Etudiant_REF_TAB);
/

CREATE OR REPLACE type Groupe_TP_REF_VA as varray(2) of REF GroupeTP_TY;--pour les TP
/

CREATE OR REPLACE TYPE GroupeTP_REF_NT as table of REF GroupeTP_TY ;
/

CREATE OR REPLACE TYPE Cursus_REF_NT as table of REF Cursus_TY;
/
ALTER TYPE Etudiant_TY ADD ATTRIBUTE  (liste_cursus Cursus_REF_NT ) CASCADE; 
--On ajoute la table la référence d'une UE au type Personnel_TY peut etre nulle
ALTER TYPE Personnel_TY ADD ATTRIBUTE  ( cursus REF Cursus_TY) CASCADE;
--On ajoute la table de référence vers les ligne de ue
ALTER TYPE Personnel_TY ADD ATTRIBUTE  ( liste_ue UE_REF_NT) CASCADE;
--On ajoute la table de référence vers les ligne de la table groupeTD
ALTER TYPE Personnel_TY ADD ATTRIBUTE  ( liste_tds  GroupeTD_REF_NT) CASCADE; 
--On ajoute la table de référence vers les ligne de la table groupeTP
--ALTER TYPE Personnel_TY ADD ATTRIBUTE  ( liste_tps  GroupeTP_REF_NT) CASCADE; -- a vérifier


ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (etudiants Etudiant_REF_NT) CASCADE  ;
ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (responsable REF Personnel_TY) CASCADE ;
ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (tps  Groupe_TP_REF_VA ) CASCADE ;
ALTER TYPE GroupeTP_TY ADD ATTRIBUTE (etudiants Etudiant_REF_NT) CASCADE  ;
ALTER TYPE Cursus_TY ADD ATTRIBUTE ( etudiants Etudiant_REF_NT) CASCADE  ;
ALTER TYPE Cursus_TY ADD ATTRIBUTE ( liste_ue UE_REF_NT) CASCADE  ;





CREATE TABLE Etudiant_tab of Etudiant_TY
NESTED TABLE liste_cursus STORE AS Cursus_REF_NT_TAB;

CREATE TABLE Personnel_tab of Personnel_TY 
NESTED TABLE liste_ue STORE AS UE_REF_NT_TAB 
NESTED TABLE liste_tds STORE AS GroupeTD_REF_NT_TAB
--NESTED TABLE liste_tps STORE AS GroupeTP_REF_NT_TAB
;
 
CREATE TABLE Cursus_tab of Cursus_TY
NESTED TABLE etudiants STORE AS Etudiant_REF_NT_TAB
NESTED TABLE liste_ue STORE AS CU_UE_NT_TAB
NESTED TABLE liste_tds STORE AS TD_NT_TAB;

CREATE TABLE GroupeTD_tab of GroupeTD_TY
NESTED TABLE etudiants STORE AS Etudiant2_REF_NT_TAB
;

CREATE TABLE GroupeTP_tab of GroupeTP_TY NESTED TABLE etudiants STORE AS Etudiant3_REF_NT_TAB
;




CREATE TABLE TYPE UE_tab of UE_TY

-

--CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),id_code VARCHAR(25), niveau VARCHAR(25),responsable REF Personnel_TY,

--INSERT INTO Personnel_tab values('MrALMA','Chri','LINA');
--INSERT INTO Etudiant_tab values (Etudiant_TY('RINCE','Ramir',99453),Cursus_NT(Cursus_TY('ALMA','1','MASTER',(select ref (p)FROM Personnel_tab p WHERE p.nom='MrALMA') )));


INSERT INTO Etudiant_tab values (Etudiant_TY('RINCE','Romain',97893,null));
INSERT INTO Etudiant_tab values (Etudiant_TY('LINUX','blague',92543,null));
INSERT INTO Etudiant_tab values (Etudiant_TY('LUTIN','barbu',99543,null));
INSERT INTO Etudiant_tab values (Etudiant_TY('DELASOUL','eric',99783,null));
INSERT INTO Etudiant_tab values (Etudiant_TY('LINUX','heu',97853,null));
