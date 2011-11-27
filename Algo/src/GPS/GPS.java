package GPS;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Set;
import Graphe.AbstractGrapheOriente;
import Graphe.Arc;
import Graphe.ListGraph;
import Graphe.MatGraph;
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
		ArrayList<Object> max = new ArrayList<Object>();
		//graph = new ListGraph();
		graph = new MatGraph();

		villes = new HashMap<Integer, Ville>();
		routes = new HashMap<Integer, Route>();
		Parseur parseur = new Parseur(fichier);
		parseur.parse(graph, villes, routes, max);
		imax = (Integer) max.get(1);
		dmax = (Double) max.get(0);
	}
	// QUELLE SOLUTION LORSQUE QUE LON A UN RESULTAT NEGATIF?
	public double get_agregat(Route route, double A)
	{
		double result;
		// wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗
		// imax )
		result = A * route.getLongueur() / dmax - (1 - A)
		* (route.getQualite() + villes.get(route.getN2()).getQualite())
		/ (2 * imax);
		//		System.out.println(result);

		return result;

	}
	public ArrayList<Double> agregation(double A)
	{
		// ArrayList<Route> result = new ArrayList<Route>();

		ArrayList<Double> routes_ponderation = new ArrayList<Double>();
		for (int i = 0; i < graph.NombreArcs(); i++)
		{
			routes_ponderation.add(get_agregat(routes.get(i), A));
		}
		//		System.out.println(routes_ponderation);
		return routes_ponderation;
	}
	public ArrayList<Route>/* ?? */BellmanFord(ArrayList<Double> tab_routes)
	{
		ArrayList<Route> PCC = new ArrayList<Route>();
		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
		Set<Integer> PCCkeys;
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
		//Pour stocker la route du PCC permettant d'acceder au noeud référencé par sa la clef de cette route
		HashMap<Integer, Integer> r = new HashMap<Integer, Integer>();

		for (Integer noeud : listeNoeud)
		{
			d.put(noeud, Double.MAX_VALUE); // -1 ou l'infini ?
			pi.put(noeud, -1);
		}
		// INIT
		d.put(0, 0.0);
		pi.put(0, 0);
		puthd(d);
		puthi(pi);
		for (int villecourante = 0; villecourante < graph.NombreNoeuds() - 1; villecourante++)
		{
			for (int routecourante = 0; routecourante < graph.NombreArcs(); routecourante++)
			{
				//si d[v]>d[u]+w(u v)
				if (d.get(routes.get(routecourante).getN2()) > (d.get(routes.get(routecourante).getN1())
						+ tab_routes.get(routecourante)) &&  (d.get(routes.get(routecourante).getN2()) != null))
				{
					//d[v]<- d[u]+w(u v)
					d.put(routes.get(routecourante).getN2(), tab_routes.get(routecourante)
							+(d.get(routes.get(routecourante).getN1())));
					//π[v]<- u
					pi.put(routes.get(routecourante).getN2(),routes.get(routecourante).getN1());
					//route reliant π[v]<-u 
					r.put(routes.get(routecourante).getN2(), routecourante);
					//System.out.println("MAJ");

				}
			}
		}
		// VERIFICATION DE CIRCUIT ABSORBANT
		for (int routecourante = 0; routecourante < graph.NombreArcs(); routecourante++)
		{
			//si d[v]>d[u]+w(u v)
			if (d.get(routes.get(routecourante).getN2()) > (d.get(routes.get(routecourante).getN1())
					+ tab_routes.get(routecourante)))
			{
				//CIRCUIT ABSORBANT
				return PCC; //VIDE

			}
		}
		// }
		puthd(d);
		puthi(pi);
		PCCkeys = pi.keySet();
		PCCkeys = r.keySet();

		// On remplit le resultat
		for (Integer i : PCCkeys)
		{
			PCC.add(routes.get(r.get(i)));
			//		System.out.println(routes.get(r.get(i)));

		}
		return PCC;

	}

	public ArrayList<Route>/* ?? */BellmanFord(ArrayList<Double> tab_routes,
			int ville_dep, int ville_a)
			{
		ArrayList<Route> PCC = new ArrayList<Route>();
		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
		Set<Integer> PCCkeys;
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
		//Pour stocker la route du PCC permettant d'acceder au noeud référencé par sa la clef de cette route
		HashMap<Integer, Integer> r = new HashMap<Integer, Integer>();

		for (Integer noeud : listeNoeud)
		{
			d.put(noeud, Double.MAX_VALUE); // -1 ou l'infini ?
			pi.put(noeud, -1);
		}
		// INIT
		d.put(ville_dep, 0.0);
		pi.put(ville_dep, ville_dep);
		puthd(d);
		puthi(pi);
		for (int villecourante = 0; villecourante < graph.NombreNoeuds() - 1; villecourante++)
		{
			for (int routecourante = 0; routecourante < graph.NombreArcs(); routecourante++)
			{
				//si d[v]>d[u]+w(u v)
				if (d.get(routes.get(routecourante).getN2()) > (d.get(routes.get(routecourante).getN1())
						+ tab_routes.get(routecourante)))
				{
					//d[v]<- d[u]+w(u v)
					d.put(routes.get(routecourante).getN2(), tab_routes.get(routecourante)
							+(d.get(routes.get(routecourante).getN1())));
					//π[v]<- u
					pi.put(routes.get(routecourante).getN2(),routes.get(routecourante).getN1());
					//route reliant π[v]<-u 
					r.put(routes.get(routecourante).getN2(), routecourante);
					//System.out.println("MAJ");

				}
			}
		}
		// VERIFICATION DE CIRCUIT ABSORBANT
		for (int routecourante = 0; routecourante < graph.NombreArcs(); routecourante++)
		{
			//si d[v]>d[u]+w(u v)
			if (d.get(routes.get(routecourante).getN2()) > (d.get(routes.get(routecourante).getN1())
					+ tab_routes.get(routecourante)) &&  (d.get(routes.get(routecourante).getN2()) != null))
			{
				//CIRCUIT ABSORBANT
				return PCC; //VIDE

			}
		}
		// }
		puthd(d);
		puthi(pi);
		PCCkeys = pi.keySet();

		PCCkeys = r.keySet();

		// On remplit le resultat
		if (ville_a<ville_dep)
		{
			for (Integer i : PCCkeys)
			{
				if (i.compareTo(ville_a)<=0)
					PCC.add(routes.get(r.get(i)));//		System.out.println(routes.get(r.get(i)));

			}
		}
		else
		{
			for (Integer i : PCCkeys)
			{
				if (i.compareTo(ville_dep)>0 && i.compareTo(ville_a)<=0)
					PCC.add(routes.get(r.get(i)));


			}
		}

		return PCC;

			}

	// VERIFIER LA MOY DES ETOILES
	public void put_itineraire(ArrayList<Route> PCC)
	{
		String itineraire = new String("Ville Départ : ");
		String ville = new String("");
		String route = new String("");
		int etoiles=0;
		double longueur=0;
		double l;
		int cpt=0;
//		System.out.println(PCC);
		// l’itinéraire sera
		// affiché en donnant la séquence des routes empruntées et des lieux
		// traversés ; sa longueur et son
		// intérêt touristique seront indiqués, ainsi que le temps mis pour le
		// calculer.
		ville = getville(villes.get(PCC.get(0).getN1()));
		itineraire += ville;
		itineraire += '\n';
		route += getroute(PCC.get(0));
		l=PCC.get(0).getLongueur();
		longueur+=l;
		ville = getville(villes.get(PCC.get(0).getN2()));
		itineraire += "route "+route+"vers :"+ville +" longeueur : "+l+"\n";
		etoiles+=villes.get(PCC.get(0).getN1()).getQualite()+PCC.get(0).getQualite()+villes.get(PCC.get(0).getN2()).getQualite();
		cpt+=3;
		for (int i = 1; i <= PCC.size() -1; i++)
		{
			l=PCC.get(i).getLongueur();
			longueur+=l;
			route = getroute(PCC.get(i));
			ville = getville(villes.get(PCC.get(i).getN2()));
			etoiles+=PCC.get(i).getQualite()+villes.get(PCC.get(i).getN2()).getQualite();
			cpt+=2;
			itineraire += "route "+route+"vers :"+ville +" longeueur : "+l+"\n";
		}

		//etoiles+=PCC.get(PCC.size()-1).getQualite();
		itineraire += "Ville arrivée :";
		ville = getville(villes.get(PCC.get(PCC.size() -1).getN2()));
		itineraire += ville;
		//		System.out.println(etoiles);
		//		System.out.println(cpt);
			System.out.println(itineraire);
		System.out.println("Longueur de l'itinéraire : "+longueur);
		System.out.print("Intérêt touristique: ");
		for(int i =1;i<=(etoiles/cpt);i++)
			System.out.print("*");

	}

	public String getville(Ville ville)
	{
		String result = new String("");
		result += ville.getNom();
		result += " ";
		result += getetoiles(ville);

		return result;

	}
	public String getroute(Route route)
	{
		String result = new String("");
		result += route.getNom();
		result += " ";
		result += getetoiles(route);
		return result;
	}
	public String getetoiles(Ville ville)
	{
		String result = new String("");
		for(int i=1;i<=ville.getQualite();i++)
			result += "*";
		return result;
	}
	public String getetoiles(Route route)
	{
		String result = new String("");
		for(int i=1;i<=route.getQualite();i++)
			result += "*";
		return result;
	}
	public LinkedList<Route> detourBorne(double K, int depart, int arrivee)
	{
		ArrayList<Double> routes_ponderation = new ArrayList<Double>();
		ArrayList<Route> PCC = null;
		double bornePCC = 0;

		for (int i = 0; i < routes.size(); i++)
		{
			routes_ponderation.add(routes.get(i).getLongueur());
		}

		PCC = BellmanFord(routes_ponderation);

		for (Route route : PCC)
		{
			bornePCC += route.getLongueur();
		}
		bornePCC *= K;

		return detourBorneIter(bornePCC, depart, arrivee);

	}
	public LinkedList<Route> detourBorneIter(double bornePCC, int depart,
			int arrivee)
			{
		LinkedList<Route> cheminCourant = new LinkedList<Route>();
		LinkedList<Route> meilleurChemin = new LinkedList<Route>();
		HashMap<Integer, Integer> tabCouleurs = new HashMap<Integer, Integer>();
		return detourBorneIter(cheminCourant, meilleurChemin, tabCouleurs,
				bornePCC, depart, arrivee, 0, 0, 0);
			}
	@SuppressWarnings("unchecked")
	public LinkedList<Route> detourBorneIter(LinkedList<Route> cheminCourant,
			LinkedList<Route> meilleurChemin,
			HashMap<Integer, Integer> tabCouleurs, double bornePCC, int depart,
			int arrivee, double somme, int qualiteCumule, int qualiteMax)
			{
		if (depart == arrivee && qualiteMax < qualiteCumule)
		{
			meilleurChemin = (LinkedList<Route>) cheminCourant.clone();
		}
		else
		{
			ArrayList<Arc> routesSuivantes;
			int id;
			int ville;
			double longueur;
			int qualite;
			tabCouleurs.put(depart, 1);
			routesSuivantes = graph.listerArcsSortants(depart);
			for (Arc routeSuivante : routesSuivantes)
			{
				ville = routeSuivante.getN1();
				id = routeSuivante.getId();
				longueur = routes.get(id).getLongueur();
				qualite = routes.get(id).getQualite()
				+ villes.get(ville).getQualite();
				if ((tabCouleurs.get(ville) == 0 || tabCouleurs.get(ville) == null)
						&& somme + longueur < bornePCC)
				{
					cheminCourant.add(routes.get(id));
					detourBorneIter(cheminCourant, meilleurChemin, tabCouleurs,
							bornePCC, ville, arrivee, somme + longueur,
							qualiteCumule + qualite, qualiteMax);
					cheminCourant.removeLast();// File
				}
			}

		}

		return meilleurChemin;
			}
	//	AFFICHAGE DE HASHMAP PR DEBUG
	public void puthd (HashMap<Integer, Double>h)
	{
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys)
		{

			System.out.print(h.get(i));
		}
		System.out.println("]");
	}
	public void puthi (HashMap<Integer, Integer>h)
	{
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys)
		{

			System.out.print(h.get(i));


		}
		System.out.println("]");
	}
	public void puthr (HashMap<Integer, Route>h)
	{
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys)
		{System.out.print(h.get(i));}
		System.out.println("]");
	}
	// BAD NEWS : DIJKSTRA A REMPLACER PAR BELLMAN FORD
	// PROBLEME AU NIVEAU DES FILES DE PRIORITES
	// DE PLUS LA PONDERATION DE LA FONCTION PEUT RENVOYER DES VALEURS
	// NEGATIVES, IL FAUT DONC UTILISER BELLMAN-FORD
	// public ArrayList<Integer>/* ?? */Dijkstra(ArrayList<Double> tab_routes)
	// {
	// int noeudCourant;
	// ArrayList<Integer> PCC = new ArrayList<Integer>();
	// ArrayList<Integer> listeNoeud = graph.listeNoeuds();
	// Set<Integer> PCCkeys;
	// Set<Integer> routeskeyx;
	// HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
	// PriorityQueue<Integer> file = new PriorityQueue<Integer>();
	// HashMap<Integer, Double> d = new HashMap<Integer, Double>();
	//
	// for (Integer noeud : listeNoeud)
	// {
	// d.put(noeud, -1.0); // -1 ou l'infini ?
	// pi.put(noeud, 0);
	// }
	// routeskeyx = pi.keySet();
	// // on remplie la file
	// for (Integer route : routeskeyx)
	// {
	// file.add(route);
	// }
	// // INIT
	// d.put(1, 0.0);
	// pi.put(1, 1);
	//
	// while (!file.isEmpty())
	// {
	// noeudCourant = file.poll();
	// for (Integer voisin : graph.listerSuccesseurs(noeudCourant)) //
	// {
	// if (d.get(noeudCourant) < tab_routes.get(voisin)
	// + d.get(noeudCourant))
	// {
	// d.put(noeudCourant, tab_routes.get(voisin)
	// + d.get(noeudCourant));
	// pi.put(voisin, noeudCourant);
	//
	// }
	// }
	// }
	// PCCkeys = pi.keySet();
	//
	// // On remplit le resultat
	// for (Integer i : PCCkeys)
	// {
	// PCC.add(pi.get(i));
	// }
	// return PCC;
	// }

}
