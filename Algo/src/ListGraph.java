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
		boolean trouve = false;
		int i = 0;
		LinkedList<Encapsulateur<Integer>> aux;
		do
		{
			aux = graphe.get(i);
			trouve = aux.getFirst().getValeur() == n1;
			i++;
		}
		while (trouve);
		Iterator<Encapsulateur<Integer>> iter = aux.iterator();
		Encapsulateur<Integer> encaps;

		idGenerator++;
		// On augmente le nb d'arc associe au noeud
		iter.next().changeNbArc(1);
		if (iter.hasNext())
		{
			encaps = iter.next();
			while (iter.hasNext() && encaps.getValeur() != n2)
			{
				encaps = iter.next();
			}
			encaps.ajouterArc(idGenerator);
		}
		else
		{
			encaps = new Encapsulateur<Integer>(n2, idGenerator);
			aux.addLast(encaps);// Permet d'assurer que le premier element reste
			// le meme le noeud
		}
		nbArc++;
		return idGenerator;
	}

	@Override
	public void ajouterN(int n)
	{
		LinkedList<Encapsulateur<Integer>> aux = new LinkedList<Encapsulateur<Integer>>();
		aux.add(new Encapsulateur<Integer>(n));// On stocke le nombre d'arc
		// issus du noeud en question
		graphe.add(aux);
		nbNoeuds++;
	}

	@Override
	public void supprimerA(int id, int n1, int n2)
	{
		boolean trouve = false;
		int i = 0;
		LinkedList<Encapsulateur<Integer>> aux;
		do
		{
			aux = graphe.get(i);
			trouve = aux.getFirst().getValeur() == n1;
			i++;
		}
		while (trouve);
		Iterator<Encapsulateur<Integer>> iter = aux.iterator();
		Encapsulateur<Integer> encaps;

		idGenerator++;
		// On décremente le nb d'arc au niveau du noeud
		iter.next().changeNbArc(-1);
		encaps = iter.next();
		while (iter.hasNext() && encaps.getValeur() != n2)
		{
			encaps = iter.next();
		}
		encaps.supprimerArc(id);
		if (encaps.isEmpty())
		{
			iter.remove();
		}
		nbArc--;
	}

	@Override
	public void supprimerN(int n)
	{
		boolean areteTrouve;
		Encapsulateur<Integer> areteCourante;
		Encapsulateur<Integer> noeud;
		LinkedList<Encapsulateur<Integer>> noeudCourant;
		Iterator<Encapsulateur<Integer>> iterAretes;
		Iterator<LinkedList<Encapsulateur<Integer>>> iterNoeuds;

		iterNoeuds = graphe.iterator();
		while (iterNoeuds.hasNext())
		{
			noeudCourant = iterNoeuds.next();
			iterAretes = noeudCourant.iterator();
			noeud = iterAretes.next();
			areteTrouve = false;
			// pas besoin de verification sur next, il s'agit en fait du noeud
			if (noeud.getValeur() == n)
			{
				nbArc -= noeud.getNbArc();
				// On met a jour la valeur du noeud
				noeud.changeNbArc(noeud.getNbArc());
				iterNoeuds.remove();
			}
			else
			{
				while (iterAretes.hasNext() && !areteTrouve)
				{
					areteCourante = iterAretes.next();
					if (areteCourante.getValeur() == n)
					{
						nbArc -= areteCourante.getNbArc();
						// On met a jour la valeur du noeud
						noeud.changeNbArc(-areteCourante.getNbArc());
						iterAretes.remove();
						areteTrouve = true;

					}
				}
			}

		}
		nbNoeuds--;
	}

	@Override
	public List<Integer> listerArcsEntrants(int n)
	{
		return null;
	}

	Iterator<Encapsulateur<Integer>> iterAretes;

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
		return null;
	}

	@Override
	public String toString()
	{
		String retour = "";
		Encapsulateur<Integer> temp;
		Iterator<Encapsulateur<Integer>> iterAretes;
		for (int i = 0; i < nbNoeuds; i++)
		{
			iterAretes = graphe.get(i).iterator();
			retour += iterAretes.next().getValeur();
			while (iterAretes.hasNext())
			{
				temp = iterAretes.next();
				retour += "->" + temp.getValeur() + temp.getListe();
			}
			retour += "\n";
		}
		return retour;
	}

}
