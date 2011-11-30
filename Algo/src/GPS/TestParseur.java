package GPS;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

import Graphe.GrapheOriente;
import Graphe.ListGraph;


public class TestParseur
{

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		long mili;
		File fich = new File("/comptes/E074862X/workspace/Algo/test/g1.dot");
		//File fich = new File("/home/alain/workspace/Algo/test/g1.dot");
		GPS monGPS = new GPS(fich);
		System.out.println(monGPS.imax);
	//	monGPS.BellmanFord(aAffiche,2,0);
	//	System.out.println(aAffiche);
//		mili = System.currentTimeMillis();
//		monGPS.agregation(0.7);
//		mili = System.currentTimeMillis() - mili;
//		System.out.println("temps = " + mili);
//		System.out.println("agreg");
		mili = System.currentTimeMillis();
		monGPS.detourBorne(1, 0, 500);
		mili = System.currentTimeMillis() - mili;
		System.out.println("temps = " + mili);
		System.out.println("borne");
	}

}
