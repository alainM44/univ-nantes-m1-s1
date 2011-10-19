import java.util.ArrayList;
import java.util.List;

public interface GrapheOriente
{

	/*
	 * Ajoute le noeud n au graphe
	 * 
	 * @param n : la valeur du Noeud
	 */
	public void ajouterN(int n);

	/*
	 * Supprime le noeud n du graphe
	 * 
	 * @param n : la valeur du Noeud
	 */
	public void supprimerN(int n);

	/*
	 * Ajoute l'arete entre n1 et n2 au graphe et retourne un l'id de cette
	 * arête
	 * 
	 * @param n : la valeur du Noeud
	 * 
	 * @return int valeur de l'id
	 */
	public int ajouterA(int n1, int n2);

	/*
	 * Supprime l'arete entre n1 et n2 du graphe ayant comme identifiant id
	 * 
	 * @param n : la valeur du Noeud
	 */
	public void supprimerA(int id, int n1, int n2);
	
	public ArrayList<Integer> listeNoeuds();
	
	public ArrayList<Integer> listeAretes();

	public List<Integer> listerSuccesseurs(int n);

	public List<Integer> listerPredecesseurs(int n);

	public List<Integer> listerArcsEntrants(int n);

	public List<Integer> listerArcsSortants(int n);

	public int NombreNoeuds();

	public int NombreAretes();

}