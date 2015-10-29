
import java.rmi.*;


//  HelloClient : client qui va lire un message genere par le serveur
//
public class HelloClient 
{


	// Variable qui stocke ledit message
	//
	String message = "";


	// Port permettant d'acceder a rmiregistry
	//
	static String portRmiregistry;


	// Constructeur pour HelloClient
	//
	public HelloClient (String Machine)
	{
		try
		{
			// Recuperer la reference d'objet du serveur a interroger
			// a partir d'un nom symbolique. Cette reference est 
			// renvoyee par le service de nom de JAVA : rmiregistry
			// 
			// La structure d'un nom est :  //machine:port/nom
			// "machine" est le nom de la machine ou tourne le service
			// et "nom" correspond au nom du service.
			// le "port" est le numero de port
			// ou rmiregistry est en attente des requetes
			// pour le service de noms
			//
			//
			String nomService = "//" + Machine + ":" + portRmiregistry + "/HelloServeur";
			System.out.println (" Connection au service : " + nomService);
			Hello obj = (Hello) Naming.lookup (nomService);

			// Finalement, on peut invoquer la methode de l'objet
			// qui est heberge par le serveur
			//
			message = obj.lireMessage ();
			System.out.println ("Le message est : " + message );
		}

		catch (Exception e)
		{
			System.out.println ("Hello exception: " + e.getMessage ());
			e.printStackTrace ();
		}


	}



	//   Methode principale
	//
	public static void main (String args[])
	{
		if (args.length != 2)
		{
			System.out.println ("Deux arguments : port-rmiregistry machine  ! ");
			System.exit (2);
		}

		portRmiregistry=args[0];

		MyHostName machine = new MyHostName(args[1]);
		new HelloClient (machine.QualifiedHost());
	}


}
