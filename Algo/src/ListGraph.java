import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class ListGraph extends AbstractGrapheOriente
{

	// ArrayList pour le moment
	ArrayList<LinkedList<Encapsulateur<Integer>>> graphe;

	ListGraph()
	{
		super();
		graphe = new ArrayList<LinkedList<Encapsulateur<Integer>>>();
	}

	@Override
	public int ajouterA(int n1, int n2)
	{
		LinkedList<Encapsulateur<Integer>> aux = graphe.get(n1);
		Iterator<Encapsulateur<Integer>> iter = aux.iterator();
		Encapsulateur<Integer> encaps;

		idGenerator++;
		iter.next();
		if (iter.hasNext())
		{
			encaps = iter.next();
			while (iter.hasNext() && encaps.getValeur() != n2)
			{
				encaps = iter.next();
			}
			encaps.ajouterArete(idGenerator);
		}
		else
		{
			encaps = new Encapsulateur<Integer>(n2, idGenerator);
			aux.addLast(encaps);// Permet d'assurer que le premier element reste
								// le meme le noeud
		}
		nbAretes++;
		return idGenerator;
	}

	@Override
	public void ajouterN(int n)
	{
		LinkedList<Encapsulateur<Integer>> aux = new LinkedList<Encapsulateur<Integer>>();
		aux.add(new Encapsulateur<Integer>(n));
		graphe.add(aux);
		nbNoeuds++;
	}

	@Override
	public void supprimerA(int id, int n1, int n2)
	{
		LinkedList<Encapsulateur<Integer>> aux = graphe.get(n1);
		Iterator<Encapsulateur<Integer>> iter = aux.iterator();
		Encapsulateur<Integer> encaps;

		idGenerator++;
		iter.next();
		encaps = iter.next();
		while (iter.hasNext() && encaps.getValeur() != n2)
		{
			encaps = iter.next();
		}
		encaps.supprimerArete(id);
		if (encaps.isEmpty())
		{
			iter.remove();
		}
		nbAretes--;
	}

	@Override
	public void supprimerN(int n)
	{
		boolean areteTrouve;
		Encapsulateur<Integer> areteCourante;
		LinkedList<Encapsulateur<Integer>> noeudCourant;
		Iterator<Encapsulateur<Integer>> iterAretes;
		Iterator<LinkedList<Encapsulateur<Integer>>> iterNoeuds;

		iterNoeuds = graphe.iterator();
		while (iterNoeuds.hasNext())
		{
			noeudCourant = iterNoeuds.next();
			iterAretes = noeudCourant.iterator();
			areteTrouve = false;
			// pas besoin de verification sur next, il s'agit en fait du noeud
			if (iterAretes.next().getValeur() == n)
			{
				iterNoeuds.remove();
			}
			else
			{
				while (iterAretes.hasNext() && !areteTrouve)
				{
					areteCourante = iterAretes.next();
					if (areteCourante.getValeur() == n)
					{
						iterAretes.remove();
						areteTrouve = true;
					}
				}
			}

		}
	}

	@Override
	public List<Integer> listerArcsEntrants(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerArcsSortants(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerPredecesseurs(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List<Integer> listerSuccesseurs(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listeNoeuds()
	{
		Iterator<LinkedList<Encapsulateur<Integer>>> iterNoeuds;
		ArrayList<Integer> retour = new ArrayList<Integer>();
		iterNoeuds = graphe.iterator();
		while (iterNoeuds.hasNext())
		{
			retour.add(iterNoeuds.next().getFirst().getValeur());
		}
		return retour;
	}

	@Override
	public ArrayList<Integer> listeAretes()
	{
		// TODO Auto-generated method stub
		return null;
	}

}