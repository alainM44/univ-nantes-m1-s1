package Graphe;

public class Route extends Arc
{
	private String nom;
	private int longueur;
	private int qualite;

	public Route(int n1, int n2, int id, String nom, int longueur,
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

	public int getLongueur()
	{
		return longueur;
	}

	public void setLongueur(int longueur)
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

}
