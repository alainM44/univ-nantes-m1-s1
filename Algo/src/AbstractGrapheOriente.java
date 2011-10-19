public abstract class AbstractGrapheOriente implements GrapheOriente
{

	int nbNoeuds;
	int nbAretes;
	Integer idGenerator;

	AbstractGrapheOriente()
	{
		nbNoeuds = 0;
		nbAretes = 0;
		idGenerator = 0;
	}

	@Override
	public int NombreNoeuds()
	{
		return nbNoeuds;
	}
	
	public int NombreAretes()
	{
		return nbAretes;
	}
}