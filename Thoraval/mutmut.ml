(*                                                  
Pour une execution depuis l'interprete, faire executer d'abord les directives 
suivantes :                                                                      
  #load "unix.cma";;
  #load "threads/threads.cma";;
  #directory "/comptes/heaulme-a/IN06/amble/lib";; (* selon repertoire ou se trouve amble.cma *)
  #load "amble.cma";;
*)

open Map
open Amble

int maison=0;
(* ========================================================================== *)
(* Types des messages circulant sur les divers canaux de communication *)
(* et definition des types parametres de network *)
(* ========================================================================== *)
type canal = Acc of int
type canal = Req of int

 type chatchat = HC | Candidat | SC
   
   class node reseau  id =
     object (self)
       inherit ['a] process HC id
       val mutable horlogeL : int =0;
       val mutable concurrents : Map
	 
       method garde_HC () =       
	 true;
	 
       method candidat_vers_SC contrat =       
	 match contrat with Acc(i) ->
	   i=id

       method candidat_a_candidat contrat =       
	 match contrat with Acc(i) ->
	   i<>id
	 
       method garde_SC _ =       
	 true;
	 
       method debut_HC_a_Candidat () = 
	 horlogeL := horlogeL +1;
	 
       method de_HC_a_Candidat _ = 
	 horlogeL := horlogeL +1;
       
       method garde_demande  = 
	 match msg with Req(horloge)->
	   true

       method garde_acq  = 
	 match msg with Acq(id)->
	   true

       method reste_Candidat msg = 
	 horlogeL := horlogeL +1;
	 match msg with Acq(id)->
	   concurrents := remove (i concurrents)

       method de_Candidat_a_SC msg = 
	 horlogeL := horlogeL +1;
	 maison := maison + id

       method nouvelle_demande i msg = 
	 horlogeL := horlogeL +1;
	 match msg with Req(horloge)->
	   if(horloge > horlogeL) then
	     horlogeL := horloge +1;
	   concurrents := add (i horloge concurrents)


(* -------------------------------------------------------------------------- *)

initializer
       
    (** definition des transitions (une seule ici) **)
       self#strans HC Candidat
	 self#garde_HC
	 self#debut_HC_a_Candidat
	 
;
   (** definition des transitions (une seule ici) **)
       self#strans HC HC
	 self#garde_demande
	 self#nouvelle_demande
	 
;

      (** definition des transitions (une seule ici) **)
       self#strans HC HC
	 self#garde_acq
	 self#nouvel_acq
	 
;
      (** definition des transitions (une seule ici) **)
       self#strans Candidat Candidat
	 self#candidat_a_candidat
	 self#reste_candidat	 
;
  (** definition des transitions (une seule ici) **)
       self#strans Candidat Candidat
	 self#garde_demande
	 self#nouvelle_demande
	 
;

  (** definition des transitions (une seule ici) **)
       self#strans Candidat SC
	 self#candidat_vers_SC
	 self#de_Candidat_a_SC
	 
;


end
