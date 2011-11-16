package Graphe;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.concurrent.ArrayBlockingQueue;

/**
 * La classe va appliquer les différents algorithmes demandés peut-être aussi
 * les benchmarks
 */
public class TestMonGraphe
{
	GrapheOriente	monGraphe;

	public TestMonGraphe(GrapheOriente graphe)
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
	public HashMap<Integer, Integer> BFS(int n, boolean option, HashMap<Integer, Integer> horloge)
	{
		int temps = 0;
		int noeudCourant;
		ArrayList<Integer> listeNoeud = monGraphe.listeNoeuds();
		// 0 est la couleur blanche, 1 la couleur grise, 2 la couleur noire
		HashMap<Integer, Integer> couleur = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		ArrayBlockingQueue<Integer> file = new ArrayBlockingQueue<Integer>(monGraphe.NombreNoeuds());

		for (Integer noeud : listeNoeud)
		{
			couleur.put(noeud, 0);
		}

		try
		{
			file.put(n);
		} catch (InterruptedException e)
		{
			e.printStackTrace();
		}
		pi.put(n, n);
		while (!file.isEmpty())
		{
			noeudCourant = file.poll();
			horloge.put(temps, noeudCourant);
			temps++;
			for (Integer voisin : monGraphe.listerSuccesseurs(noeudCourant))
			{
				if (couleur.get(voisin) == 0)
				{
					couleur.put(voisin, 1);
					pi.put(voisin, noeudCourant);
					try
					{
						file.put(voisin);
					} catch (InterruptedException e)
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
			couleur.put(noeudCourant, 2);
			if (option && file.isEmpty())
			{
				for (Integer noeud : listeNoeud)
				{
					if (couleur.get(noeud) == 0)
					{
						try
						{
							file.put(noeud);
						} catch (InterruptedException e)
						{
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						pi.put(noeud, noeud);
						break;// Sinon on pourrait ajouter plusieurs noeuds à la
						      // file
					}
				}
			}
		}
		return pi;
	}

	/**
	 * @param n
	 *            : noeud de départ
	 * @param option
	 *            : si vrai alors parcourir tout le graphe
	 * @param typeParcours
	 *            : 0 pour DFS, 1 pour BFS
	 */
	public void afficheParcours(int typeParcours, int n, boolean option)
	{
		HashMap<Integer, Integer> horloge = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();

		switch (typeParcours)
		{
		case 0:
			pi = DFS(n, option, horloge);
			System.out.println("\n===DFS===");
			break;
		case 1:
			pi = BFS(n, option, horloge);
			System.out.println("\n===BFS===");
			break;

		}
		for (int i : horloge.keySet())
		{
			System.out.print("[" + i + "]" + pi.get(horloge.get(i)) + "->" + horloge.get(i) + " ");
		}
	}

	public boolean acyclicite()
	{
		HashMap<Integer, TreeSet<Integer>> listeAcces = new HashMap<Integer, TreeSet<Integer>>();
		ArrayList<Arc> listeArcs = monGraphe.listeArcs();
		for (Arc monArc : listeArcs)
		{
			int n1 = monArc.getN1();
			int n2 = monArc.getN2();
			if (n1 != n2)
			{
				if (listeAcces.get(n1) == null)
				{
					TreeSet<Integer> aux = new TreeSet<Integer>();
					aux.add(n2);
					listeAcces.put(n1, aux);
				}
				else
				{
					listeAcces.get(n1).add(n2);
				}
			}
		}
		return trouveBoucle(listeAcces);

	}

	private boolean trouveBoucle(HashMap<Integer, TreeSet<Integer>> listeAcces)
	{
		boolean termine = false;
		TreeSet<Integer> acces;
		TreeSet<Integer> temp;
		int tailleAvantModif;
		while (!termine)
		{
			termine = true;
			for (Integer noeud : listeAcces.keySet())
			{
				temp = new TreeSet<Integer>();
				acces = listeAcces.get(noeud);
				tailleAvantModif = acces.size();
				for (Integer noeudAccessible : acces)
				{
					if (listeAcces.get(noeudAccessible) != null)
						temp.addAll(listeAcces.get(noeudAccessible));
				}
				acces.addAll(temp);
				if (acces.contains(noeud))
					return true;
				if (tailleAvantModif != acces.size())
					termine = false;
			}
		}

		return false;
	}

	public boolean connexite()
	{
		HashMap<Integer, Integer> horloge;
		HashMap<Integer, Integer> pi;
		ArrayList<Integer> listeNoeuds = monGraphe.listeNoeuds();
		int nbNoeuds = monGraphe.NombreNoeuds();

		for (Integer noeud : listeNoeuds)
		{
			horloge = new HashMap<Integer, Integer>();
			pi = DFS(noeud, false, horloge);
			if (pi.size() != nbNoeuds)
				return false;
		}
		return true;
	}

	public boolean simple()
	{
		ArrayList<Arc> listeArcs = monGraphe.listeArcs();
		HashMap<Integer, TreeSet<Integer>> chercheNonSimple = new HashMap<Integer, TreeSet<Integer>>();
		int n1;
		int n2;

		for (Arc monArc : listeArcs)
		{
			n1 = monArc.getN1();
			n2 = monArc.getN2();
			if (n1 == n2)
				return false;
			else
				if (chercheNonSimple.get(n1) == null)
				{
					TreeSet<Integer> aux = new TreeSet<Integer>();
					aux.add(n2);
					chercheNonSimple.put(n1, aux);
				}
				else
					if (chercheNonSimple.get(n1).contains(n2))
					{
						return false;
					}
					else
					{
						chercheNonSimple.get(n1).add(n2);
					}
		}
		return true;
	}
}
