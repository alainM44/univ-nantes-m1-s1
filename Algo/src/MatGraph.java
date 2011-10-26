import java.util.ArrayList;

import java.util.List;


public class MatGraph extends AbstractGrapheOriente{

	ArrayList2D<Encapsulateur<Boolean>>graph;	
	ArrayList<Encapsulateur<Integer>> tabnoeuds;

	public MatGraph(){
		super();
		graph = new ArrayList2D<Encapsulateur<Boolean>>() ;
	}

	@Override
	public int ajouterA(int n1, int n2) {
		idGenerator++;
		graph.get(n1, n2).ajouterArc(idGenerator);
		//	tabnoeuds.get(n1).setNbArc(n2)
		return idGenerator;
	}

	@Override
	public void ajouterN(int n) {
		//on ajoute une arraylist
		graph.getLine(n).get(n).setValeur(true);
		graph.getLine(n).get(n).setNbArc(0);		
		tabnoeuds.add(new Encapsulateur<Integer>(n));

	}

	@Override
	public ArrayList<Integer> listeArcs() {
		ArrayList<Integer> result = new ArrayList<Integer>();
		int nblignes =graph.getNbLignes();
		int lignesize;
		int listsize;
		for(int i=1;i<=nblignes;i++)
		{
			lignesize=graph.getLine(i).size();
			for(int j=1;i<=lignesize;j++)
			{
				listsize =graph.getLine(i).get(j).getListe().size();
				for(int k=1;i<=listsize;j++)
				{
					result.add(graph.getLine(i).get(j).getListe().get(k));
				}
	
			}
		}

		
		return result;
	}

	@Override
	public ArrayList<Integer> listeNoeuds() {
		ArrayList<Integer> result = new ArrayList<Integer>();
		for(int i=1;i<=tabnoeuds.size();i++)
			result.add(tabnoeuds.get(i).valeur);
			return null;
	}

	@Override
	public ArrayList<Arete> listerArcsEntrants(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Arete> listerArcsSortants(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listerPredecesseurs(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listerSuccesseurs(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void supprimerA(int id, int n1, int n2) {
		// TODO Auto-generated method stub

	}

	@Override
	public void supprimerN(int n) {
		// TODO Auto-generated method stub

	}

	//	public void setNoeud(<Encapsulateur<Boolean>> casemat,Boolean b, int nba){
	//		casemat
	//		
	//	}

}