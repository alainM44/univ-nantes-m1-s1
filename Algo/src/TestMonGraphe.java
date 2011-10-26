import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.concurrent.ArrayBlockingQueue;

/*
 * La classe va appliquer les différents algorithmes demandés
 * peut-être aussi les benchmarks
 */
public class TestMonGraphe
{
	GrapheOriente monGraphe;
//	HashMap<Integer, Integer> piDFS;
//	HashMap<Integer, Integer> piBFS;
//	HashMap<Integer, Integer> dDFS = new HashMap<Integer, Integer>();
//	HashMap<Integer, Integer> dBFS = new HashMap<Integer, Integer>();

	public TestMonGraphe(GrapheOriente graphe)
	{
		monGraphe = graphe;
	}

	/*
	 * @param n : noeud de départ, option : si vrai alors parcourir tout le
	 * graphe
	 */
	public void DFS(int n, boolean option)
	{
		int temps = 0;
		ArrayList<Integer> listeNoeud = monGraphe.listeNoeuds();
		// 0 est la couleur blanche, 1 la couleur grise, 2 la couleur noire
		HashMap<Integer, Integer> couleur = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> d = new HashMap<Integer, Integer>();

		for (Integer noeud : listeNoeud)
		{
			couleur.put(noeud, 0);
		}

		pi.put(n, n);
		temps = Visiter(n, temps, couleur, pi, d);

		if (option)
		{
			for (Integer noeud : listeNoeud)
			{
				if (couleur.get(noeud) == 0)
				{
					pi.put(noeud, noeud);
					temps = Visiter(noeud, temps, couleur, pi, d);
				}
			}
		}
		System.out.println("\n===DFS===");

		for (int i : d.keySet())
		{
			System.out.print("[" + i + "]" + pi.get(d.get(i)) + "->" + d.get(i)
					+ " ");
		}
	}

	private int Visiter(int n, int temps, HashMap<Integer, Integer> couleur,
			HashMap<Integer, Integer> pi, HashMap<Integer, Integer> d)
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

	public void BFS(int n, boolean option) throws InterruptedException
	{
		int temps = 0;
		int noeudCourant;
		ArrayList<Integer> listeNoeud = monGraphe.listeNoeuds();
		// 0 est la couleur blanche, 1 la couleur grise, 2 la couleur noire
		HashMap<Integer, Integer> couleur = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> d = new HashMap<Integer, Integer>();
		ArrayBlockingQueue<Integer> file = new ArrayBlockingQueue<Integer>(
				monGraphe.NombreNoeuds());

		for (Integer noeud : listeNoeud)
		{
			couleur.put(noeud, 0);
		}

		file.put(n);
		pi.put(n, n);
		while (!file.isEmpty())
		{
			noeudCourant = file.poll();
			d.put(temps, noeudCourant);
			temps++;
			for (Integer voisin : monGraphe.listerSuccesseurs(noeudCourant))
			{
				if (couleur.get(voisin) == 0)
				{
					couleur.put(voisin, 1);
					pi.put(voisin, noeudCourant);
					file.put(voisin);
				}
			}
			couleur.put(noeudCourant, 2);
			if (option && file.isEmpty())
			{
				for (Integer noeud : listeNoeud)
				{
					if (couleur.get(noeud) == 0)
					{
						file.put(noeud);
						pi.put(noeud, noeud);
						break;//Sinon on pourrait ajouter plusieurs noeuds à la file
					}
				}
			}
		}

		System.out.println("\n===BFS===");
		for (int i : d.keySet())
		{
			System.out.print("[" + i + "]" + pi.get(d.get(i)) + "->" + d.get(i)
					+ " ");
		}
	}

	public boolean acyclicite()
	{
		HashMap<Integer, TreeSet<Integer>> listeAcces = new HashMap<Integer, TreeSet<Integer>>();
		ArrayList<Arc> listeArcs = monGraphe.listeArcs();
		for(Arc monArc : listeArcs)
		{
			int n1 = monArc.getN1();
			int n2 = monArc.getN2();
			if (listeAcces.get(n1) ==null)
			{
				TreeSet<Integer> aux = new TreeSet<Integer>();
				aux.add(n2);
				listeAcces.put(n1, aux);
			}
			else
			{
				listeAcces.get(n1).add(2);
			}
			//a refaire
			for(Integer noeud : listeAcces.keySet())
			{
				if(listeAcces.get(noeud).contains(noeud));
				return true;
			}
		}
		return false;
		
	}

	
}
