
import java.rmi.*;


public class Client 
{


	// Port permettant d'acceder a rmiregistry
	//
	static String portRmiregistry;


	public Client (String Machine)
	{
		try
		{
			String nomService = "//" + Machine + ":" + portRmiregistry + "/PileServeur";
			System.out.println (" Connection au service : " + nomService);
			UsinePile usine = (UsinePile) Naming.lookup (nomService);


			// Invocations de l'usine
			//
			Pile p = usine.creation_pile("mapile", 10);
			p.empiler(100);
			p.empiler(101);
			System.out.println ("Taille courante = " + p.lire_taille_courante() + "; Taille max = " + p.lire_taille_max() );
			System.out.println ("Element en haut de la pile : " + p.haut());
				
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
		new Client (machine.QualifiedHost());
	}


}
