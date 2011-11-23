package GPS;

import java.io.File;
import java.util.HashMap;

import Graphe.GrapheOriente;
import Graphe.ListGraph;
import Graphe.Route;
import Graphe.Ville;

public class TestParseur
{

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		GrapheOriente graphe = new ListGraph();
		HashMap<Integer, Ville> villes = new HashMap<Integer, Ville>();
		HashMap<Integer, Route> routes = new HashMap<Integer, Route>();
		File fich = new File("/comptes/E074862X/Desktop/Generateur/out.txt");
		Parseur pars = new Parseur(fich);
		pars.parse(graphe, villes, routes);
		System.out.println(graphe);
		for (int i : villes.keySet())
			System.out.println(villes.get(i).getNom()+" "+villes.get(i).getQualite());
		System.out.println(routes);
	}

}
