import java.util.ArrayList;

public class Encapsulateur<E> {

    // Pour ce sujet la valeur sera de type bool ou unit
    E valeur;

    // ArrayList est pertinante pour l'implémentation des listes d'adjacences ou
    // pas
    // (à vérifier pour les matrices)
    // ATTENTION : Le contenu de la liste est sans importance vu qu'elle
    // contient son id
    // elle permet juste de différencier différentes arêtes
    ArrayList<Integer> listeIdAretes;

    Encapsulateur(E val, int id) {
	valeur = val;
	listeIdAretes = new ArrayList<Integer>(id);
    }
    
    public Encapsulateur(E val) {	
    	valeur = val;
	listeIdAretes = null;
	}

    public E getValeur() {
	return valeur;
    }

    public void ajouterArete(Integer id) {
	// Pas de vérification sinon l'on doit effectuer un parcours qui
	// impacterait le cout de l'algo
	listeIdAretes.add(id);
    }

    public void supprimerArete(Integer id) {
	// Pas de vérification sinon l'on doit effectuer un parcours qui
	// impacterait le cout de l'algo
	listeIdAretes.remove(id);
    }
    
	public boolean isEmpty()
	{
		return listeIdAretes.isEmpty();
	}

   
}
