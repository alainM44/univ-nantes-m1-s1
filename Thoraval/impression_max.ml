(* UNIVERSITE DE NANTES - MASTER INFORMATIQUE I - MODULE S1IA030 PARALLELISME - 2008/2009 - *)
(* programme d'introduction aux TP en Amble *)
(* Alain HEAULME - Rene THORAVAL *)

(* Un exemple tres simple, sans veritable parallelisme effectif, mais utile pour une 
   introduction la plus simple possible a la programmation avec Amble *)

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
(* type canal_vers_droite
   reseau initialise par les fichiers de topologie obtenus par get_network *)
(* le message max_gauche transmet vers la droite l'entier maximum de tous les processus
   situes a gauche, y compris le processus expediteur *)

type canal_vers_droite = Max_gauche of int

(* ========================================================================== *)
(* processus premier (situe en tete de chaine*)
(* ========================================================================== *)

(* compteur ordinal du processus premier - deux etats, pour une seule transition *)
type etat_premier = Initial | Valeur_envoyee

(* -------------------------------------------------------------------------- *)
class premier reseau_vers_droite id =
object (self)
    inherit ['a] process Initial id
    val mutable ma_valeur : int = Random.int(100)

(* -------------------------------------------------------------------------- *)
(** fonctions utilisees dans les gardes et commandes gardees **)


   (* garde sans condition (en fait condition systematiquement evaluee a vrai *)
    method pret_a_envoyer () =
      true
    method j_envoie_et_c_est_fini () =
      self#log (" -- valeur : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
      self#write_all reseau_vers_droite (Max_gauche(ma_valeur))
      (* pourrait etre, en utilisant l'identite du destinataire 
         (les connexions sont alors necessairement supposees faites dans 
          l'ordre des id) : 
       self#write reseau_vers_droite (id + 1) (Max_gauche(ma_valeur))
      *)

(* -------------------------------------------------------------------------- *)
  initializer

    (* definition des transitions (une seule ici) *)
      self#strans Initial Valeur_envoyee 
                  self#pret_a_envoyer 
                  self#j_envoie_et_c_est_fini 

end

(*
class premier :
  canal_vers_droite Amble.network ->
  int ->
  object
    val mutable ma_valeur : int
    method id : int
    method j_envoie_et_c_est_fini : unit -> unit
    method log : string -> unit
    method nbsites : 'a Amble.network -> int
    method pret_a_envoyer : unit -> bool
    method strans :
      etat_premier ->
      etat_premier -> (unit -> bool) -> (unit -> unit) -> unit
    method trans :
      etat_premier ->
      etat_premier ->
      'b Amble.network -> int -> ('b -> bool) -> ('b -> unit) -> unit
    method trans_all :
      etat_premier ->
      etat_premier ->
      'c Amble.network -> ('c -> bool) -> (int -> 'c -> unit) -> unit
    method write : 'd Amble.network -> int -> 'd -> unit
    method write_all : 'e Amble.network -> 'e -> unit
  end
*)



(* ========================================================================== *)
(* processus imprimante *)
(* ========================================================================== *)

(* compteur ordinal du processus imprimante - deux etats, une seule transition *)
type etat_imprimante = Pret_impression | Max_imprime

(* -------------------------------------------------------------------------- *)
class imprimante reseau_vers_droite id =
object (self)
    inherit ['a] process Pret_impression id

(* -------------------------------------------------------------------------- *)
(** fonctions utilisees dans les gardes et commandes gardees **)

(* reception du max a imprimer *)
                                               (* garde sur reception message *)
    method quand_reception_max _ (* pour msg *) =
      true
                         (* commande gardee - tableau transitions - trans_all *)
    method imprime_max _ (* pour expediteur *) msg =
      match msg with Max_gauche(le_max) -> self#log ("Maximum : " 
                                                     ^ string_of_int(le_max))
     (* plus simplement, pourrait etre : 
      method imprime_max _  Max_gauche(le_max) =
         self#log ("Maximum : " ^ string_of_int(le_max))
     *)

(* -------------------------------------------------------------------------- *)

  initializer
  
    (** definition des transitions (une seule ici) **)
        self#trans_all Pret_impression Max_imprime 
                       reseau_vers_droite 
                       self#quand_reception_max
                       self#imprime_max

end

(*class imprimante :
  canal_vers_droite Amble.network ->
  int ->
  object
    method id : int
    method imprime_max : int -> canal_vers_droite -> unit
    method log : string -> unit
    method nbsites : 'a Amble.network -> int
    method quand_reception_max : canal_vers_droite -> bool
    method strans :
      etat_imprimante ->
      etat_imprimante -> (unit -> bool) -> (unit -> unit) -> unit
    method trans :
      etat_imprimante ->
      etat_imprimante ->
      'b Amble.network -> int -> ('b -> bool) -> ('b -> unit) -> unit
    method trans_all :
      etat_imprimante ->
      etat_imprimante ->
      'c Amble.network -> ('c -> bool) -> (int -> 'c -> unit) -> unit
    method write : 'd Amble.network -> int -> 'd -> unit
    method write_all : 'e Amble.network -> 'e -> unit
  end
*)



(* ========================================================================== *)
(* processus intermediaire *)
(* ========================================================================== *)

(* compteur ordinal du processus intermediaire *)
type etat_intermediaire = En_attente_max | Max_envoye

(* -------------------------------------------------------------------------- *)
class intermediaire reseau_vers_droite id =
object (self)
    inherit ['a] process En_attente_max id
    val mutable ma_valeur : int = Random.int(100)

(* -------------------------------------------------------------------------- *)
(** fonctions utilisees dans les gardes et commandes gardees **)

(* reception du max de gauche *)
                                               (* garde sur reception message *)
    method quand_reception_max_gauche _ =
                     (* _ pour msg qui est de toutes facons Max_gauche(_) *)
      true
           
                         (* commande gardee - tableau transitions - trans_all *)
    method fais_suivre_max_gauche _ (* pour expediteur *) msg =
      self#log (" -- valeur : " ^ string_of_int(ma_valeur)) ; (* pour tracer *)
      match msg with Max_gauche(le_max_gauche) -> 
         if ma_valeur > le_max_gauche
           then self#write_all reseau_vers_droite (Max_gauche(ma_valeur))
           else self#write_all reseau_vers_droite (Max_gauche(le_max_gauche))

(* -------------------------------------------------------------------------- *)

  initializer
  
    (** definition des transitions (une seule ici) **)
        self#trans_all En_attente_max Max_envoye 
                       reseau_vers_droite  
                       self#quand_reception_max_gauche
                       self#fais_suivre_max_gauche

end

(*class intermediaire :
  canal_vers_droite Amble.network ->
  int ->
  object
    val mutable ma_valeur : int
    method fais_suivre_max_gauche : int -> canal_vers_droite -> unit
    method id : int
    method log : string -> unit
    method nbsites : 'a Amble.network -> int
    method quand_reception_max_gauche : canal_vers_droite -> bool
    method strans :
      etat_intermediaire ->
      etat_intermediaire -> (unit -> bool) -> (unit -> unit) -> unit
    method trans :
      etat_intermediaire ->
      etat_intermediaire ->
      'b Amble.network -> int -> ('b -> bool) -> ('b -> unit) -> unit
    method trans_all :
      etat_intermediaire ->
      etat_intermediaire ->
      'c Amble.network -> ('c -> bool) -> (int -> 'c -> unit) -> unit
    method write : 'd Amble.network -> int -> 'd -> unit
    method write_all : 'e Amble.network -> 'e -> unit
  end
*)

(* ========================================================================== *)
(* initialisation et lancement du systeme *)
(* ========================================================================== *)

           
(* !!!!!!!!  supprimer cette mise en commentaire des 7 lignes pour compilation 
   !!!!!!!!!!!!!!! la remettre pour interpretation du fichier (directive #use) *)                                  
let _ =             
    load_settings true [| |];
    let le_reseau_vers_droite = get_network "res_vers_droite" 
    in launch "prem" (new premier le_reseau_vers_droite);
       launch "inter" (new intermediaire le_reseau_vers_droite);
       launch "imprim" (new imprimante le_reseau_vers_droite) ;
       start ()
(* supprimer cette mise en commentaire de 7 lignes pour compilation  !!!!!! *)

(*---------*)   
             
                                                 
             (* EXEMPLES DE LIGNES DE COMMANDE *)
             (* VOIR impression_max_templates.ml *)
