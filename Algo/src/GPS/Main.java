package GPS;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

import Graphe.GrapheOriente;
import Graphe.ListGraph;

public class Main
{

	static String villea;
	static String villed;
	static double A;
	static double K;
	static String Methode;
	static String Implementation;
	static String fichier;

	public static String lireString()
	{// lecture d'une chaine
		String ligne_lue = null;
		try
		{
			InputStreamReader lecteur = new InputStreamReader(System.in);
			BufferedReader entree = new BufferedReader(lecteur);
			ligne_lue = entree.readLine();
		} catch (IOException err)
		{
			System.exit(0);
		}
		return ligne_lue;
	}

	public static double lireDouble()
	{// lecture d'un double
		double x = 0; // valeur à lire
		try
		{
			String ligne_lue = lireString();
			x = Double.parseDouble(ligne_lue);
		} catch (NumberFormatException err)
		{
			System.out.println("***Erreur de données Double attendu***");
			System.exit(0);
		}
		return x;
	}

	public static String lireLettre()
	{// lecture d'un double
		String ligne_lue = lireString();
		String result = ligne_lue.substring(0, 1);
		return result;
	}

	public static void menu()
	{
		System.out.println("********************");
		System.out.println("********GPS*********");
		System.out.println("********************");
		System.out.println("Nom du fichier");
		String adresse = Main.lireString();
		if (adresse.charAt(0) == '/')
			fichier = adresse;
		else
			fichier += adresse;
		System.out.println("Choix l'implémentations de la structure de graphe");
		System.out.println("Tapez l pour utiliser une liste d'adjacence ");
		System.out.println("Tapez m pour utiliser une matrice d'adjacence ");
		Implementation = Main.lireLettre();
		System.out.println("Merci pour" + Implementation);
		System.out.println("Choix de la méthode de la calcul d'itinéraire");
		System.out.println("Tapez a pour la méthode par agrégation");
		System.out.println("Tapez d Pour la méthode detour borné ");
		Methode = Main.lireLettre();
		System.out.println("Tapez la ville de départ  ");
		villed = Main.lireString();
		System.out.println("Tapez ville de d'arrivée  ");
		villea = Main.lireString();

	}

	public static void getpwd() throws IOException
	{
		Runtime runtime = Runtime.getRuntime();
		Process process = runtime.exec(new String[] { "pwd" });
		// On ferme le flux d'entrée
		process.getOutputStream().close();
		// Et le flux d'erreur :
		process.getErrorStream().close();
		BufferedReader reader = new BufferedReader(new InputStreamReader(
				process.getInputStream()));
		try
		{
			String line = reader.readLine();
			fichier = line;
			fichier += "/";
			// System.out.println("Nom du fichier : " + fichier);
		} finally
		{
			reader.close();
		}

	}

	public static void main(String[] args) throws IOException
	{
		Main.getpwd();
		menu();
		long mili = 0;
		File fich = new File(fichier);
		GPS monGPS = new GPS(fich);
		if (Methode.compareTo("a") == 0)
		{
			System.out.println("Saisisser A");
			A = Main.lireDouble();
			System.out.println("Merci pour" + A);
			mili = System.currentTimeMillis();
			ArrayList<Double> ponderation = monGPS.agregation(A);
			monGPS.put_itineraire(monGPS.BellmanFord(ponderation, villed,
					villea));
			mili = System.currentTimeMillis() - mili;

		}
		else if (Methode.compareTo("d") == 0)
		{

			System.out.println("Saisissez K");
			K = Main.lireDouble();
			System.out.println("Merci pour" + K);
			mili = System.currentTimeMillis();
			monGPS.put_itineraire((monGPS.detourBorne(K, villed, villea)));
			mili = System.currentTimeMillis();

		}
		else
			System.out.println("ERROR : choix de methode");
		System.out.println("Temps de calcul de l'itinéraire: " + mili
				+ " milli sec");

	}

}
