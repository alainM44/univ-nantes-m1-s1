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
		i = graphe.ajouterA(3, 8);
		listeId.add(0, i);
		System.out.println(graphe);

		i = graphe.ajouterA(3, 6);
		listeId.add(1, i);
		System.out.println(graphe);

		i = graphe.ajouterA(8, 8);
		listeId.add(2, i);
		System.out.println(graphe);

		i = graphe.ajouterA(6, 3);
		listeId.add(3, i);
		System.out.println(graphe);

		i = graphe.ajouterA(6, 3);
		listeId.add(4, i);
		System.out.println(graphe);

		i = graphe.ajouterA(6, 3);
		listeId.add(5, i);
		System.out.println(graphe);
		
		i = graphe.ajouterA(6, 8);
		listeId.add(6, i);
		System.out.println(graphe);

		

		System.out.println(graphe.listeNoeuds());
		System.out.println(graphe.NombreNoeuds() + " NbNoeuds");
		System.out.println(graphe.NombreArcs() + " NbArcs");
		System.out.println(graphe);
		System.out.println(graphe.listerArcsEntrants(8));
		System.out.println(graphe.listeNoeuds());
		System.out.println(graphe.listeArcs());
		System.out.println(graphe.listerArcsSortants(3));
		System.out.println(graphe.listerPredecesseurs(6));
		System.out.println(graphe.listerSuccesseurs(6));


		

	}
}
