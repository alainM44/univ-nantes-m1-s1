import java.util.ArrayList;
import java.util.Collection;



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
	
		graph.get(n1,n2).listeIdArc =new ArrayList<Integer>();
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
		for(int i=0; i<nbNoeuds-1;i++) // parcours de n
		{
			if (tabnoeuds.get(i).getValeur() ==n)
			{
				tabnoeuds.remove(i);
				pos=i;
			}
		}

		graph.suppLigne(pos); //en O de N
		nbNoeuds--;
	}
	
	//PAS DANS LE SOUJET
	@Override
	public ArrayList<Arc> listeArcs() {
		ArrayList<Integer> result = new ArrayList<Integer>();
		int nblignes =graph.getNbLignes();
		int listsize;
		int lignesize;
		for(int i=1;i<=nblignes;i++)
		{
			lignesize=graph.getLine(i).size();
			for(int j=1;i<=lignesize;j++)
			{
				listsize =graph.getLine(i).get(j).getListe().size();
				for(int k=1;i<=listsize;j++)
				{
					result.add(graph.getLine(i).get(j).getListe().get(k));
				}

			}
		}


		return null;//result;
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
				result.addAll( (Collection)(graph.get(j,pos).listeIdArc));//!!!
			
		}
		return result;
	
	}

	@Override
	public ArrayList<Arc> listerArcsSortants(int n) {
		
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
				result.addAll( (Collection)(graph.get(pos, j).listeIdArc));//!!!
			
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

//	public String put_tab(){
//		String result = new String();
//
//	}


}