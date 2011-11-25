package Graphe;

public class Route extends Arc
{
	private String nom;
	private double longueur;
	private int qualite;

	public Route(int n1, int n2, int id, String nom, double longueur,
			int qualite)
	{
		super(n1, n2, id);
		this.nom = nom;
		this.longueur = longueur;
		this.qualite = qualite;
	}

	public String getNom()
	{
		return nom;
	}

	public void setNom(String nom)
	{
		this.nom = nom;
	}

	public double getLongueur()
	{
		return longueur;
	}

	public void setLongueur(double longueur)
	{
		this.longueur = longueur;
	}

	public int getQualite()
	{
		return qualite;
	}

	public void setQualite(int qualite)
	{
		this.qualite = qualite;
	}

	public String toString()
	{
		return "Route : " + nom + " longueur : " + longueur + " qualité : "
				+ qualite + " " + super.toString();
	}

}
