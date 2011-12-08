package Graphe;
import java.util.ArrayList;

/**
 * 
 * @author alain
 *
 *Necessaire pour la définition de MatGraph. Seules les opérations necessaires à cet ustage sont définies içi.
 * @param <Type>
 */

public class ArrayList2D<Type>
{
	ArrayList<ArrayList<Type>>  array;

	public ArrayList2D()
	{
		array = new ArrayList<ArrayList<Type>>();
	}

	//ajouter une ligne en fin
	public void addLigne()
	{
		array.add(new ArrayList<Type>());
	}

	//Ajoute une ligne à la position indiquée.
	public void addLigne(int ligne)
	{
		if (ligne >= 0 && ligne < this.getNbLignes())
			array.add(ligne, new ArrayList<Type>());
	}

	public void suppLigne(int ligne){
		array.remove(array.get(ligne));
	}
	
	public void addCol(int x)
	{
		if (x >= 0 && x < this.getNbLignes())
			array.get(x).add(null);
	}
	public void suppCol(int x)
	{
		for(int i=0; i<getNbLignes();i++)
			//if (x <=  this.getNbLignes())
				array.get(i).remove(x);
		}
	

	public void addCol(int x, int y)
	{
		array.get(x).add(y, null);
	}

	public void addCol(int x, int y, Type T)
	{
		array.get(x).add(y, T);
	}

	public ArrayList<Type> getLine(int ligne)
	{
		return array.get(ligne);
	}
	
	
	public Type get(int ligne, int col)
	{
		return array.get(ligne).get(col);
	}

	public void set(int row, int col, Type data)
	{
		if (col >= 0 && col < this.getNbCols())
			array.get(row).set(col,data);
	}

	public int getNbLignes()
	{
		return array.size();
	}

	public int getNbCols()
	{
		return array.get(0).size();
	}

}

