(*                                                  
Pour une execution depuis l'interprete, faire executer d'abord les directives 
suivantes :                                                                      
  #load "unix.cma";;
  #load "threads/threads.cma";;
  #directory "/comptes/heaulme-a/IN06/amble/lib";; (* selon repertoire ou se trouve amble.cma *)
  #load "amble.cma";;
*)

open Amble


(* ========================================================================== *)
(* Types des messages circulant sur les divers canaux de communication *)
(* et definition des types parametres de network *)
(* ========================================================================== *)

type canal = Val of int

(* ========================================================================== *)
(* processus Node*)
(* ========================================================================== *)

 type etat_node = Init | Attente
   
   class node reseau  id =
   object (self)
   inherit ['a] process Init id
   val mutable ma_valeur : int = Random.int(100);
   val mutable max : int =0;
     
     method garde_Init () =       
       true;
    
 method garde_Attente _ =       
       true;

     method j_envoie_des_le_depart () = 
       max <- ma_valeur;
       self#log (" -- valeurClientDeb : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
       self#write_all reseau (Val(max));


   
     method j_envoie_et_j_attends _ msg  =   
       match msg with Val(max_envoye)->
	 if max < max_envoye
	 then (max <- max_envoye;
	 self#log (" --new max : " ^ string_of_int(max)) ; (* pour tracer *)
       self#write_all reseau (Val(max)); )


(* -------------------------------------------------------------------------- *)

initializer
       
    (** definition des transitions (une seule ici) **)
       self#strans Init Attente
	 self#garde_Init
	 self#j_envoie_des_le_depart
	 
;


  (** definition des transitions (une seule ici) **)
       self#trans_all Attente Attente
	 reseau
	 self#garde_Attente
	 self#j_envoie_et_j_attends
   end


(* ========================================================================== *)
(* initialisation et lancement du systeme *)
(* ========================================================================== *)

           
(* !!!!!!!!  supprimer cette mise en commentaire des 7 lignes pour compilation 
   !!!!!!!!!!!!!!! la remettre pour interpretation du fichier (directive #use) *)                                  
let _ =   
    load_settings true [| |];
    let le_reseau = get_network "res" 
     in launch "node" (new node le_reseau);
       start ()
(* supprimer cette mise en commentaire de 7 lignes pour compilation  !!!!!! *)

(*---------*)   
             
                                                 
             (* EXEMPLES DE LIGNES DE COMMANDE *)
             (* VOIR impression_max_templates.ml *)
