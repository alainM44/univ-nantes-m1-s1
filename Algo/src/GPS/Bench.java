package GPS;

import java.io.File;
import java.util.HashMap;

public class Bench
{
	private static GPS monGPS;

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		String villea = "20";
		File fich = new File("/comptes/E074862X/workspace/Algo/test/test0.dot");
		monGPS = new GPS(fich, "l");
		// ag(1, villea);
		db(8, villea);

	}

	private static void ag(double A, String n)
	{
		long mili;
		mili = System.currentTimeMillis();
		HashMap<Integer, Double> ponderation = monGPS.agregation(A);
		monGPS.BellmanFord(ponderation, "1", n);
		mili = System.currentTimeMillis() - mili;
		System.out.println("time : " + mili);
	}

	private static void db(double K, String n)
	{
		long mili;
		mili = System.currentTimeMillis();
		monGPS.detourBorne(K, "1", n);
		mili = System.currentTimeMillis() - mili;
		System.out.println("time : " + mili);
	}
}
