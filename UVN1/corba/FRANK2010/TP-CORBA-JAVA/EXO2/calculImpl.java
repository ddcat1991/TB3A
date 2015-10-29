

package tpcorba.exo2;

import org.omg.CORBA.*;
import java.lang.*;


public class calculImpl extends calculPOA
	{


	private	double contenu;


	public calculImpl()
		{
		contenu=0;
		}


	public double memoire()
		{
		return contenu;
		}



	***


	public void diviseMemoire(*** valeur) 
		throws divisionParZero
		{
		if(valeur==0)
			throw new divisionParZero();

		contenu=contenu/valeur;
		}


        public void incrementer(IntHolder data)
                {
                System.out.println("Invocation d'incrementer()");

                data.value=data.value+1;
                }


        public void decrementer(IntHolder data)
                {
                System.out.println("Invocation de decrementer()");

                data.value=data.value-1;
                }




	}
