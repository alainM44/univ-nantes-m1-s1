import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;

public class ListGraph extends AbstractGrapheOriente
{

	// ArrayList pour le moment
	HashMap<Integer, LinkedList<Encapsulateur<Integer>>> graphe;

	ListGraph()
	{
		super();
		graphe = new HashMap<Integer, LinkedList<Encapsulateur<Integer>>>();
	}

	@Override
	public int ajouterA(int n1, int n2)
	{

		LinkedList<Encapsulateur<Integer>> aux = graphe.get(n1);
		Iterator<Encapsulateur<Integer>> iter = aux.iterator();
		Encapsulateur<Integer> encaps;

		idGenerator++;
		// On augmente le nb d'arc associe au noeud
		iter.next().changeNbArc(1);
		while (iter.hasNext())
		{
			encaps = iter.next();
			if (encaps.getValeur() == n2)
			{
				encaps.ajouterArc(idGenerator);
				return idGenerator;
			}
		}

		encaps = new Encapsulateur<Integer>(n2, idGenerator);
		aux.addLast(encaps);// Permet d'assurer que le premier element reste
		// le meme le noeud

		nbArc++;
		return idGenerator;
	}

	@Override
	public void ajouterN(int n)
	{
		LinkedList<Encapsulateur<Integer>> aux = new LinkedList<Encapsulateur<Integer>>();
		aux.add(new Encapsulateur<Integer>(n));// On stocke le nombre d'arc
		// issus du noeud en question
		graphe.put(n, aux);
		nbNoeuds++;
	}

	@Override
	public void supprimerA(int id, int n1, int n2)
	{
		LinkedList<Encapsulateur<Integer>> aux = graphe.get(n1);
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
		Set<Integer> mesClefs = graphe.keySet();
		Integer clefASupprimer = null;

		for (Integer clef : mesClefs)
		{

			noeudCourant = graphe.get(clef);
			iterAretes = noeudCourant.iterator();
			noeud = iterAretes.next();
			areteTrouve = false;
			// pas besoin de verification sur next, il s'agit en fait du noeud
			if (noeud.getValeur() == n)
			{
				nbArc -= noeud.getNbArc();
				// On met a jour la valeur du noeud
				noeud.changeNbArc(noeud.getNbArc());
				clefASupprimer = clef;
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
		graphe.remove(clefASupprimer);
		nbNoeuds--;
	}

	@Override
	public ArrayList<Arete> listerArcsEntrants(int n)
	{
		ArrayList<Arete> listeRetour = new ArrayList<Arete>();
		Set<Integer> clefsNoeuds = graphe.keySet();
		Iterator<Encapsulateur<Integer>> iterArete;
		Encapsulateur<Integer> noeudCourant;
		Encapsulateur<Integer> areteCourante;

		for (Integer clefNoeud : clefsNoeuds)
		{
			iterArete = graphe.get(clefNoeud).iterator();
			noeudCourant = iterArete.next();
			while (iterArete.hasNext())
			{
				areteCourante = iterArete.next();
				if (areteCourante.getValeur() == n)
				{
					for (int i = 0; i < areteCourante.getNbArc(); i++)
					{
						listeRetour.add(new Arete(noeudCourant.getValeur(),
								areteCourante.getValeur(), areteCourante
										.getId(i)));
					}
				}
			}
		}
		return listeRetour;
	}

	@Override
	public ArrayList<Arete> listerArcsSortants(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listerPredecesseurs(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listerSuccesseurs(int n)
	{
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArrayList<Integer> listeNoeuds()
	{
		Iterator<LinkedList<Encapsulateur<Integer>>> iterNoeuds;
		ArrayList<Integer> retour = new ArrayList<Integer>();
		iterNoeuds = graphe.values().iterator();
		while (iterNoeuds.hasNext())
		{
			retour.add(iterNoeuds.next().getFirst().getValeur());
		}
		return retour;
	}

	@Override
	public ArrayList<Integer> listeArcs()
	{
		return null;
	}

	@Override
	public String toString()
	{
		String retour = "";
		Encapsulateur<Integer> temp;
		Iterator<Encapsulateur<Integer>> iterAretes;
		for (Integer clefNoeud : graphe.keySet())
		{
			iterAretes = graphe.get(clefNoeud).iterator();
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
