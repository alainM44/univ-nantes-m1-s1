import java.util.ArrayList;
import java.util.List;

public class ListGraph extends AbstractGrapheOriente {

	// ArrayList pour le moment
	ArrayList<ArrayList<conteneurGraph<Integer>>> listeNoeuds;

	ListGraph() {
		listeNoeuds = new ArrayList<ArrayList<conteneurGraph<Integer>>>();
	}

	@Override
	public void ajouterA(int id, int n1, int n2) {
		conteneurGraph<Integer> noeudArrivee;
		ArrayList<conteneurGraph<Integer>> listeNoeudsArrivee;
		noeudArrivee = listeNoeuds.get(n1).get(n2);
		listeNoeudsArrivee = listeNoeuds.get(n1);
		noeudArrivee = listeNoeudsArrivee.get(n2);
		if (noeudArrivee != null) {
			noeudArrivee.ajouterArete(id);
		} 
		else {
			listeNoeudsArrivee.add(new conteneurGraph<Integer>(n2, id));
		}
	}

	@Override
	public void ajouterN(int n) {

	}

	@Override
	public List<Integer> listerArcsEntrants(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerArcsSortants(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerPredecesseurs(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerSuccesseurs(int n) {
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

}