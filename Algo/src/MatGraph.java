import java.util.ArrayList;




public class MatGraph extends AbstractGrapheOriente{



	ArrayList2D<Encapsulateur<Boolean>>graph;	
	ArrayList<Encapsulateur<Integer>> tabnoeuds;

	public MatGraph(){
		super();
		graph = new ArrayList2D<Encapsulateur<Boolean>>() ;
		tabnoeuds = new ArrayList<Encapsulateur<Integer>>();
	}

	@Override
	public int ajouterA(int n1, int n2) {//position du noeud 
		idGenerator++;
		nbArc++;	
		if(	graph.get(n1,n2).listeIdArc ==null)
			graph.get(n1,n2).listeIdArc =new ArrayList<Integer>();
		else
		graph.get(n1,n2).ajouterArc(idGenerator);
		graph.get(n1,n2).setValeur(true);
		tabnoeuds.get(n1).nbArc++;
		//graph.ta
		return idGenerator;
	}
	@Override
	public void supprimerA(int id, int n1, int n2) { // odre du noeud !!!!! 1 pour 1er 2 pour  2eme... l'arc doit exister
		int listsize=graph.get(n1,n2).getListe().size();
		for(int j=0;j<listsize;j++)
		{
			if (graph.get(n1,n2).getListe().get(j) == id) // en O de 1
			{
				graph.get(n1,n2).getListe().remove(j);
				graph.get(n1, n2).setValeur(false);
			}
		}	
		tabnoeuds.get(n1).nbArc--;
		nbArc--;	
	}


	@Override
	public void ajouterN(int n) {
		//on ajoute une arraylist

		graph.addLigne();
		for(int i=0;i<nbNoeuds;i++)
		{	
			graph.getLine(i).add(new Encapsulateur<Boolean>(false));		//	graph.addCol(i,i,new Encapsulateur<Boolean>(false));
		}
		nbNoeuds++;
		for(int i=0;i<nbNoeuds;i++)
		{	
			graph.getLine(nbNoeuds-1).add(new Encapsulateur<Boolean>(false));
		}

		tabnoeuds.add(new Encapsulateur<Integer>(n));
		//	nbNoeuds++;
	}



	@Override
	public void supprimerN(int n) {
		int pos=0;
//		ArrayList<Arc> arcasup= listerArcsEntrants(tabnoeuds.get(n).getValeur());
		
//		int taillelistearcs=arcasup.size();	
//		for(int i=0;i<taillelistearcs;i++)
//		{
//			graph.get(i, tabnoeuds.get(n).valeur).setValeur(false);
//			graph.get(tabnoeuds.get(n).getValeur(),i).listeIdArc.remove(arcasup.get(i)); // INUTILITE DE NB AR
			//nbArc--;
//			
//		}
		for(int i=0; i<nbNoeuds-1;i++) // parcours de n
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				tabnoeuds.remove(i);
				pos=i;
			}
		}
		nbArc-=tabnoeuds.get(pos).getNbArc();
		graph.suppCol(pos);
		graph.suppLigne(pos); //en O de N
	
		nbNoeuds--;
		//on supprime les arc entrant

	}


	@Override
	public ArrayList<Arc> listeArcs() {
		ArrayList<Arc> result = new ArrayList<Arc>();
		int nbarctemp = nbArc;
		int taillelistearcs;	
		for(int i=0;i<nbNoeuds;i++)
		{
			for(int j=0;j<nbNoeuds;j++)
			{
				taillelistearcs =graph.get(i,j).listeIdArc.size();
				nbarctemp-=taillelistearcs;
				for(int k=0;k<taillelistearcs;k++)
					result.add(new Arc(tabnoeuds.get(i).getValeur(), tabnoeuds.get(j).getValeur(), graph.get(i,j).listeIdArc.get(k)));
				if(nbarctemp==0)
					break;
			}
		}
		return result;
	}

	@Override
	public ArrayList<Integer> listeNoeuds() {
		ArrayList<Integer> result = new ArrayList<Integer>();
		for(int i=0;i<nbNoeuds;i++)
			result.add(tabnoeuds.get(i).valeur);
		return result;
	}



	@Override
	public ArrayList<Integer> listerPredecesseurs(int n) {
		ArrayList<Integer> result = new ArrayList<Integer>();
		int pos=-1;
		for(int i=0;i<nbNoeuds;i++)
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				pos=i;
			}
		}
		if (pos==-1)
			System.out.println("erreur noeud inexistant");

		for(int j=0;j<nbNoeuds;j++)
		{
			if( graph.get(j, pos).getValeur() )
				result.add(tabnoeuds.get(j).valeur);

		}
		return result;
	}

	@Override
	public ArrayList<Integer> listerSuccesseurs(int n) {
		ArrayList<Integer> result = new ArrayList<Integer>();
		int pos=-1;
		for(int i=0;i<nbNoeuds;i++)
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				pos=i;
			}
		}
		if (pos==-1)
			System.out.println("erreur noeud inexistant");

		int	lignesize=graph.getLine(pos).size();
		for(int j=0;j<lignesize;j++)
		{
			if( graph.get(pos, j).getValeur() )
				result.add(tabnoeuds.get(j).valeur);

		}
		return result;
	}



	@Override
	public ArrayList<Arc> listerArcsEntrants(int n) {
		ArrayList<Arc> result = new ArrayList<Arc>();
		int taillelistearcs;	
		int pos=-1;
		for(int i=0;i<nbNoeuds;i++)
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				pos=i;
			}
		}
		if (pos==-1)
			System.out.println("erreur noeud inexistant");

		for(int j=0;j<nbNoeuds;j++)
		{
			if( graph.get(j,pos).getValeur() )
			{
				taillelistearcs= graph.get(j,pos).getListe().size();
				for(int k=0;k<taillelistearcs;k++)
					result.add(new Arc(j,n, graph.get(j,pos).listeIdArc.get(k)));
			}

		}
		return result;

	}

	@Override
	public ArrayList<Arc> listerArcsSortants(int n) {
		int taillelistearcs;	
		ArrayList<Arc> result = new ArrayList<Arc>();
		int pos=-1;
		for(int i=0;i<nbNoeuds;i++)
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				pos=i;
			}
		}
		if (pos==-1)
			System.out.println("erreur noeud inexistant");

		for(int j=0;j<nbNoeuds;j++)
		{
			if( graph.get(pos,j).getValeur() )
			{
				taillelistearcs= graph.get(pos,j).getListe().size();
				for(int k=0;k<taillelistearcs;k++)
					result.add(new Arc(n, j, graph.get(pos,j).listeIdArc.get(k)));
			}

		}
		return result;
	}

	@Override
	public String toString() {
		String result =new String("0 ");
		//PREMIERE LIGNE
		for(int i = 0;i<nbNoeuds;i++)
		{	

			result+=String.valueOf(tabnoeuds.get(i).getValeur());

		}
		result+="\n";
		//CORPS
		for(int i = 1;i<=nbNoeuds;i++)
		{
			result+=String.valueOf(tabnoeuds.get(i-1).getValeur())+" ";
			for(int j = 0;j<nbNoeuds;j++)
			{
				if(graph.get(i-1,j).getValeur())
					result+="V";
				else
					result+="F";
			}
			result+="\n";
		}
		//tableau
		for(int i =0; i<tabnoeuds.size();i++)
			result+=i+":"+String.valueOf(tabnoeuds.get(i).getValeur())+";";
		result+="\n";
		result+="nb noeuds : "+nbNoeuds+"\n";
		result+="nb arcs : "+nbArc+"\n";



		return result;

	}


}