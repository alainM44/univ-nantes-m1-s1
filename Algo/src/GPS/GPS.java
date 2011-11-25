package GPS;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Set;
import Graphe.AbstractGrapheOriente;
import Graphe.ListGraph;
import Graphe.Route;
import Graphe.Ville;

public class GPS
{

	int imax;
	double dmax;
	AbstractGrapheOriente graph;
	HashMap<Integer, Ville> villes;
	HashMap<Integer, Route> routes;

	public GPS(File fichier)
	{
		Integer imaxTemp = new Integer(0);
		Double dmaxTemp = new Double(0);
		graph = new ListGraph();
		villes = new HashMap<Integer, Ville>();
		routes = new HashMap<Integer, Route>();
		Parseur parseur = new Parseur(fichier);
		parseur.parse(graph, villes, routes, dmaxTemp, imaxTemp);
	}

	// QUELLE SOLUTION LORSQUE QUE LON A UN RESULTAT NEGATIF?
	public double get_agregat(Route route, double A)
	{
		double result;
		// wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗
		// imax )
		result = A * route.getLongueur() / dmax - (1 - A)* (route.getQualite() + villes.get(route.getN2()).getQualite())/ (2 * imax);
		System.out.println(result);

		return result;

	}

	public ArrayList<Double> agregation(double A)
	{
		//ArrayList<Route> result = new ArrayList<Route>();
		
		ArrayList<Double> routes_ponderation = new ArrayList<Double>();
		for (int i = 0; i < graph.NombreArcs(); i++)
		{
			routes_ponderation.add(get_agregat(routes.get(i), A));
		}
		System.out.println(routes_ponderation);
		return routes_ponderation;
	}

	// public ArrayList<Route> detour_borne(){
	// ArrayList<Route> result;
	//		
	//		return result;
	//	}




	public  ArrayList<Route>/*??*/BellmanFord(ArrayList<Double> tab_routes)
	{
		ArrayList<Route> PCC= new ArrayList<Route>();
		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
		Set<Integer> PCCkeys;
		
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
		HashMap<Integer, Double> r = new HashMap<Integer, Double>();


		for (Integer noeud : listeNoeud)
		{
			d.put(noeud,Double.MAX_VALUE); //-1 ou l'infini ?
			pi.put(noeud, 0);
		}		
	

		//INIT
		d.put(1,0.0);
		pi.put(1,1);


		for(int villecourante=0; villecourante<graph.NombreNoeuds()-1;villecourante++)
		{
			for(int routecourante=0; routecourante<graph.NombreArcs();routecourante++)
			{
				if (d.get(villecourante)<tab_routes.get(routecourante)+d.get(villecourante))
				{
					d.put(villecourante, tab_routes.get(routecourante)+d.get(villecourante));
					pi.put(routecourante,villecourante);
					r.put(routecourante,tab_routes.get(routecourante));
					System.out.println(tab_routes.get(routecourante));

				}
			}
		}
		
		//VERIFICATION DE CIRCUIT ABSORBANT
//	for(int routecourante=0; routecourante<graph.NombreArcs();routecourante++)
//	{
//		//hum hum
//		if( (d.get(routes.get(routecourante).getN2()) > (d.get(routes.get(routecourante).getN1())+tab_routes.get(routecourante))))
//			return PCC;	
//	
//	}

		PCCkeys = r.keySet();

		// On remplit le resultat
		for (Integer i : PCCkeys)
		{
			PCC.add(routes.get(r.get(i)));	
		}
		return PCC;
		
	}



	// BAD NEWS : DIJKSTRA A REMPLACER PAR BELLMAN FORD
	// PROBLEME AU NIVEAU DES FILES DE PRIORITES
	// DE PLUS LA PONDERATION DE LA FONCTION PEUT RENVOYER DES VALEURS
	// NEGATIVES, IL FAUT DONC UTILISER BELLMAN-FORD
//	public ArrayList<Integer>/* ?? */Dijkstra(ArrayList<Double> tab_routes)
//	{
//		int noeudCourant;
//		ArrayList<Integer> PCC = new ArrayList<Integer>();
//		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
//		Set<Integer> PCCkeys;
//		Set<Integer> routeskeyx;
//		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
//		PriorityQueue<Integer> file = new PriorityQueue<Integer>();
//		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
//
//		for (Integer noeud : listeNoeud)
//		{
//			d.put(noeud, -1.0); // -1 ou l'infini ?
//			pi.put(noeud, 0);
//		}
//		routeskeyx = pi.keySet();
//		// on remplie la file
//		for (Integer route : routeskeyx)
//		{
//			file.add(route);
//		}
//		// INIT
//		d.put(1, 0.0);
//		pi.put(1, 1);
//
//		while (!file.isEmpty())
//		{
//			noeudCourant = file.poll();
//			for (Integer voisin : graph.listerSuccesseurs(noeudCourant)) // 
//			{
//				if (d.get(noeudCourant) < tab_routes.get(voisin)
//						+ d.get(noeudCourant))
//				{
//					d.put(noeudCourant, tab_routes.get(voisin)
//							+ d.get(noeudCourant));
//					pi.put(voisin, noeudCourant);
//
//				}
//			}
//		}
//		PCCkeys = pi.keySet();
//
//		// On remplit le resultat
//		for (Integer i : PCCkeys)
//		{
//			PCC.add(pi.get(i));
//		}
//		return PCC;
//	}

	public void put_itineraire(ArrayList<Route> PCC)
	{
		String itineraire = new String("Ville Départ : ");
		String ville = new String("");
		String route = new String("");
		String integer = new String("");
		// l’itinéraire sera
		// affiché en donnant la séquence des routes empruntées et des lieux
		// traversés ; sa longueur et son
		// intérêt touristique seront indiqués, ainsi que le temps mis pour le
		// calculer.
		itineraire += "Ville départ :";
		ville += getville(villes.get(PCC.get(1)));
		route += getroute(PCC.get(1));
		itineraire += ville;
		itineraire += '\n';
		itineraire += route;
		itineraire += '\n';
		for (int i = 2; i < PCC.size() - 1; i++)
		{
			ville += getville(villes.get(PCC.get(i)));
			route += getroute(PCC.get(i));
			itineraire += '\n';
		}
		itineraire += "Ville départ :";
		ville += getville(villes.get(PCC.get(PCC.size())));
		route += getroute(PCC.get(PCC.size()));

		System.out.println(itineraire);
	}

	public String getville(Ville ville)
	{
		String result = new String("");
		result += ville.getNom();
		result += " ";
		result += ville.getQualite();
		return result;
	}

	public String getroute(Route route)
	{
		String result = new String("");
		result += route.getNom();
		result += " ";
		result += route.getQualite();
		return result;
	}

	public ArrayList<Route> detourBorne (double K)
	{
		
		return null;
		
	}
	
}
