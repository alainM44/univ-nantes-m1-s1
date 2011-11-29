package Graphe;
public abstract class AbstractGrapheOriente implements GrapheOriente
{

	int nbNoeuds;
	int nbArc;

	AbstractGrapheOriente()
	{
		nbNoeuds = 0;
		nbArc = 0;
	}

	@Override
	public int NombreNoeuds()
	{
		return nbNoeuds;
	}
	
	public int NombreArcs()
	{
		return nbArc;
	}
}