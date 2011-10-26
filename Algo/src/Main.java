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
		
		graphe.ajouterN(3);
		graphe.ajouterN(8);
		graphe.ajouterN(6);
		graphe.ajouterN(5);
		graphe.ajouterN(4);
		i = graphe.ajouterA(3, 8);
		listeId.add( i);
		System.out.println(graphe);




		
		i = graphe.ajouterA(6, 8);
		listeId.add( i);
		System.out.println(graphe);
		
		i = graphe.ajouterA(3, 4);
		listeId.add( i);
		System.out.println(graphe);
		
		i = graphe.ajouterA(4, 6);
		listeId.add( i);
		System.out.println(graphe);

		TestMonGraphe test = new TestMonGraphe(graphe);
		test.DFS(6, true);
		try
		{
			test.BFS(6, true);
		} catch (InterruptedException e)
		{
			System.out.println("chat");
			e.printStackTrace();
		}
		System.out.println(test.acyclicite());

	}
}
