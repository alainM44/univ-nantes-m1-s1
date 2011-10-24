import java.util.ArrayList;

public class Encapsulateur<E>
{

	// Pour ce sujet la valeur sera de type bool ou unit
	E valeur;
	int nbArc;
	// ArrayList est pertinante pour l'implémentation des listes d'adjacences ou
	// pas
	// (à vérifier pour les matrices)
	// ATTENTION : Le contenu de la liste est sans importance vu qu'elle
	// contient son id
	// elle permet juste de différencier différentes arêtes
	ArrayList<Integer> listeIdArc;

	Encapsulateur(E val, int id)
	{
		valeur = val;
		listeIdArc = new ArrayList<Integer>();
		listeIdArc.add(id);
		nbArc = 1;
	}

	public Encapsulateur(E val)
	{
		valeur = val;
		listeIdArc = null;
		nbArc = 0;
	}

	public E getValeur()
	{
		return valeur;
	}

	public int getNbArc()
	{
		return nbArc;
	}

	public ArrayList<Integer> getListe()
	{
		return listeIdArc;
	}

	public void ajouterArc(Integer id)
	{
		// Pas de vérification sinon l'on doit effectuer un parcours qui
		// impacterait le cout de l'algo
		listeIdArc.add(id);
		nbArc++;
	}

	public void supprimerArc(Integer id)
	{
		// Pas de vérification sinon l'on doit effectuer un parcours qui
		// impacterait le cout de l'algo
		listeIdArc.remove(id);
		nbArc--;
	}

	public boolean isEmpty()
	{
		return listeIdArc.isEmpty();
	}

	/*
	 * @param i : indique la variation a effectue sur le nombre d'arc (peut être positif ou negatif)
	 */
	public void changeNbArc(int i)
	{
		nbArc += i;
	}

}
