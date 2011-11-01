

public class Benchmark
{

	public static void main(String[] args)
	{
		long mili;
		ListGraph grapheListe10 = new ListGraph();
		ListGraph grapheListe100 = new ListGraph();
		ListGraph grapheListe1000 = new ListGraph();
		
		System.out.println("===CREATION DES NOEUDS===");
		System.out.println("Creation noeuds ListGraph10");
		mili=System.currentTimeMillis();
		creerNoeuds(grapheListe100, 10);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = "+ mili);
		
		System.out.println("Creation noeuds MatGraph10");
		
		System.out.println("Creation noeuds ListGraph100");
		mili=System.currentTimeMillis();
		creerNoeuds(grapheListe100, 1000);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = "+ mili);
		
		System.out.println("Creation noeuds MatGraph100");
		
		System.out.println("Creation noeuds ListGraph1000");
		mili=System.currentTimeMillis();
		creerNoeuds(grapheListe1000, 1000);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = "+ mili);
		
		System.out.println("Creation noeuds MatGraph1000");
		
		System.out.println(grapheListe10.listeNoeuds());//TODO remove
		System.out.println("===CREATION DES ARCS===");
		System.out.println("Creation Arcs ListGraph10");
		mili=System.currentTimeMillis();
		creerArcs(grapheListe10, 10);
		mili = System.currentTimeMillis() - mili;
		
		System.out.println("Creation Arcs MatGraph10");
		System.out.println("Creation Arcs ListGraph100");
		mili=System.currentTimeMillis();
		creerArcs(grapheListe100, 100);
		mili = System.currentTimeMillis() - mili;
		
		System.out.println("Creation Arcs MatGraph100");
		System.out.println("Creation Arcs ListGraph1000");
		mili=System.currentTimeMillis();
		creerArcs(grapheListe1000, 1000);
		mili = System.currentTimeMillis() - mili;
		
		System.out.println("Creation Arcs MatGraph1000");
		
		// TODO grapheMatrice
	}

	public static void creerNoeuds(GrapheOriente graph, int nbNoeuds)
	{
		for (int i = 0; i < nbNoeuds; i++)
		{
			graph.ajouterN(i);
		}
		System.out.println(graph.listeNoeuds());//TODO remove
	}
	
	public static void creerArcs(GrapheOriente graph, int nbNoeuds)
	{
		for (int i = 0; i < nbNoeuds; i++)
		{
			for (int j = i+1; j < nbNoeuds; j++)
			{
				System.out.println(i+" "+j);//TODO remove
				graph.ajouterA(i,j);
			}
		}
	}

}
