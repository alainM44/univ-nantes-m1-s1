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

type canal_vers_serveur = Val_client of int
    
type canal_vers_client = Max of int
    
(* ========================================================================== *)
(* processus serveur*)
(* ========================================================================== *)
   type etat_serveur = Attente
   
   class serveur reseau_vers_client reseau_vers_serveur id =
   object (self)
   inherit ['a] process Attente id
   val mutable ma_valeur : int = 0
   
   method pret_a_envoyer _ =  
   true

   method je_recois_et_j_attends i msg =
   self#log (" -- valeurServeur : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
   match msg with Val_client(le_max) -> 
   if le_max >= ma_valeur
   then  (ma_valeur <- le_max;
	  self#write reseau_vers_client i  (Max(ma_valeur)); self#log (" --reponseIf "^ string_of_int(i)) ;)
   else   (self#write reseau_vers_client i  (Max(ma_valeur));self#log (" --reponseElse "^ string_of_int(i));)
(* -------------------------------------------------------------------------- *)
   
   
   initializer
   
    (** definition des transitions (une seule ici) **)
   self#trans_all Attente Attente
   reseau_vers_serveur
   self#pret_a_envoyer
   self#je_recois_et_j_attends
   end
(* ========================================================================== *)
(* processus client*)
(* ========================================================================== *)
   
   
   type etat_client = Initial | Patiente
   
   class client reseau_vers_serveur reseau_vers_client id=
   object (self)
   inherit ['a] process Initial id
   val mutable ma_valeur : int = Random.int(100);
     
     method garde_Init () =       
       true;
	 
     method serveur_plus_petit msg =       
       match msg with Max(max_serveur)->
	 max_serveur<=ma_valeur
	   
     method j_envoie_et_j_attends _ _ =       
       ma_valeur <- Random.int(100);
       self#log (" -- valeurClientAttente : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
       self#write_all reseau_vers_serveur (Val_client(ma_valeur));
	
     method j_envoie_des_le_depart () =       
       ma_valeur <- Random.int(100);
       self#log (" -- valeurClientDeb : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
       self#write_all reseau_vers_serveur (Val_client(ma_valeur))
(* -------------------------------------------------------------------------- *)

       
     initializer
       
    (** definition des transitions (une seule ici) **)
       self#strans Initial Patiente
	 self#garde_Init
	 self#j_envoie_des_le_depart
	 
;
       
    (** definition des transitions (une seule ici) **)
       self#trans_all Patiente Patiente
	 reseau_vers_client
	 self#serveur_plus_petit
	 self#j_envoie_et_j_attends
   end

(* ========================================================================== *)
(* initialisation et lancement du systeme *)
(* ========================================================================== *)

           
(* !!!!!!!!  supprimer cette mise en commentaire des 7 lignes pour compilation 
   !!!!!!!!!!!!!!! la remettre pour interpretation du fichier (directive #use) *)                                  
let _ =   
    load_settings true [| |];
    let le_reseau_vers_serveur = get_network "res_vers_serveur" 
    in let le_reseau_vers_client = get_network "res_vers_client" 
    in launch "serv" (new serveur le_reseau_vers_client le_reseau_vers_serveur);
       launch "client" (new client le_reseau_vers_serveur le_reseau_vers_client);
       start ()
(* supprimer cette mise en commentaire de 7 lignes pour compilation  !!!!!! *)

(*---------*)   
             
                                                 
             (* EXEMPLES DE LIGNES DE COMMANDE *)
             (* VOIR impression_max_templates.ml *)
