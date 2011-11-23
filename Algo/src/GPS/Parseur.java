package GPS;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

import Graphe.GrapheOriente;
import Graphe.Route;
import Graphe.Ville;

public class Parseur
{
	File monFichier;

	public Parseur(File fich)
	{
		monFichier = fich;
	}

	/**
	 * Parse le fichier fourni representant le gps et retourne
	 * 
	 * @param graph
	 *            le graphe correspondant au fichier
	 * @param villes
	 *            une HashMap contenant les villes indicées par un id
	 * @param routes
	 *            une HashMap contenant les routes indicées par un id
	 */
	public void parse(GrapheOriente graph, HashMap<Integer, Ville> villes,
			HashMap<Integer, Route> routes)
	{
		int nbVille = 0;
		int nbRoute = 0;
		String nomTemp;
		int n1Temp;
		int n2Temp;
		int qualiteTemp;
		double longueurTemp;
		Ville villeTemp;
		Route routeTemp;

		HashMap<String, Integer> annuaireInverse = new HashMap<String, Integer>();
		String[] decoupe;
		String valeur;
		Scanner scan = null;
		try
		{
			scan = new Scanner(monFichier);
		} catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		valeur = scan.nextLine();
		while (scan.hasNextLine())
		{
			valeur = scan.nextLine();
			if (valeur
					.matches("[a-zA-Z0-9]* \\[label=\\\"[a-zA-Z0-9]*\\([\\*]*\\)\\\"\\]"))
			{
				decoupe = valeur.split(" ");
				nomTemp = decoupe[0];
				annuaireInverse.put(nomTemp, nbVille);
				decoupe = decoupe[1].split("\\(");
				decoupe = decoupe[1].split("\\)");
				qualiteTemp = decoupe[0].length();
				villeTemp = new Ville(nomTemp, qualiteTemp);
				villes.put(nbVille, villeTemp);
				graph.ajouterN(nbVille);
				nbVille++;
			}
			else if (valeur
					.matches("[a-zA-Z0-9]*->[a-zA-Z0-9]* \\[label=\\\"[a-zA-Z0-9]*\\([0-9]*\\.?[0-9]*;[\\*]*\\)\\\"\\]"))
			{
				decoupe = valeur.split("->");
				n1Temp = annuaireInverse.get(decoupe[0]);
				decoupe = decoupe[1].split(" ");
				n2Temp = annuaireInverse.get(decoupe[0]);
				decoupe = decoupe[1].split("\\\"");
				decoupe = decoupe[1].split("\\(");
				nomTemp = decoupe[0];
				decoupe = decoupe[1].split(";");
				longueurTemp = Double.parseDouble(decoupe[0]);
				decoupe = valeur.split(";");
				decoupe = decoupe[1].split("\\)");
				qualiteTemp = decoupe[0].length();
				graph.ajouterA(n1Temp, n2Temp);
				routeTemp = new Route(n1Temp, n2Temp, nbRoute, nomTemp,
						longueurTemp, qualiteTemp);
				routes.put(nbRoute, routeTemp);
				nbRoute++;
			}
			else if (valeur.matches("}"))
			{}
			else
				System.out.println("erreur " + valeur);
		}
		System.out.println(graph);
	}
}
