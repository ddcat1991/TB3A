
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
			String nomService = "//" + Machine + ":" + portRmiregistry + "/CompteServeur";
			System.out.println (" Connection au service : " + nomService);

			// Se connecter à un objet de type compte et invoquer les methodes
			//		- debiter/crediter
			//		- lire_solde
			***
				
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
