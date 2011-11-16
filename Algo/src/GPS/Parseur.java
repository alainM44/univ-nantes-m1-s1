package GPS;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.regex.Pattern;


import Graphe.Route;
import Graphe.Ville;

public class Parseur
{
	File monFichier;

	public Parseur(File fich)
	{
		monFichier = fich;
	}
	
	public void parse( HashMap<Integer, Ville> villes, HashMap<Integer, Route> routes ) throws FileNotFoundException
	{
		String valeur;
		Scanner scan = new Scanner(monFichier);
		valeur = scan.next("diagraph {");
		while(valeur!="}")
		{
			scan.next("[a-zA-Z0-9}");
		}
	}
}
