DROP TABLE Etudiant_tab;
DROP TABLE Cursus_tab;
DROP TABLE GroupeTD_tab;
DROP TABLE GroupeTP_tab;
DROP TABLE UE_tab;
DROP TABLE Vacataire_tab;
DROP TABLE Titulaire_tab;
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
DROP TYPE UE_REF_NT FORCE;

SET LINESIZE 250

-- Mémo pour le login
-- source /etc/profile
-- sqlplus admi9@cienetdb 
-- afficher les tables select * from tab; 



----------------------------------------------------------------------------------------------------------------
------------------------------------------- TYPES--------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
CREATE OR REPLACE TYPE Personnel_TY as object (
       	  nom VARCHAR(25),
	  prenom VARCHAR(25),
	  equipe VARCHAR(25),  
	  member function volume_horaire_EquiTD return NUMBER) 
	  not final;
/

CREATE OR REPLACE type Personnel_REF_VA as varray(2) of REF Personnel_TY;
/
CREATE OR REPLACE TYPE UE_TY as object (
       	  intitule VARCHAR(25),
	  id_code VARCHAR(25),
	  nb_seance_CM NUMBER ,
	  nb_seance_TD NUMBER,
	  nb_seance_TP NUMBER, 
	  responsable_CM ref Personnel_TY);
/


CREATE OR REPLACE TYPE UE_REF_NT as table of REF UE_TY;
/

CREATE OR REPLACE TYPE GroupeTD_TY as object (id NUMBER, 
       	  	       		      	     placelimite NUMBER);
/

CREATE OR REPLACE TYPE GroupeTD_REF_NT as table of REF GroupeTD_TY;
/

CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),
       	  	       		    	   id_code VARCHAR(25), 
					   niveau VARCHAR(25),
					   responsable REF Personnel_TY, 
					   liste_tds GroupeTD_REF_NT,
					   member function volume_horaire return NUMBER);
/
CREATE OR REPLACE TYPE Titulaire_TY UNDER Personnel_TY(
	OVERRIDING member function volume_horaire_EquiTD RETURN NUMBER
);
/
CREATE OR REPLACE TYPE Vacataire_TY UNDER Personnel_TY();
/


CREATE OR REPLACE TYPE Etudiant_TY as object (nom VARCHAR(25),
       	  	       		      	     prenom VARCHAR(25),
					     num_etu VARCHAR(25));
/

CREATE TYPE Etudiant_REF_NT  AS TABLE OF REF Etudiant_TY;
/


CREATE OR REPLACE TYPE GroupeTP_TY as object (id NUMBER,
       	  	       		      	     responsables Personnel_REF_VA,
					     etudiants Etudiant_REF_NT);
/
CREATE OR REPLACE TYPE GroupeTP_REF_NT as table of REF GroupeTP_TY ;
/


CREATE OR REPLACE type Groupe_TP_REF_VA as varray(2) of REF GroupeTP_TY;--pour les TP
/


CREATE OR REPLACE TYPE Cursus_REF_NT as table of REF Cursus_TY;
/

ALTER TYPE Etudiant_TY ADD ATTRIBUTE  (liste_cursus Cursus_REF_NT ) CASCADE; 
--On ajoute la table la référence d'une UE au type Personnel_TY peut etre nulle
ALTER TYPE Personnel_TY ADD ATTRIBUTE  (cursus REF Cursus_TY) CASCADE;
--On ajoute la table de référence vers les ligne de ue
ALTER TYPE Personnel_TY ADD ATTRIBUTE  (liste_ue UE_REF_NT) CASCADE;
--On ajoute la table de référence vers les ligne de la table groupeTD
ALTER TYPE Personnel_TY ADD ATTRIBUTE  (liste_tds  GroupeTD_REF_NT) CASCADE; 
--On ajoute la table de référence vers les ligne de la table groupeTP
ALTER TYPE Personnel_TY ADD ATTRIBUTE  (liste_tps  GroupeTP_REF_NT) CASCADE; 
      	   	
ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (responsable REF Personnel_TY) CASCADE ;
ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (tps  Groupe_TP_REF_VA ) CASCADE ;
ALTER TYPE GroupeTD_TY ADD ATTRIBUTE (etudiants Etudiant_REF_NT) CASCADE;

ALTER TYPE Cursus_TY ADD ATTRIBUTE ( etudiants Etudiant_REF_NT) CASCADE  ;
ALTER TYPE Cursus_TY ADD ATTRIBUTE ( liste_ue UE_REF_NT) CASCADE  ;



----------------------------------------------------------------------------------------------------------------
------------------------------------------- TABLES--------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------

CREATE TABLE Cursus_tab of Cursus_TY(	CONSTRAINT cursus_id_code_pk PRIMARY KEY(id_code))
NESTED TABLE etudiants STORE AS Etudiant_REF_NT_TAB
NESTED TABLE liste_ue STORE AS CU_UE_NT_TAB
NESTED TABLE liste_tds STORE AS TD_NT_TAB
;

 
CREATE TABLE Etudiant_tab of Etudiant_TY(  constraint etudiant_etu_pk PRIMARY KEY(nom))
NESTED TABLE liste_cursus STORE AS Cursus_REF_NT_TAB;

Create table Titulaire_tab of Titulaire_TY( constraint  titulaire_id_pk PRIMARY KEY(nom))
NESTED TABLE liste_ue STORE AS UE_REF_NT_TAB 
NESTED TABLE liste_tds STORE AS GroupeTD_REF_NT_TAB
NESTED TABLE liste_tps STORE AS GroupeTP_REF_NT_TAB
;

Create table Vacataire_tab of Vacataire_TY( constraint vacataire_id_pk PRIMARY KEY(nom))
NESTED TABLE liste_ue STORE AS UE_REF_NT_TAB2 
NESTED TABLE liste_tds STORE AS GroupeTD_REF_NT_TAB2
NESTED TABLE liste_tps STORE AS GroupeTP_REF_NT_TAB2
;

CREATE TABLE GroupeTD_tab of GroupeTD_TY ( constraint groupetd_id_pk PRIMARY KEY(id))
NESTED TABLE etudiants STORE AS Etudiant2_REF_NT_TAB
;
CREATE TABLE GroupeTP_tab of GroupeTP_TY  ( constraint groupetp_id_pk PRIMARY KEY(id))
NESTED TABLE etudiants STORE AS Etudiant3_REF_NT_TAB
;
CREATE TABLE  UE_tab of UE_TY(  constraint ue_id_code_pk PRIMARY KEY(id_code));



----------------------------------------------------------------------------------------------------------------
------------------------------------------- FONCTIONS-----------------------------------------------------------
----------------------------------------------------------------------------------------------------------------

create or replace FUNCTION volume_horaire_UE(IDCurs VARCHAR) RETURN NUMBER IS nb_h NUMBER;
BEGIN
--1TD
--11TP =2/3TD
--1CM=1.5TD
  select sum(deref(column_value).nb_seance_cm)*1.5 + sum(deref(column_value).nb_seance_td) + (sum(deref(column_value).nb_seance_tp)*3)/2
  into nb_h
  from cursus_tab c , table(c.liste_ue)
  WHERE id_code = IDCurs;
  RETURN nb_h * 80;
END volume_horaire_UE;
/



CREATE OR REPLACE TYPE BODY Cursus_TY as 
member function volume_horaire return NUMBER is 
begin
	RETURN VOLUME_HORAIRE_UE(id_code);
	end;
end;	
/

----------------------------------------------------------------------------------------------------------------
------------------------------------------- INSERTION-----------------------------------------------------------
----------------------------------------------------------------------------------------------------------------

INSERT INTO GroupeTD_tab values (1,30,NULL,NULL,NULL);
INSERT INTO GroupeTD_tab values (2,30,NULL,NULL,NULL);

INSERT INTO UE_tab values ('ALGO','452657',15,10,10,NULL);
INSERT INTO UE_tab values ('ANGLAIS','457741',15,10,10,NULL);
INSERT INTO UE_tab values ('GLO','454467',15,15,10,NULL);
INSERT INTO UE_tab values ('BD','457887',15,15,10,NULL);

INSERT INTO Titulaire_tab values('MrALMA','Chri','LINA',
null,-- MAJ plus tard
UE_REF_NT((Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='ALGO')),
GroupeTD_REF_NT((Select Ref(TD) FROM GroupeTD_tab TD WHERE TD.id=1)),
GroupeTP_REF_NT((Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=1)));
     

INSERT INTO Titulaire_tab values('ARDOUE','Ille','LINA',
null,
UE_REF_NT((Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='GLO')),
GroupeTD_REF_NT((Select Ref(TD) FROM GroupeTD_tab TD WHERE TD.id=1)),
GroupeTP_REF_NT((Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=1)));

INSERT INTO Titulaire_tab values('BRENDON','JEFF','LONDON',
null,
UE_REF_NT((Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='ANGLAIS')),
GroupeTD_REF_NT((Select Ref(TD) FROM GroupeTD_tab TD WHERE TD.id=1)),
GroupeTP_REF_NT((Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=1)));


INSERT INTO Vacataire_tab values('GEORGE','Sympas','LINA',
null, -- n'est reponsable d'aucun cursus
UE_REF_NT((Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='BD')),
GroupeTD_REF_NT((Select Ref(TD) FROM GroupeTD_tab TD WHERE TD.id=2)),
GroupeTP_REF_NT((Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=2)));


--MISE A JORU DES UE POUR LEUR ATTRIBUER LEURS RESPONSABLES
UPDATE ue_tab SET responsable_CM  = (Select Ref(T) FROM Titulaire_tab T WHERE T.nom='MrALMA') WHERE intitule='ALGO';
UPDATE ue_tab SET responsable_CM = (Select Ref(T) FROM Titulaire_tab T WHERE T.nom='ARDOUE')WHERE intitule='GLO';
UPDATE ue_tab SET responsable_CM = (Select Ref(T) FROM Titulaire_tab T WHERE T.nom='BRENDON')WHERE intitule='ANGLAIS';
UPDATE ue_tab SET responsable_CM = (Select Ref(T) FROM Vacataire_tab T WHERE T.nom='GEORGE')WHERE intitule='BD';





--5 ETUDIANT DANS LE CURSUS MINFO NECESSAIRE
INSERT INTO Etudiant_tab values ('RINCE','Ramir',99453,null);
INSERT INTO Etudiant_tab values ('LINUX','blague',92573,null);
INSERT INTO Etudiant_tab values ('LUTIN','barbu',98543,null);
INSERT INTO Etudiant_tab values ('DELASOUL','eric',99783,null);
INSERT INTO Etudiant_tab values ('LINUX2','heu',97853,null);


INSERT INTO Cursus_tab values ('M1INFO','C12452','M1',
(Select Ref(T) FROM Titulaire_tab T WHERE T.nom='MrALMA'),
GroupeTD_REF_NT((Select Ref(TD) FROM GroupeTD_tab TD WHERE TD.id=1)),
Etudiant_REF_NT((Select Ref(E) FROM Etudiant_tab E WHERE E.nom='RINCE'),
		(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LUTIN'),
		(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='DELASOUL'),
		(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LINUX'),
		(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LINUX2')),
UE_REF_NT((Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='ALGO'),
		  (Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='GLO'),
		  (Select Ref(UE) FROM UE_tab UE WHERE UE.intitule='ANGLAIS')));




--IL FAUT MAINTENANT MODIFIER LES ATTRIBUTS DANS LA TABLE ETUDIANT, LA REFERENCE DES CURSUS (ALORS A NULLE) POUR QUELLE REFERENCE LE CURSUS ALMA
UPDATE Etudiant_tab SET liste_cursus = Cursus_REF_NT((Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO'))WHERE nom='RINCE';
UPDATE Etudiant_tab SET liste_cursus = Cursus_REF_NT((Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO'))WHERE nom='LUTIN';
UPDATE Etudiant_tab SET liste_cursus = Cursus_REF_NT((Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO'))WHERE nom='DELASOUL';
UPDATE Etudiant_tab SET liste_cursus = Cursus_REF_NT((Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO'))WHERE nom='LINUX';
UPDATE Etudiant_tab SET liste_cursus = Cursus_REF_NT((Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO'))WHERE nom='LINUX2';

UPDATE Titulaire_tab SET cursus = (Select Ref(C) FROM Cursus_tab C WHERE C.intitule='M1INFO')WHERE nom='MrALMA';



INSERT INTO GroupeTP_tab values(1,
				Personnel_REF_VA((Select Ref(T) FROM Titulaire_tab T WHERE T.nom='MrALMA')),
				Etudiant_REF_NT((Select Ref(E) FROM Etudiant_tab E WHERE E.nom='RINCE'),
						(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='DELASOUL'),
						(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LUTIN')));

INSERT INTO GroupeTP_tab values(2,
				Personnel_REF_VA((Select Ref(T) FROM Titulaire_tab T WHERE T.nom='ARDOUE')),
				Etudiant_REF_NT((Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LINUX'),
						(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='LINUX2')));


UPDATE GroupeTD_tab SET responsable= (Select Ref(T) FROM Titulaire_tab T WHERE T.nom='MrALMA'),
       		    	tps=Groupe_TP_REF_VA((Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=1),(Select Ref(TP) FROM GroupeTP_tab TP WHERE TP.id=2)),
			 etudiants=Etudiant_REF_NT((Select Ref(E) FROM Etudiant_tab E WHERE E.nom='RINCE'),
			 			(Select Ref(E) FROM Etudiant_tab E WHERE E.nom='DELASOUL'));


----------------------------------------------------------------------------------------------------------------
------------------------------------------- REQUETES-------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
--1
select deref(column_value).nom as ETU_ALMA
from Cursus_tab c , table(c.etudiants)
where c.intitule='M1INFO';

--2
SELECT C.volume_horaire() AS TEST_FONCTION_VOLUME
FROM Cursus_tab C
WHERE C.intitule='M1INFO';