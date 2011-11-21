DROP TABLE Etudiant_tab;
DROP TABLE Personnel_tab;
DROP TABLE Cursus_tab;
DROP TABLE GroupeTD_tab;
DROP TABLE GroupeTP_tab;
DROP TABLE UE_tab;

DROP TYPE Cursus_TY FORCE;
DROP TYPE UE_TY FORCE;
DROP TYPE GroupeTP_TY FORCE;
DROP TYPE GroupeTD_TY FORCE;
DROP TYPE Etudiant_TY FORCE;
DROP TYPE Titulaire_TY;
DROP TYPE Vacataire_TY;
DROP TYPE Personnel_TY;



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
	RETURN 1;
	end;
end;	
/

CREATE OR REPLACE TYPE UE_TY as object (intitule VARCHAR(25),id_code VARCHAR(25),nb_seance_CM NUMBER ,nb_seance_TD NUMBER,nb_seance_TP NUMBER);
/

CREATE OR REPLACE TYPE Titulaire_TY under Personnel_TY ();
/
CREATE OR REPLACE TYPE Vacataire_TY under Personnel_TY ();
/
CREATE OR REPLACE TYPE UE_NT as table of UE_TY;
/

CREATE OR REPLACE TYPE Cursus_TY as object (intitule VARCHAR(25),id_code VARCHAR(25), niveau VARCHAR(25),responsable REF Personnel_TY,ues UE_NT,
member function volume_horaire return NUMBER) nested table ues store as UE_NT_TAB ;
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
CREATE OR REPLACE TYPE GroupeTD_TY as object (id NUMBER, place_limite NUMBER);
/
CREATE OR REPLACE TYPE GroupeTP_TY as object (id NUMBER, place_limite NUMBER);
/


CREATE TABLE Etudiant_tab of Etudiant_TY;
CREATE TABLE Personnel_tab of Personnel_TY;
CREATE TABLE Cursus_tab of Cursus_TY;
CREATE TABLE GroupeTD_tab of GroupeTD_TY;
CREATE TABLE GroupeTP_tab of groupeTP_TY;
CREATE TABLE UE_tab of UE_TY;