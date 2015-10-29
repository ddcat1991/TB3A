
import java.rmi.*;


public class Creation
{


	// Port permettant d'acceder a rmiregistry
	//
	static String portRmiregistry;


	public Creation (String Machine)
	{
		try
		{
			String nomService = "//" + Machine + ":" + portRmiregistry + "/PileServeur";
			System.out.println (" Connection au service : " + nomService);
			UsinePile usine = (UsinePile) Naming.lookup (nomService);


			// Invocations de l'usine
			//
			Pile p = usine.creation_pile("mapile", 10);
			Toutou chien1 = new Toutou(12,54);
			Matou chat1 = new Matou("minou","noir");

			p.empiler(chat1);
			p.empiler(chien1);
			System.out.println ("Taille courante = " + p.lire_taille_courante() + "; Taille max = " + p.lire_taille_max() );
				
		}

		catch (RemoteException e)
		{
			System.out.println ("RemoteException: " + e.getMessage ());
			e.printStackTrace ();
		}
		catch (Exception e)
		{
			System.out.println ("Exception: " + e.getMessage ());
			e.printStackTrace ();
		}

	}



	public static void main (String args[])
	{
		if (args.length != 2)
		{
			System.out.println ("Deux arguments : port-rmiregistry machine  ! ");
			System.exit (2);
		}

		portRmiregistry=args[0];

		MyHostName machine = new MyHostName(args[1]);
		new Creation (machine.QualifiedHost());
	}


}
