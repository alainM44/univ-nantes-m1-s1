package main;
import java.util.List;
import java.util.ArrayList;


public class Bulle 
{

	private void echanger(int[] t, int i, int j)
	{
		int aux;
		aux= t[i];
		t[i]= t[j];
		t[j] = aux;
		
	}
	
	public static void triBulle(List<Integer> tab)
	{
		 int aux;
		    int longueur=tab.size();
		    boolean inversion;		    
		    do
		        {
		        inversion=false;

		        for(int i=0;i<longueur-1;i++)
		            {
		            if(tab.get(i)>tab.get(i+1))
		                {
		                aux = tab.get(i);
		                tab.set(i, tab.get(i+1));
		                tab.set(i+1, aux);
		                inversion=true;
		                }
		            }
		         longueur--;
		         }
		    while(inversion);
	}
	
	 public void triBulle(ArrayList<Integer> tab )
	    {
		 int aux;
	    int longueur=tab.size();
	    boolean inversion;
	    
	    do
	        {
	        inversion=false;

	        for(int i=0;i<longueur-1;i++)
	            {
	            if(tab.get(i)>tab.get(i+1))
	                {
	                aux = tab.get(i);
	                tab.set(i, tab.get(i+1));
	                tab.set(i+1, aux);
	                inversion=true;
	                }
	            }
	         longueur--;
	         }
	    while(inversion);
	    }
	/*
    public void triBulle(int tableau[])
    {
    int longueur=tableau.length;
    boolean inversion;
    
    do
        {
        inversion=false;

        for(int i=0;i<longueur-1;i++)
            {
            if(tableau[i]>tableau[i+1])
                {
                echanger(tableau,i,i+1);
                inversion=true;
                }
            }
         longueur--;
         }
    while(inversion);
    }
    */
}
