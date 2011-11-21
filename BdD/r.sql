
DROP TABLE Etudiant_tab;
DROP TABLE Personnel_tab;
DROP TABLE Cursus_tab;
DROP TABLE GroupeTD_tab;
DROP TABLE GroupeTP_tab;
DROP TABLE UE_tab;

DROP TYPE Etudiant_TAB_REF FORCE;
DROP TYPE Cursus_TY FORCE;
DROP TYPE UE_TY FORCE;
DROP TYPE Etudiant_TY FORCE;
DROP TYPE Titulaire_TY FORCE;
DROP TYPE Vacataire_TY FORCE;
DROP TYPE Personnel_REF_VA FORCE;
DROP TYPE Personnel_TY FORCE;

-- Mémo pour le login
-- source /etc/profile
-- sqlplus admi9@cienetdb 
-- afficher les tables select * from tab; 



-- cascade constraints;

--1TD
--11TP =2/3TD
--1CM=1.5TD



CREATE OR REPLACE TYPE Personnel_TY as object (nom VARCHAR(25),prenom VARCHAR(25),equipe VARCHAR(25),id NUMBER, --!!!
member function volume_horaire_EquiTD return NUMBER) not final;
/

CREATE OR REPLACE TYPE BODY Personnel_TY as 
member function volume_horaire_EquiTD return NUMBER is 
      begin
	RETURN 1;
	end;
end;	
/
CREATE OR REPLACE type Personnel_REF_VA as varray(5) of REF Personnel_TY;
/

CREATE OR REPLACE TYPE UE_TY as object (intitule VARCHAR(25),id_code VARCHAR(25),nb_seance_CM NUMBER ,nb_seance_TD NUMBER,nb_seance_TP NUMBER);
/

CREATE OR REPLACE TYPE Titulaire_TY under Personnel_TY ();
/
CREATE OR REPLACE TYPE Vacataire_TY under Personnel_TY ();
/
CREATE OR REPLACE TYPE UE_NT as table of UE_TY;
/

CREATE OR REPLACE TYPE Etudiant_TY as object (nom VARCHAR(25),prenom VARCHAR(25), num_etu VARCHAR(25));
/

CREATE TYPE Etudiant_TAB_REF  AS TABLE OF REF Etudiant_TY;
/
CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),id_code VARCHAR(25), niveau VARCHAR(25),responsable REF Personnel_TY,
member function volume_horaire return NUMBER);
/

CREATE OR REPLACE TYPE BODY Cursus_TY as 
member function volume_horaire return NUMBER is 
      begin
	RETURN 1;
	end;
end;	
/







CREATE TABLE GroupeTD_tab (id NUMBER, placelimite NUMBER );----??


CREATE OR REPLACE TYPE Cursus_NT as table of Cursus_TY;
/
CREATE TABLE GroupeTP_tab (id NUMBER, liste_etu Etudiant_TAB_REF,responsables Personnel_REF_VA)  NESTED TABLE liste_etu STORE AS Etudiant_TAB_REF_NT;


CREATE TABLE Etudiant_tab (etudiant Etudiant_TY, liste_cursus Cursus_NT) NESTED TABLE liste_cursus STORE AS Cursus_NT_TAB;

CREATE TABLE Personnel_tab of Personnel_TY;
CREATE TABLE Cursus_tab of Cursus_TY;

CREATE TABLE UE_tab of UE_TY;

--CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),id_code VARCHAR(25), niveau VARCHAR(25),responsable REF Personnel_TY,

INSERT INTO Personnel_tab values('MrALMA','Chri','LINA',1);
INSERT INTO Etudiant_tab values (Etudiant_TY('RINCE','Ramir',99453),Cursus_NT(Cursus_TY('ALMA','1','MASTER',(select ref (p)FROM Personnel_tab p WHERE p.id=1) )));
--INSERT INTO Etudiant_tab values (Etudiant_TY('RINCE','Romain',99453));
--INSERT INTO Etudiant_tab values (Etudiant_TY('LINUX','blague',99453));
--INSERT INTO Etudiant_tab values (Etudiant_TY('LUTIN','barbu',99453));
--INSERT INTO Etudiant_tab values (Etudiant_TY('DELASOUL','eric',99453));