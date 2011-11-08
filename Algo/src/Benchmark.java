import java.util.ArrayList;

public class Benchmark
{

	public static void bench(GrapheOriente graphe, int n)
	{
		long mili;
		boolean verif;
		ArrayList<Integer> listeId = new ArrayList<Integer>();


		System.out.println("===CREATION DES " + n + " NOEUDS===");

		mili = System.currentTimeMillis();
		creerNoeuds(graphe, n);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);

		System.out.println("===CREATION DES " + ((n * n + n) / 2) + " ARCS===");

		mili = System.currentTimeMillis();
		listeId = creerArcs(graphe, n);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);

		System.out.println("===LISTE DES NOEUDS===");

		mili = System.currentTimeMillis();
		ArrayList<Integer> listeNoeuds = graphe.listeNoeuds();
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);
		System.out.println(listeNoeuds);

		System.out.println("===LISTE DES ARCS===");

		mili = System.currentTimeMillis();
		ArrayList<Arc> listeArcs = graphe.listeArcs();
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);

		TestMonGraphe test = new TestMonGraphe(graphe);

//		System.out.println("===ACYCLIQUE===");
//
//		mili = System.currentTimeMillis();
//		verif = test.acyclicite();
//		mili = System.currentTimeMillis() - mili;
//		System.out.println(verif);
//		System.out.println("temps = " + mili);

		System.out.println("===SIMPLE===");

		mili = System.currentTimeMillis();
		verif = test.simple();
		mili = System.currentTimeMillis() - mili;
		System.out.println(verif);
		System.out.println("temps = " + mili);

		System.out.println("===CONNEXE===");

		mili = System.currentTimeMillis();
		verif = test.connexite();
		mili = System.currentTimeMillis() - mili;
		System.out.println(verif);
		System.out.println("temps = " + mili);

		System.out.println("===SUCCESSEURS===");
		mili = System.currentTimeMillis();
		listeNoeuds = graphe.listerSuccesseurs(0);
		mili = System.currentTimeMillis() - mili;
//		System.out.println(listeNoeuds);
		System.out.println("temps = " + mili);

		System.out.println("===PREDECESSEURS===");
		mili = System.currentTimeMillis();
		listeNoeuds = graphe.listerPredecesseurs(n-1);
		mili = System.currentTimeMillis() - mili;
//		System.out.println(listeNoeuds);
		System.out.println("temps = " + mili);
		
		System.out.println("===ARCS SORTANTS===");
		mili = System.currentTimeMillis();
		listeArcs = graphe.listerArcsSortants(0);
		mili = System.currentTimeMillis() - mili;
//		System.out.println(listeArcs);
		System.out.println("temps = " + mili);
		
		System.out.println("===ARCS ENTRANTS===");
		mili = System.currentTimeMillis();
		listeArcs = graphe.listerArcsEntrants(n-1);
		mili = System.currentTimeMillis() - mili;
//		System.out.println(listeArcs);
		System.out.println("temps = " + mili);

		mili = System.currentTimeMillis();
		test.afficheParcours(0, 0, true);
		mili = System.currentTimeMillis() - mili;
		System.out.println("\ntemps = " + mili);

		mili = System.currentTimeMillis();
		test.afficheParcours(1, 0, true);
		mili = System.currentTimeMillis() - mili;
		System.out.println("\ntemps = " + mili);

		System.out.println("===SUPPRESSION DES ARCS===");

		mili = System.currentTimeMillis();
		supprimerArcs(graphe, n, listeId);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);

		System.out.println("Graphe en cours de création. Veuillez patienter...");

		listeId = creerArcs(graphe, n);

		System.out.println("===SUPPRESSION DES NOEUDS===");

		mili = System.currentTimeMillis();
		supprimerNoeuds(graphe, n);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);

	}

	private static void creerNoeuds(GrapheOriente graph, int nbNoeuds)
	{
		for (int i = 0; i < nbNoeuds; i++)
		{
			graph.ajouterN(i);
		}
	}

	private static ArrayList<Integer> creerArcs(GrapheOriente graph, int nbNoeuds)
	{
		ArrayList<Integer> listeId = new ArrayList<Integer>();
		for (int i = 0; i < nbNoeuds; i++)
		{
			for (int j = i + 1; j < nbNoeuds; j++)
			{
				listeId.add(graph.ajouterA(i, j));
			}
		}
		return listeId;
	}

	private static void supprimerNoeuds(GrapheOriente graph, int nbNoeuds)
	{
		for (int i = 0; i < nbNoeuds; i++)
		{
			graph.supprimerN(i);
		}
	}

	private static void supprimerArcs(GrapheOriente graph, int nbNoeuds, ArrayList<Integer> listeId)
	{
		int k = 0;
		for (int i = 0; i < nbNoeuds; i++)
		{
			for (int j = i + 1; j < nbNoeuds; j++)
			{
				graph.supprimerA(listeId.get(k), i, j);
			}
		}
	}
}
