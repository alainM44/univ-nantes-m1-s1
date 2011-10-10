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

   method je_recois_et_j_attends _ msg =
   self#log (" -- valeurServeur : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
   match msg with Val_client(le_max) -> 
   if le_max > ma_valeur
   then   (self#write_all reseau_vers_client (Max(le_max));
ma_valeur <- le_max)
   else   self#write_all reseau_vers_client (Max(ma_valeur));
     self#log (" -- valeurclient : " ^ string_of_int(le_max)) ; (* pour tracer *)
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
   
   
   type etat_client = Initial | Valeur_envoyee
   
   class client reseau_vers_serveur  id=
   object (self)
   inherit ['a] process Initial id
   val mutable ma_valeur : int = Random.int(100)
   
   method pret_a_envoyer () =
   true
   
   method j_envoie_et_c_est_fini () =
     (* self#log (" -- valeur : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)*)
	self#write_all reseau_vers_serveur (Val_client(ma_valeur))
	
	
(* -------------------------------------------------------------------------- *)


 initializer
  
    (** definition des transitions (une seule ici) **)
        self#strans Initial Valeur_envoyee
                       self#pret_a_envoyer
                       self#j_envoie_et_c_est_fini
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
       launch "client" (new client le_reseau_vers_serveur);
       start ()
(* supprimer cette mise en commentaire de 7 lignes pour compilation  !!!!!! *)

(*---------*)   
             
                                                 
             (* EXEMPLES DE LIGNES DE COMMANDE *)
             (* VOIR impression_max_templates.ml *)
