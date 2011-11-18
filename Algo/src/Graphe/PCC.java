package Graphe;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.TreeSet;
import java.util.concurrent.ArrayBlockingQueue;

/**
 * La classe va appliquer les différents algorithmes demandés peut-être aussi
 * les benchmarks
 */
public class PCC
{
	GrapheOriente	monGraphe;

	public PCC(GrapheOriente graphe)
	{
		monGraphe = graphe;
	}

	/**
	 * @param n
	 *            : noeud de départs
	 * @param option
	 *            : si vrai alors parcourir tout le graphe
	 * @param horloge
	 *            : hashmap fourni en paramêtre qui indice les noeuds par des
	 *            temps(permet de conserver l'horloge chez l'appelant)
	 * 
	 * @return : pi une hashmap de noeuds d'arrivés indicé par leur noeud de
	 *         départ.
	 */
	public HashMap<Integer, Integer> DFS(int n, boolean option, HashMap<Integer, Integer> horloge)
	{
		int temps = 0;
		ArrayList<Integer> listeNoeud = monGraphe.listeNoeuds();
		// 0 est la couleur blanche, 1 la couleur grise, 2 la couleur noire
		HashMap<Integer, Integer> couleur = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();


		for (Integer noeud : listeNoeud)
		{
			couleur.put(noeud, 0);
		}

		pi.put(n, n);
		temps = Visiter(n, temps, couleur, pi, horloge);

		if (option)
		{
			for (Integer noeud : listeNoeud)
			{
				if (couleur.get(noeud) == 0)
				{
					pi.put(noeud, noeud);
					temps = Visiter(noeud, temps, couleur, pi, horloge);
				}
			}
		}
		return pi;
	}

	private int Visiter(int n, int temps, HashMap<Integer, Integer> couleur, HashMap<Integer, Integer> pi, HashMap<Integer, Integer> d)
	{
		ArrayList<Integer> voisins = monGraphe.listerSuccesseurs(n);
		d.put(temps, n);
		temps++;
		couleur.put(n, 1);
		for (Integer voisin : voisins)
		{
			if (couleur.get(voisin) == 0)
			{
				pi.put(voisin, n);
				temps = Visiter(voisin, temps, couleur, pi, d);
			}
		}
		couleur.put(n, 2);
		temps++;
		return temps;
	}

	/**
	 * @param n
	 *            : noeud de départ
	 * @param option
	 *            : si vrai alors parcourir tout le graphe
	 * @param horloge
	 *            : hashmap fourni en paramêtre qui indice les noeuds par des
	 *            temps(permet de conserver l'horloge chez l'appelant)
	 * 
	 * @return : pi une hashmap de noeuds d'arrivés indicé par leur noeud de
	 *         départ.
	 */
	public void /*??*/Dijkstra(int n, boolean option, HashMap<Integer, Integer> horloge, ArrayList<Integer> tab_routes)
	{
		int temps = 0;
		int noeudCourant;
		ArrayList<Integer> listeNoeud = monGraphe.listeNoeuds();

		// 0 est la couleur blanche, 1 la couleur grise, 2 la couleur noire
		HashMap<Integer, Integer> couleur = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		PriorityQueue<Integer> file =  new PriorityQueue<Integer>();


		// a remplir avec les routes apres cacluls de leur pondération
		HashMap<Integer, Integer> d = new HashMap<Integer, Integer>();


		for (Integer noeud : listeNoeud)
		{
			d.put(noeud,-1); //-1 ou l'infini ?
			pi.put(noeud, 0);
		}		

		//on remplie la file
		for (Integer route : tab_routes)
		{
			file.add(route);
		}		
		//INIT
		d.put(1,0);
		pi.put(1,1);


		while (!file.isEmpty())
		{
			noeudCourant = file.poll();
			for (Integer voisin : monGraphe.listerSuccesseurs(noeudCourant)) // 
			{
				if (d.get(noeudCourant)<tab_routes.get(voisin)+d.get(noeudCourant))
				{
					d.put(noeudCourant, tab_routes.get(voisin)+d.get(noeudCourant));
					pi.put(voisin,noeudCourant);

				}
			}
		}

		//return pi;
	}
	/**
	 * @param route
	 *            : route concernée
	 * @param dmax
	 *            : plus grande distance affectée à une route
	 * @param imax
	 *            : plus grand intérêt porté à un lieu ou à une route
	 * @param A
	 *            :paramètre réel compris en 0 et 1 qui représente l’importance respective donnée
	 *à la distance par rapport à l’intérêt touristique : lorsque A = 0 le chemin calculé dépend uniquement
	 *de l’intérêt, alors que lorsque A = 1 il ne dépend que de la distance.


	 */

	//QUELLE SOLUTION LORSQUE QUE LON A UN RESULTAT NEGATIF?
	public double get_agregat(Route route, int dmax,int imax,double A){
		double result;
		//wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗ imax )
result=A*route.getLongueur()/dmax-(1-A* route.getN2() (2*imax);
		return result;
	}
	
}
