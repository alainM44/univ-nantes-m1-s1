package main;
import java.awt.geom.GeneralPath;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Vector;


public class main<E> 
{


	public static void main(final String[] args) 
	{
		long begin;
		long end;
		float time;
		float moyenne;
		moyenne=0f;
		
		List<Integer> sortedlist = new Vector<Integer>();
		List<Integer> randomlist = new Vector<Integer>();
		List<Integer> sortedinversedlist = new Vector<Integer>();


//		List<Integer> sortedlist = new LinkedList<Integer>();
//		List<Integer> randomlist = new LinkedList<Integer>();
//		List<Integer> sortedinversedlist = new LinkedList<Integer>();

//		List<Integer> sortedlist = new ArrayList<Integer>();
//		List<Integer> randomlist = new ArrayList<Integer>();
//		List<Integer> sortedinversedlist = new ArrayList<Integer>();
//		
		System.out.println("Structure triée (meilleurs cas) :");
		genereSortedList(sortedlist, 10);
		System.out.println(sortedlist.toString());
		begin =System.currentTimeMillis();
		Bulle.triBulle(sortedlist);
		end =System.currentTimeMillis();
		time = ((float)(end - begin))/1000f;
		moyenne += time;
				System.out.println(sortedlist.toString());
		System.out.println("Durée de l'opération :"+time);

		System.out.println();
		System.out.println("Structure aléatoire :");

		for(int i = 0; i<3; i++)
		{
			genereRandomList(randomlist, 10, 100);
			System.out.println(randomlist.toString());
			begin =System.currentTimeMillis();
			Bulle.triBulle(randomlist);
			end =System.currentTimeMillis();
			time = ((float)(end - begin))/1000f;
			System.out.println(randomlist.toString());
			System.out.println("Durée de l'opération :"+time);
			randomlist.clear();
		}
				
		System.out.println("Moyenne des cas aléatoires:"+ time/3);
		
		System.out.println();
		
		System.out.println("Structure triée à l'envers (pire cas) :");
		genereSortedInversedList(sortedinversedlist, 10);
		System.out.println(sortedinversedlist.toString());
		begin =System.currentTimeMillis();
		Bulle.triBulle(sortedinversedlist);
		end =System.currentTimeMillis();
		time = ((float)(end - begin))/1000f;
		System.out.println(sortedinversedlist.toString());
		System.out.println("Durée de l'opération :"+time);

	}
	public static void genereSortedList(List<Integer> l, int taille)
	{
		for(int i = 0; i<taille; i++)
			l.add(i);

	}
	public static void genereSortedInversedList(List<Integer> l, int taille)
	{
		for(int i=taille; i>0; i--)
			l.add(i);
	}
	public static void genereRandomList(List<Integer> l, int taille,int max)
	{
		Random ran = new Random();
		for(int i = 0; i<taille; i++)
			l.add(ran.nextInt(max));
	}

}
