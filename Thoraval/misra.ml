open Amble

type canal = React of int
type ferme = Jeton of int
type tueur = Kill of int

 type misra = Traitre | Simple | Final

  class chat reseau  id =     
    object (self)
      inherit ['a] process Simple id
      val mutable actif : bool  = true;
      val mutable inactif_depuis_jeton : bool = false;

method garde_actif () =
actif

method garde_non_actif msg =
match msg with React(b) ->
  not actif

method desactive () =
actif := false

method envoi_desactive () =
actif := false;
self#write_all reseau (React(id))

method reactive msg =
actif := vrai;
inactif_depuis_jeton :=false

method garde_attrape_jeton_inutile msg = 
match msg with Jeton(b)->
  not actif && not inactif_depuis_jeton

method relance_jeton msg =
  self#write_all reseau (Jeton(id));
inactif_depuis_jeton := true

method garde_attrape_jeton_diff msg = 
match msg with Jeton(b)->
  not actif &&  inactif_depuis_jeton && b <> id

method relance_jeton_identique msg =
  self#write_all reseau (msg);
inactif_depuis_jeton := true

method garde_attrape_jeton_identique msg = 
match msg with Jeton(b)->
  not actif &&  inactif_depuis_jeton && b = id

method lance_kill msg =
  self#write_all reseau (Kill(id));

method garde_kill_diff msg = 
match msg with Kill(b)->
b<>id

method garde_kill_identique msg = 
match msg with Kill(b)->
b=id

method transmet_kill msg =
  self#write_all reseau (msg)

method stop_tout msg = 
self#log ("Fin ")

initializer
       
    (** definition des transitions (une seule ici) **)
  self#strans Simple Simple
    self#garde_actif
    self#desactive
    
    ;
  
  self#strans Simple Simple
    self#garde_actif
    self#envoi_desactive
    
    ;      
  
  self#trans_all Simple Simple
    reseau
    self#garde_non_actif
    self#reactive
    
    ;

  self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_inutile
    self#relance_jeton
    
    ;  

self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_diff
    self#relance_jeton_identique
    
    ;

self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_identique
    self#lance_kill
    
    ;

self#trans_all Simple Final
    reseau
    self#garde_kill_diff
    self#transmet_kill
    
    ;

self#trans_all Simple Final
    reseau
    self#garde_kill_identique
    self#stop_tout
    
    end
      
      
class mechant_chat reseau  id =     
  object (self)
    inherit ['a] process Traitre id
    val mutable actif : bool  = true;
    val mutable inactif_depuis_jeton : bool = false;
	
    method garde_actif () =
      actif
	
    method garde_non_actif msg =
      match msg with React(b) ->
	!actif
	  
    method desactive () =
      actif := false

method envoi_desactive () =
actif := false;
self#write_all reseau (React(id))

method reactive msg =
actif := vrai;
inactif_depuis_jeton :=false

method garde_attrape_jeton_inutile msg = 
match msg with Jeton(b)->
  not actif && not inactif_depuis_jeton

method relance_jeton msg =
  self#write_all reseau (Jeton(id));
inactif_depuis_jeton := true

method garde_attrape_jeton_diff msg = 
match msg with Jeton(b)->
  not actif &&  inactif_depuis_jeton && b <> id

method relance_jeton_identique msg =
  self#write_all reseau (msg);
inactif_depuis_jeton := true

method garde_attrape_jeton_identique msg = 
match msg with Jeton(b)->
  not actif &&  inactif_depuis_jeton && b = id

method lance_kill msg =
  self#write_all reseau (Kill(id));

method garde_kill_diff msg = 
match msg with Kill(b)->
b<>id

method garde_kill_identique msg = 
match msg with Kill(b)->
b=id

method transmet_kill msg =
  self#write_all reseau (msg);

method stop_tout msg = self#log ("Fin ")

method garde_traitre () =
true

method trahison () =
self#write_all reseau (Jeton(-1))


initializer
       
    (** definition des transitions (une seule ici) **)
  self#strans Simple Simple
    self#garde_actif
    self#desactive
    
    ;
  
  self#strans Simple Simple
    self#garde_actif
    self#envoi_desactive
    
    ;      
  
  self#trans_all Simple Simple
    reseau
    self#garde_non_actif
    self#reactive
    
    ;

  self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_inutile
    self#relance_jeton
    
    ;  

self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_diff
    self#relance_jeton_identique
    
    ;

self#trans_all Simple Simple
    reseau
    self#garde_attrape_jeton_identique
    self#lance_kill
    
    ;

self#trans_all Simple Final
    reseau
    self#garde_kill_diff
    self#transmet_kill
    
    ;

self#trans_all Simple Final
    reseau
    self#garde_kill_identique
    self#stop_tout
    
    ;


self#trans_all Traitre Simple
    reseau
    self#garde_traitre
    self#trahison
    
end


let _ =   
    load_settings true [| |];
    let le_reseau = get_network "reseau" 
    in 
    launch "chat" (new chat le_reseau);
    launch "mechant_chat" (new mechant_chat le_reseau);
       start ()
