package main;

import java.util.List;

public interface GrapheOriente {
	//public void supprimer();
public void ajouterN (int n);

public void supprimerN(int n);

public void ajouterA(int id, int n1, int n2);

public void supprimerA(int id, int n1, int n2);

public List<Integer> listerSuccesseurs(int n);

public List<Integer> listerPredecesseurs(int n);

public List<Integer> listerArcsEntrants(int n);

public List<Integer> listerArcsSortants(int n);

public int NombreNoeuds();

}