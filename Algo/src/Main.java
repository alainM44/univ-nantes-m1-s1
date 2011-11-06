import java.util.ArrayList;

public class Main
{

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		ArrayList<Integer> listeId = new ArrayList<Integer>();

		int i;
		GrapheOriente graphe = new ListGraph();

//		graphe.ajouterN(3);
//		graphe.ajouterN(8);
//		graphe.ajouterN(6);
//		graphe.ajouterN(5);
//		graphe.ajouterN(4);
//		graphe.ajouterN(7);
//		i = graphe.ajouterA(3, 8);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		i = graphe.ajouterA(4, 3);
//		listeId.add(i);
//		System.out.println(graphe);
//		
//		i = graphe.ajouterA(8, 6);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		i = graphe.ajouterA(6, 5);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		i = graphe.ajouterA(6, 4);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		i = graphe.ajouterA(5, 7);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		i = graphe.ajouterA(7, 8);
//		listeId.add(i);
//		System.out.println(graphe);
//
//		TestMonGraphe test = new TestMonGraphe(graphe);
//		test.afficheParcours(0, 6, true);
//		System.out.println();
//		test.afficheParcours(1, 6, true);
//		System.out.println();
//
//
//		System.out.println("\n===Acyclicité===\n" + test.acyclicite());
//		System.out.println("\n===Connexité===\n" + test.connexite());
//		System.out.println("\n===Simple===\n" + test.simple());
		
		Benchmark.bench(graphe, 2000);

	}
}
