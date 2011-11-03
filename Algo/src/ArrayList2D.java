import java.util.ArrayList;

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
	/**
	 *  Ajoute une colone à la fin du tableau à la ligne x. Cette colone est initialisé à null.
	 */

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
	
	/**
	 * Ajoute une colone à la position y à la ligne x. Cette ligne est initialisé à null.
	 * @param x
	 * @param y
	 */
	public void addCol(int x, int y)
	{
		array.get(x).add(y, null);
	}
	/**
	 * Ajoute un élément à la ligne x et à la colonne y.
	 * @param x
	 * @param y
	 * @param T
	 */
	public void addCol(int x, int y, Type T)
	{
		array.get(x).add(y, T);
	}
	/**
	 * Recupère l'objet situé à la ligne row et à la colone col.
	 * @param row
	 * @param col
	 * @return 
	 * @return 
	 * @return
	 */
	public ArrayList<Type> getLine(int ligne)
	{
		return array.get(ligne);
	}
	
	
	public Type get(int ligne, int col)
	{
		return array.get(ligne).get(col);
	}
	/**
	 * Change l'objet situé à la ligne row et à la colone col.
	 * @param row
	 * @param col
	 * @param data
	 */
	public void set(int row, int col, Type data)
	{
		if (col >= 0 && col < this.getNbCols())
			array.get(row).set(col,data);
	}
	/**
	 * Retourne le nombre de ligne du tableau.
	 * @return
	 */
	public int getNbLignes()
	{
		return array.size();
	}
	/**
	 * Retourne le nombre de colone du tableau.
	 * @return
	 */
	public int getNbCols()
	{
		return array.get(0).size();
	}

}

