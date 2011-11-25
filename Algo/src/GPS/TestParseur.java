package GPS;

import java.io.File;
import java.util.ArrayList;
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
		File fich = new File("/comptes/E074862X/Desktop/Generateur/g1.dot");
		GPS monGPS = new GPS(fich);
		System.out.println(monGPS.imax);
		ArrayList<Double> aAffiche = monGPS.agregation(0.7);
		System.out.println(aAffiche);
	}

}
