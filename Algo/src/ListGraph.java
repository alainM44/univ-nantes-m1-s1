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

		Iterator<Encapsulateur<Integer>> iter = graphe.get(n1).iterator();
		Encapsulateur<Integer> encaps;

		nbArc++;
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
		graphe.get(n1).addLast(encaps);// Permet d'assurer que le premier element reste
		// le meme le noeud

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
		Iterator<Encapsulateur<Integer>> iterArc;
		Set<Integer> mesClefs = graphe.keySet();
		Integer clefASupprimer = null;

		for (Integer clef : mesClefs)
		{

			noeudCourant = graphe.get(clef);
			iterArc = noeudCourant.iterator();
			noeud = iterArc.next();
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
				while (iterArc.hasNext() && !areteTrouve)
				{
					areteCourante = iterArc.next();
					if (areteCourante.getValeur() == n)
					{
						nbArc -= areteCourante.getNbArc();
						// On met a jour la valeur du noeud
						noeud.changeNbArc(-areteCourante.getNbArc());
						iterArc.remove();
						areteTrouve = true;

					}
				}
			}

		}
		graphe.remove(clefASupprimer);
		nbNoeuds--;
	}

	@Override
	public ArrayList<Arc> listerArcsEntrants(int n)
	{
		ArrayList<Arc> listeRetour = new ArrayList<Arc>();
		Set<Integer> clefsNoeuds = graphe.keySet();
		Iterator<Encapsulateur<Integer>> iterArete;
		Encapsulateur<Integer> noeudCourant;
		Encapsulateur<Integer> arcCourant;

		for (Integer clefNoeud : clefsNoeuds)
		{
			iterArete = graphe.get(clefNoeud).iterator();
			noeudCourant = iterArete.next();
			while (iterArete.hasNext())
			{
				arcCourant = iterArete.next();
				if (arcCourant.getValeur() == n)
				{
					for (int i = 0; i < arcCourant.getNbArc(); i++)
					{
						listeRetour.add(new Arc(noeudCourant.getValeur(),
								arcCourant.getValeur(), arcCourant.getId(i)));
					}
				}
			}
		}
		return listeRetour;
	}

	@Override
	public ArrayList<Arc> listerArcsSortants(int n)
	{
		ArrayList<Arc> listeRetour = new ArrayList<Arc>();
		Iterator<Encapsulateur<Integer>> iterArc = graphe.get(n).iterator();
		Encapsulateur<Integer> arcCourant;

		iterArc.next();
		while (iterArc.hasNext())
		{
			arcCourant = iterArc.next();
			for (int i = 0; i < arcCourant.getNbArc(); i++)
			{
				listeRetour.add(new Arc(n, arcCourant.getValeur(), arcCourant
						.getId(i)));
			}
		}
		return listeRetour;
	}

	@Override
	public ArrayList<Integer> listerPredecesseurs(int n)
	{
		ArrayList<Integer> listeRetour = new ArrayList<Integer>();
		Set<Integer> clefsNoeuds = graphe.keySet();
		Iterator<Encapsulateur<Integer>> iterArete;
		Encapsulateur<Integer> noeudCourant;
		Encapsulateur<Integer> arcCourant;

		for (Integer clefNoeud : clefsNoeuds)
		{
			iterArete = graphe.get(clefNoeud).iterator();
			noeudCourant = iterArete.next();
			while (iterArete.hasNext())
			{
				arcCourant = iterArete.next();
				if (arcCourant.getValeur() == n)
				{
					listeRetour.add(noeudCourant.getValeur());
					break;
				}
			}
		}
		return listeRetour;
	}

	@Override
	public ArrayList<Integer> listerSuccesseurs(int n)
	{
		ArrayList<Integer> listeRetour = new ArrayList<Integer>();
		Iterator<Encapsulateur<Integer>> iterArc = graphe.get(n).iterator();
		Encapsulateur<Integer> arcCourant;

		iterArc.next();
		while (iterArc.hasNext())
		{
			arcCourant = iterArc.next();
			listeRetour.add(arcCourant.getValeur());
		}
		return listeRetour;
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
	public ArrayList<Arc> listeArcs()
	{
		ArrayList<Arc> listeRetour = new ArrayList<Arc>();
		Set<Integer> clefsNoeuds = graphe.keySet();
		Iterator<Encapsulateur<Integer>> iterArc;
		Encapsulateur<Integer> noeudCourant;
		Encapsulateur<Integer> arcCourant;

		for (Integer clefNoeud : clefsNoeuds)
		{
			iterArc = graphe.get(clefNoeud).iterator();
			noeudCourant = iterArc.next();
			while (iterArc.hasNext())
			{
				arcCourant = iterArc.next();
				for (int i = 0; i < arcCourant.getNbArc(); i++)
				{
					listeRetour.add(new Arc(noeudCourant.getValeur(),
							arcCourant.getValeur(), arcCourant.getId(i)));
				}
			}
		}
		return listeRetour;
	}

	@Override
	public String toString()
	{
		String retour = "";
		Encapsulateur<Integer> temp;
		Iterator<Encapsulateur<Integer>> iterArc;
		for (Integer clefNoeud : graphe.keySet())
		{
			iterArc = graphe.get(clefNoeud).iterator();
			retour += iterArc.next().getValeur();
			while (iterArc.hasNext())
			{
				temp = iterArc.next();
				retour += "->" + temp.getValeur() + temp.getListe();
			}
			retour += "\n";
		}
		return retour;
	}

}
