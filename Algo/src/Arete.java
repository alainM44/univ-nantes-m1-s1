/*
 * Utiliser pour les methodes listerArcsEntrants et listerArcsSortants
 */
public class Arete
{
	int noeud1;
	int noeud2;
	int id;

	public Arete(int n1, int n2, int id)
	{
		noeud1 = n1;
		noeud2 = n2;
		this.id = id;
	}
	
	public int getN1()
	{
		return noeud1;
	}
	
	public int getN2()
	{
		return noeud2;
	}
	
	public int getId()
	{
		return id;
	}
	
	public String toString()
	{
		return noeud1 +" -> " + noeud2 + "[" +id+"] ";
	}
}
