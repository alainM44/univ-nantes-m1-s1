import java.util.ArrayList;

public interface GrapheOriente
{

	/**
	 * Ajoute le noeud n au graphe
	 * 
	 * @param n : la valeur du Noeud
	 */
	public void ajouterN(int n);

	/**
	 * Supprime le noeud n du graphe
	 * 
	 * @param n : la valeur du Noeud
	 */
	public void supprimerN(int n);

	/**
	 * Ajoute l'arete entre n1 et n2 au graphe et retourne l'id de cette
	 * arête
	 * 
	 * @param n1 : la valeur du Noeud de départ
	 * @param n2 : la valeur du Noeud d'arrivée
	 * 
	 * @return int valeur de l'id
	 */
	public int ajouterA(int n1, int n2);

	/**
	 * Supprime l'arete entre n1 et n2 du graphe ayant comme identifiant id
	 * 
	 * @param n1 : la valeur du Noeud de départ
	 * @param n2 : la valeur du Noeud d'arrivée
	 */
	public void supprimerA(int id, int n1, int n2);
	
	/**
	 * 
	 * @return la liste des noeud
	 */
	public ArrayList<Integer> listeNoeuds();
	
	/**
	 * 
	 * @return la liste des Arcs
	 */
	public ArrayList<Arc> listeArcs();

	/**
	 * Cherche les successeurs d'un noeud dans un graphe orienté
	 * @param n Noeud dont l'on cherche les successeurs
	 * @return La liste des noeuds successeurs sous forme d'entier
	 */
	public ArrayList<Integer> listerSuccesseurs(int n);

	/**
	 * Cherche les predecesseurs d'un noeud dans un graphe orienté
	 * @param n Noeud dont l'on cherche les predecesseurs
	 * @return La liste des noeuds predecesseurs sous forme d'entier
	 */
	public ArrayList<Integer> listerPredecesseurs(int n);

	/**
	 * Cherche la liste des Arcs entrants en un Noeud
	 * @param n Noeud dont l'on cherche les arcs entrants
	 * @return La liste des Arcs qui entrent en n
	 */
	public ArrayList<Arc> listerArcsEntrants(int n);

	/**
	 * Cherche la liste des Arcs sortants d'un Noeud
	 * @param n Noeud dont l'on cherche les arcs sortants
	 * @return La liste des Arcs qui sortent de n
	 */
	public ArrayList<Arc> listerArcsSortants(int n);

	/**
	 * 
	 * @return Le nombre de noeuds du graphe
	 */
	public int NombreNoeuds();

	/**
	 * 
	 * @return Le nombre d'arc du graphe
	 */
	public int NombreArcs();
	
}