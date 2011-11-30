package GPS;

import java.io.File;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import javax.xml.crypto.dsig.spec.HMACParameterSpec;

import Graphe.AbstractGrapheOriente;
import Graphe.Arc;
import Graphe.ListGraph;
import Graphe.MatGraph;

public class GPS {

	int imax;
	double dmax;
	AbstractGrapheOriente graph;
	HashMap<Integer, Ville> villes;
	HashMap<Integer, Route> routes;
	HashMap<String, Integer> annuaireInverse;

	public GPS(File fichier) {
		ArrayList<Object> max = new ArrayList<Object>();
		// graph = new ListGraph();
		graph = new ListGraph();
		villes = new HashMap<Integer, Ville>();
		routes = new HashMap<Integer, Route>();
		Parseur parseur = new Parseur(fichier);
		annuaireInverse = parseur.parse(graph, villes, routes, max);
		imax = (Integer) max.get(1);
		dmax = (Double) max.get(0);
	}

	public GPS(File fichier, String implementation) {
		villes = new HashMap<Integer, Ville>();
		routes = new HashMap<Integer, Route>();
		if (implementation.compareTo("l") == 0) {
			graph = new ListGraph();
		} else if (implementation.compareTo("m") == 0) {
			graph = new MatGraph();
		}
		ArrayList<Object> max = new ArrayList<Object>();

		Parseur parseur = new Parseur(fichier);
		parseur.parse(graph, villes, routes, max);
		imax = (Integer) max.get(1);
		dmax = (Double) max.get(0);

	}

	public double get_agregat(Route route, double A) {
		double result;
		// wA (u → v) = A ∗ d(u → v)/dmax − (1 − A) ∗ (i(u → v) + i(v))/(2 ∗
		// imax )
		result = A * route.getLongueur() / dmax - (1 - A)
				* (route.getQualite() + villes.get(route.getN2()).getQualite())
				/ (2 * imax);
		return result;

	}

	public ArrayList<Double> agregation(double A) {
		ArrayList<Arc> listearcs = new ArrayList<Arc>();
		listearcs = graph.listeArcs();
		ArrayList<Double> routes_ponderation = new ArrayList<Double>();
		for (int i = 0; i < graph.NombreArcs(); i++) {
			routes_ponderation.add(get_agregat(routes.get(listearcs.get(i)
					.getId()), A));
		}
		// System.out.println(routes_ponderation);
		return routes_ponderation;
	}

	/**
	 * 
	 * @param tab_routes
	 *            La table des pondération indicé par l'id des routes
	 * @return Plus court chemin selon la methode d'agrégation
	 */
	public ArrayList<Route> BellmanFord(ArrayList<Double> tab_routes) {
		ArrayList<Route> result = new ArrayList<Route>();
		ArrayList<Route> PCC = new ArrayList<Route>();
		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
		// Pour stocker la route du PCC permettant d'acceder au noeud référencé
		// par sa la clef de cette route
		HashMap<Integer, Integer> r = new HashMap<Integer, Integer>();

		// INITIALISATION DES TABS
		for (Integer noeud : listeNoeud) {
			d.put(noeud, Double.MAX_VALUE);
			pi.put(noeud, -1);
		}
		d.put(0, 0.0);
		pi.put(0, 0);

		for (int villecourante = 0; villecourante < graph.NombreNoeuds() - 1; villecourante++) {

			for (Arc arc : graph.listeArcs()) {
				// si d[v]>d[u]+w(u v)

				if (d.get(arc.getN2()) > (d.get(arc.getN1()) + tab_routes
						.get(arc.getId()))
						&& (d.get(arc.getN2()) != null)) {
					// d[v]<- d[u]+w(u v)
					d.put(arc.getN2(), tab_routes.get(arc.getId())
							+ (d.get(arc.getN1())));
					// π[v]<- u
					pi.put(arc.getN2(), arc.getN1());
					// route reliant π[v]<-u
					r.put(arc.getN2(), arc.getId());
					// System.out.println("MAJ");
				}
			}
		}
		// VERIFICATION DE CIRCUIT ABSORBANT

		for (Arc arc : graph.listeArcs()) {
			// si d[v]>d[u]+w(u v)
			if (d.get(arc.getN2()) > (d.get(arc.getN1()) + tab_routes.get(arc
					.getId()))) {
				// CIRCUIT ABSORBANT
				return PCC; // VIDE

			}
		}
		Set<Integer> PCCkeys;
		PCCkeys = pi.keySet();
		PCCkeys = r.keySet();
		Integer ville = graph.NombreNoeuds() - 1;
		while (ville != 0) {
			Route tmp;
			tmp = routes.get(r.get(ville));
			PCC.add(tmp);
			ville = tmp.getN1();
		}
		// On inverse le resultat
		for (int i = PCC.size() - 1; i >= 0; i--)
			result.add(PCC.get(i));
		return result;

	}

	/**
	 * 
	 * @param tab_routes
	 *            La table des pondération indicé par l'id des routes
	 * @param ville_dep
	 *            id de la ville de départ
	 * @param ville_a
	 *            id de la ville d'arrivée
	 * @return Plus court chemin selon la methode d'agrégation
	 */

	public ArrayList<Route> BellmanFord(ArrayList<Double> tab_routes,
			int ville_dep, int ville_a) {
		ArrayList<Route> result = new ArrayList<Route>();
		ArrayList<Route> PCC = new ArrayList<Route>();
		ArrayList<Integer> listeNoeud = graph.listeNoeuds();
		Set<Integer> PCCkeys;
		HashMap<Integer, Integer> pi = new HashMap<Integer, Integer>();
		HashMap<Integer, Double> d = new HashMap<Integer, Double>();
		// Pour stocker la route du PCC permettant d'acceder au noeud référencé
		// par sa la clef de cette route
		HashMap<Integer, Integer> r = new HashMap<Integer, Integer>();

		// INITIALISATION DES TABS
		for (Integer noeud : listeNoeud) {
			d.put(noeud, Double.MAX_VALUE);
			pi.put(noeud, -1);
		}
		d.put(ville_dep, 0.0);
		pi.put(ville_dep, ville_dep);
		for (int villecourante = 0; villecourante < graph.NombreNoeuds() - 1; villecourante++) {

			for (Arc arc : graph.listeArcs()) {
				// si d[v]>d[u]+w(u v)
				if (d.get(arc.getN2()) > (d.get(arc.getN1()) + tab_routes
						.get(arc.getId()))
						&& (d.get(arc.getN2()) != null)) {
					// d[v]<- d[u]+w(u v)
					d.put(arc.getN2(), tab_routes.get(arc.getId())
							+ (d.get(arc.getN1())));
					// π[v]<- u
					pi.put(arc.getN2(), arc.getN1());
					// route reliant π[v]<-u
					r.put(arc.getN2(), arc.getId());
					// System.out.println("MAJ");
				}
			}
		}
		// VERIFICATION DE CIRCUIT ABSORBANT

		for (Arc arc : graph.listeArcs()) {
			// si d[v]>d[u]+w(u v)
			if (d.get(arc.getN2()) > (d.get(arc.getN1()) + tab_routes.get(arc
					.getId()))) {
				// CIRCUIT ABSORBANT
				return PCC; // VIDE

			}
		}
		
		PCCkeys = pi.keySet();
		PCCkeys = r.keySet();
		Integer ville;
		ville = ville_a;
		while (ville != ville_dep) {
			Route tmp;
			tmp = routes.get(r.get(ville));
			PCC.add(tmp);
			ville = tmp.getN1();
		}
		// On inverse le resultat
		for (int i = PCC.size() - 1; i >= 0; i--)
			result.add(PCC.get(i));
		return result;
	}

	/**
	 * 
	 * @param tab_routes
	 *            La table des pondération indicé par l'id des routes
	 * @param ville_dep
	 *            Nom de la ville de départ
	 * @param ville_a
	 *            Nom de la ville d'arrivée
	 * @return
	 */
	public ArrayList<Route> BellmanFord(ArrayList<Double> tab_routes,
			String ville_dep, String ville_a) {
		return BellmanFord(tab_routes, annuaireInverse.get(ville_dep),
				annuaireInverse.get(ville_a));
	}

	/**
	 * Affichage des PCC selon les consignes du sujet.
	 * 
	 * @param PCC
	 */
	public void put_itineraire(List<Route> PCC) {
		String itineraire = new String("Ville Départ : ");
		String ville = new String("");
		String route = new String("");
		int etoiles = 0;
		double longueur = 0;
		double l;
		int cpt = 0;
		ville = getville(villes.get(PCC.get(0).getN1()));
		itineraire += ville;
		itineraire += '\n';
		route += getroute(PCC.get(0));
		l = PCC.get(0).getLongueur();
		longueur += l;
		ville = getville(villes.get(PCC.get(0).getN2()));
		itineraire += "route " + route + "vers :" + ville + " longueur : " + l
				+ "\n";
		etoiles += villes.get(PCC.get(0).getN1()).getQualite()
				+ PCC.get(0).getQualite()
				+ villes.get(PCC.get(0).getN2()).getQualite();
		cpt += 3;
		for (int i = 1; i <= PCC.size() - 1; i++) {
			l = PCC.get(i).getLongueur();
			longueur += l;
			route = getroute(PCC.get(i));
			ville = getville(villes.get(PCC.get(i).getN2()));
			etoiles += PCC.get(i).getQualite()
					+ villes.get(PCC.get(i).getN2()).getQualite();
			cpt += 2;
			itineraire += "route " + route + "vers :" + ville + " longueur : "
					+ l + "\n";
		}
		itineraire += "Ville arrivée :";
		ville = getville(villes.get(PCC.get(PCC.size() - 1).getN2()));
		itineraire += ville;
		System.out.println(itineraire);
		System.out.println("Longueur de l'itinéraire : " + longueur);
		System.out.print("Intérêt touristique: ");
		for (int i = 1; i <= (etoiles / cpt); i++)
			System.out.print("*");
		System.out.println("");
	}

	public String getville(Ville ville) {
		String result = new String("");
		result += ville.getNom();
		result += " ";
		result += getetoiles(ville);

		return result;

	}

	public String getroute(Route route) {
		String result = new String("");
		result += route.getNom();
		result += " ";
		result += getetoiles(route);
		return result;
	}

	public String getetoiles(Ville ville) {
		String result = new String("");
		for (int i = 1; i <= ville.getQualite(); i++)
			result += "*";
		return result;
	}

	public String getetoiles(Route route) {
		String result = new String("");
		for (int i = 1; i <= route.getQualite(); i++)
			result += "*";
		return result;
	}

	/**
	 * Recherche le chemin de meilleur qualité sur un ensemble borné par la plus
	 * court chemin multiplié par K
	 * 
	 * @param K
	 *            valeur superieure à 1 fournissant une borne max par rapport au
	 *            PCC
	 * @param depart
	 *            nom du noeuds de départ
	 * @param arrivee
	 *            nom du noeuds d'arrivée
	 * @return le meilleur qualité sur un ensemble borné par la plus court
	 *         chemin multiplié par K
	 */
	public LinkedList<Route> detourBorne(double K, String depart, String arrivee) {
		return detourBorne(K, annuaireInverse.get(depart), annuaireInverse
				.get(arrivee));
	}

	/**
	 * Recherche le chemin de meilleur qualité sur un ensemble borné par la plus
	 * court chemin multiplié par K
	 * 
	 * @param K
	 *            valeur superieure à 1 fournissant une borne max par rapport au
	 *            PCC
	 * @param depart
	 *            id du noeuds de départ
	 * @param arrivee
	 *            id du noeuds d'arrivée
	 * @return le meilleur qualité sur un ensemble borné par la plus court
	 *         chemin multiplié par K
	 */
	public LinkedList<Route> detourBorne(double K, int depart, int arrivee) {
		ArrayList<Double> routes_ponderation = new ArrayList<Double>();
		ArrayList<Route> PCC = null;
		double bornePCC = 0;

		for (int i = 0; i < routes.size(); i++) {
			routes_ponderation.add(routes.get(i).getLongueur());
		}

		PCC = BellmanFord(routes_ponderation, depart, arrivee);

		for (Route route : PCC) {
			bornePCC += route.getLongueur();
		}
		bornePCC *= K;

		return detourBorneIter(bornePCC, depart, arrivee);

	}

	private LinkedList<Route> detourBorneIter(double bornePCC, int depart,
			int arrivee) {
		LinkedList<Route> cheminCourant = new LinkedList<Route>();
		LinkedList<Route> meilleurChemin = new LinkedList<Route>();
		HashMap<Integer, Integer> tabCouleurs = new HashMap<Integer, Integer>();
		// qualiteMax va permettre de faire remonté la meilleure qualité
		// parcourue lors de la boucle itérative
		LinkedList<Integer> qualiteMax = new LinkedList<Integer>();
		for (Integer i : graph.listeNoeuds()) {
			tabCouleurs.put(i, 0);
		}
		qualiteMax.add(0);
		return detourBorneIter(cheminCourant, meilleurChemin, tabCouleurs,
				bornePCC, depart, arrivee, 0, 0, qualiteMax);
	}

	@SuppressWarnings("unchecked")
	private LinkedList<Route> detourBorneIter(LinkedList<Route> cheminCourant,
			LinkedList<Route> meilleurChemin,
			HashMap<Integer, Integer> tabCouleurs, double bornePCC, int depart,
			int arrivee, double somme, int qualiteCumule,
			LinkedList<Integer> qualiteMax) {
		if (depart == arrivee && qualiteMax.getFirst() < qualiteCumule) {
			qualiteMax.set(0, qualiteCumule);
			meilleurChemin.clear();
			meilleurChemin.addAll(cheminCourant);
		} else {
			ArrayList<Arc> routesSuivantes;
			int id;
			int ville;
			double longueur;
			int qualite;
			tabCouleurs.put(depart, 1);
			routesSuivantes = graph.listerArcsSortants(depart);
			for (Arc routeSuivante : routesSuivantes) {
				ville = routeSuivante.getN2();
				id = routeSuivante.getId();
				longueur = routes.get(id).getLongueur();
				qualite = routes.get(id).getQualite()
						+ villes.get(ville).getQualite();
				if ((tabCouleurs.get(ville) == 0)
						&& ((somme + longueur) <= bornePCC)) {
					cheminCourant.add(routes.get(id));
					detourBorneIter(cheminCourant, meilleurChemin, tabCouleurs,
							bornePCC, ville, arrivee, somme + longueur,
							qualiteCumule + qualite, qualiteMax);

					cheminCourant.removeLast();// File
				}
			}
			tabCouleurs.put(depart, 0);

		}

		return meilleurChemin;
	}

	// AFFICHAGE DE HASHMAP PR DEBUG
	public void puthd(HashMap<Integer, Double> h) {
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys) {

			System.out.print(h.get(i) + " ");
		}
		System.out.println("]");
	}

	public void puthi(HashMap<Integer, Integer> h) {
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys) {

			System.out.print(h.get(i));

		}
		System.out.println("]");
	}

	public void puthr(HashMap<Integer, Route> h) {
		Set<Integer> PCCkeys = h.keySet();
		System.out.print("[");
		for (Integer i : PCCkeys) {
			System.out.print(h.get(i));
		}
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
