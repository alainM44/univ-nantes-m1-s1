package GPS;

import java.util.HashMap;

import Graphe.AbstractGrapheOriente;
import Graphe.Route;
import Graphe.Ville;

public class GPS {
	
	AbstractGrapheOriente graph;
	HashMap<Integer, Ville> villes;
	
	//QUELLE SOLUTION LORSQUE QUE LON A UN RESULTAT NEGATIF?
	public double get_agregat(Route route, int dmax,int imax,double A){
		double result;
		//wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗ imax )
		result=A*route.getLongueur()/dmax-(1-A)*(route.getQualite() + villes.get(route.getN2()).getQualite())/(2*imax);
		return result;
	
	}
	

	

}
