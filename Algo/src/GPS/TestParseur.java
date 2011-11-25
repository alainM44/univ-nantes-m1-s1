package GPS;

import java.io.File;
import java.io.FileNotFoundException;
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
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args)
	{
		File fich = new File("/comptes/E11A932Q/workspace/Algo/test/out.dot");
		GPS monGPS = new GPS(fich);
	//	ArrayList<Route> aAffiche = monGPS.agregation(100);
		ArrayList<Route> PCC= monGPS.BellmanFord(monGPS.agregation(0.7));
		for(int i =0;i<PCC.size();i++)
			System.out.println(PCC.get(i));
	//	monGPS.put_itineraire(PCC);
		
	//	System.out.println(aAffiche);
	}

}
