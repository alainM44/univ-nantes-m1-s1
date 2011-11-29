package Graphe;
import java.util.ArrayList;


public class MatMain {
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		
		
//		MatGraph graph = new MatGraph();
//		graph.ajouterN(1);
//		graph.ajouterN(2);
//		graph.ajouterN(3);
//		graph.ajouterN(4);
//		graph.ajouterN(5);
//		System.out.println(graph);
////		System.out.println(graph.put_tab());
//		
//		graph.supprimerN(2);
//		System.out.println(graph);
//		
//		graph.ajouterA(0,3);
//		graph.ajouterA(0,1);
//		graph.ajouterA(2,3);
//		graph.ajouterA(3,0);
//		graph.ajouterA(2,0);
//		
//		System.out.println(graph);
//		//graph.supprimerA(2, 0, 1);
//		System.out.println(graph);
//		graph.supprimerA(3, 2, 3);
//		System.out.println(graph);
//		System.out.println(graph.listeNoeuds());
//		System.out.println(graph.listerSuccesseurs(1));
//		System.out.println(graph.listerPredecesseurs(1));
//		
//		System.out.println(graph.listerArcsSortants(1));
//		System.out.println(graph.listerArcsEntrants(1));
//		
//		
		
	ArrayList<Integer> listeId = new ArrayList<Integer>();

			int i;
			//GrapheOriente graphe = new ListGraph();
			GrapheOriente graphe = new MatGraph();
			
			graphe.ajouterN(0);
			graphe.ajouterN(1);
			graphe.ajouterN(2);
			graphe.ajouterN(3);
			graphe.ajouterN(4);
			graphe.ajouterN(5);
			//i = graphe.ajouterA(3, 8);
			i = graphe.ajouterA(0, 1,0);
			listeId.add( i);
			System.out.println(graphe);

			i = graphe.ajouterA(1, 2,1);
			listeId.add( i);
			System.out.println(graphe);

			i = graphe.ajouterA(2, 3,2);
			listeId.add( i);
			System.out.println(graphe);

			i = graphe.ajouterA(3, 4,3);
			listeId.add( i);
			System.out.println(graphe);

			i = graphe.ajouterA(4, 1,4);
			listeId.add( i);
			System.out.println(graphe);

			i = graphe.ajouterA(2, 5,5);
			listeId.add( i);
			System.out.println(graphe);
			
			i = graphe.ajouterA(5, 0,6);
			listeId.add( i);
			System.out.println(graphe);
			
			i = graphe.ajouterA(5, 0,7);
			listeId.add( i);
			System.out.println(graphe);
			
//			graphe.supprimerN(4);
//			System.out.println(graphe);
//
//			graphe.ajouterN(4);
//
//			
//			i = graphe.ajouterA(4, 1);
//			listeId.add( i);
//			System.out.println(graphe);
//
//			i = graphe.ajouterA(3, 4);
//			listeId.add( i);
//			System.out.println(graphe);

			TestMonGraphe test = new TestMonGraphe(graphe);
			System.out.println(test.connexite());
			System.out.println(graphe.listeArcs());//TODO listeArc déconne, à refaire
			System.out.println(test.acyclicite());
			System.out.println(test.simple());
//			test.DFS(6, true);
//			try
//			{
//				test.BFS(6, true);
//			} catch (InterruptedException e)
//			{
//				System.out.println("chat");
//				e.printStackTrace();
//			}
		//	System.out.println(test.acyclicite());

		
		
		
		
		
	}

}
