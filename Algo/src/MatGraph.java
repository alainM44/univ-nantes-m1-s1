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
	public int ajouterA(int n1, int n2) {
		idGenerator++;
		graph.get(n1, n2).ajouterArc(idGenerator);
		//	tabnoeuds.get(n1).setNbArc(n2)
		graph.get(tabnoeuds.get(n1-1).valeur,tabnoeuds.get(n2-1).valeur).setValeur(true);
		
		return idGenerator;
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

		tabnoeuds.add(new Encapsulateur<Integer>(n-1));

	}

	@Override
	public ArrayList<Arc> listeArcs() {
		ArrayList<Integer> result = new ArrayList<Integer>();
		int nblignes =graph.getNbLignes();
		int lignesize;
		int listsize;
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
		for(int i=1;i<=tabnoeuds.size();i++)
			result.add(tabnoeuds.get(i).valeur);
		return null;
	}



	@Override
	public ArrayList<Integer> listerPredecesseurs(int n) {

		return null;
	}

	@Override
	public ArrayList<Integer> listerSuccesseurs(int n) {

		return null;
	}

	@Override
	public void supprimerA(int id, int n1, int n2) {
		// TODO Auto-generated method stub

	}

	@Override
	public void supprimerN(int n) {


	}

	@Override
	public ArrayList<Arc> listerArcsEntrants(int n) {
		ArrayList<Arc> result = new ArrayList<Arc>();
		int listsize;
		for(int i=1;i<=n;i++)
		{	
			if(graph.getLine(i).get(n).getValeur())
			{
				listsize=graph.getLine(i).get(n).getListe().size();
				for(int j=1;j<=listsize;j++)
					result.add(new Arc(i, n,graph.getLine(i).get(n).getListe().get(j) ));
			}

		}
		return null;


	}

	@Override
	public ArrayList<Arc> listerArcsSortants(int n) {
		ArrayList<Arc> result = new ArrayList<Arc>();
		int lignesize = graph.getLine(n).size();
		int listsize;
		for(int i=1;i<=lignesize;i++)
		{	
			if(graph.getLine(n).get(i).getValeur())
			{
				listsize=graph.getLine(n).get(i).getListe().size();
				for(int j=1;j<=listsize;j++)
					result.add(new Arc(n, i,graph.getLine(n).get(i).getListe().get(j) ));
			}
		}
		return result;
	}

	@Override
	public String toString() {
		String result =new String();
		//PREMIERE LIGNE
		for(int i = 0;i<=nbNoeuds;i++)
		{	
			if (i==0)
				result+=i+" ";
			else
				result+=i;
		}
		result+="\n";
		//CORPS
		for(int i = 1;i<=nbNoeuds;i++)
		{
			result+=i+" ";
			for(int j = 0;j<nbNoeuds;j++)
			{
				if(graph.get(i-1,j).getValeur())
					result+="V";
				else
					result+="F";
			}
			result+="\n";
		}
		return result;
	}


}