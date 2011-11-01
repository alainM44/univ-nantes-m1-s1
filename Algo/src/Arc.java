/*
 * Utiliser pour les methodes listerArcsEntrants et listerArcsSortants
 */
public class Arc
{
	private int noeud1;
	private int noeud2;
	private int id;

	public Arc(int n1, int n2, int id)
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
