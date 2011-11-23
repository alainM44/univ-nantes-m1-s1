package GPS;

import java.util.ArrayList;
import java.util.HashMap;
import Graphe.AbstractGrapheOriente;
import Graphe.Route;
import Graphe.Ville;

public class GPS {

	AbstractGrapheOriente graph;
	HashMap<Integer, Ville> villes;

	//QUELLE SOLUTION LORSQUE QUE LON A UN RESULTAT NEGATIF?
	public double get_agregat(Route route, float dmax,float imax,double A){
		double result;
		//wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗ imax )
		result=A*route.getLongueur()/dmax-(1-A)*(route.getQualite() + villes.get(route.getN2()).getQualite())/(2*imax);
		return result;

	}

	public void agregation(){


	}

	public void detour_borne(){

	}

	public void put_itineraire(ArrayList<Route> PCC){
		String itineraire = new String("Ville Départ : ");
		String ville = new String("");
		String route = new String("");
		String interer = new String("");
		//		l’itinéraire sera
		//		affiché en donnant la séquence des routes empruntées et des lieux traversés ; sa longueur et son
		//		intérêt touristique seront indiqués, ainsi que le temps mis pour le calculer.
		itineraire+="Ville départ :";
		ville+=getville(villes.get(PCC.get(1)));
		route+=getroute(PCC.get(1));
		itineraire+=ville;
		itineraire+='\n';
		itineraire+=route;
		itineraire+='\n';
		for(int i =2;i<PCC.size()-1;i++)
		{
			ville+=getville(villes.get(PCC.get(i)));
			route+=getroute(PCC.get(i));
			itineraire+='\n';
		}
		itineraire+="Ville départ :";
		ville+=getville(villes.get(PCC.get(PCC.size())));
		route+=getroute(PCC.get(PCC.size()));

		System.out.println(itineraire);
	}

	public String getville(Ville ville){
		String result = new String("");
		result+=ville.getNom(); 
		result+=" "; 
		result+=ville.getQualite(); 
		return result;
	}
	public String getroute(Route route){
		String result = new String("");
		result+=route.getNom();
		result+=" "; 
		result+=route.getQualite(); 
		return result;
	}

}
