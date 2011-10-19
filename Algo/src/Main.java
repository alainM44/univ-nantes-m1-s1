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
		ListGraph graphe = new ListGraph();
		graphe.ajouterN(0);
		graphe.ajouterN(1);
		graphe.ajouterN(2);
		i = graphe.ajouterA(0, 1);
		listeId.add(0, i);
		i = graphe.ajouterA(0, 2);
		listeId.add(1, i);
		i = graphe.ajouterA(1, 1);
		listeId.add(2, i);
		i = graphe.ajouterA(2, 0);
		listeId.add(3, i);
		i = graphe.ajouterA(2, 0);
		listeId.add(4, i);
		System.out.println(graphe.listeNoeuds().toString());
		graphe.supprimerA(listeId.get(4), 2, 0);
		listeId.remove(4);
		graphe.supprimerN(0);
		System.out.println(graphe.listeNoeuds().toString());
		System.out.println(graphe.nbNoeuds);
		System.out.println(graphe.nbAretes);
		

	}
}
