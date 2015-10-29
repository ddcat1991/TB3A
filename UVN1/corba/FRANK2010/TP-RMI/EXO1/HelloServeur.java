
import java.io.*;
import java.net.*;
import java.rmi.*;
import java.rmi.server.*;


// On specifie dans la definition de la classe que 
// celle-ci implante l'interface Hello et que ses
// instances seront des objets repartis
//
public class HelloServeur extends UnicastRemoteObject     
	  implements Hello
{

	// Attribut qui stocke le message qui sera renvoye 
	// aux clients 
	//
	String chaine; 
  

	// Ceci est l'implantation de la methode qui 
	// sera invoquee de facon (eventuellement) 
	// distante par les clients
	//
	public String lireMessage() throws RemoteException 
	{
		return chaine ;
	}


	// Le constructeur pour la classe 
	//
	public HelloServeur() throws RemoteException {}


	// Methode principale
	//
	public static void main(String args[]) throws IOException
	{
     
		if (args.length != 2)
		{
			System.out.println("Deux arguments : port-rmiregistry Message ! ");
			System.exit(1);
		}
      

		// Creation et installation du security manager
		//
		if (System.getSecurityManager() == null) 
			System.setSecurityManager(new RMISecurityManager());
 

		try 
		{

			// Creation de l'objet qui va etre invoque par les clients 
			//
			HelloServeur MonServeur = new HelloServeur();


			// On initialise l'attribut de l'objet avec le message passe
			// en parametre
			//
			MonServeur.chaine = args[1];


			// On publie le service au serveur de nom de JAVA : rmiregistry.
			// On utilise pour cela un nom symbolique que l'on va associer 
			// a l'objet.
			//
			// La structure d'un nom est :  //machine:port/nom
			// "machine" est le nom de la machine ou tourne le serveur
			// et "nom" correspond au nom du service.
			// "port" est le numero de port utilise par 
			// rmiregistry pour attendre les requetes destine au
			// service de noms.
			//
			MyHostName machine = new MyHostName();

                        String nomService = "//" + machine.QualifiedHost() + ":" + args[0] + "/HelloServeur";

			Naming.rebind(nomService, MonServeur);

			System.out.println("HelloServeur enregistre : " + nomService);
		} 
		catch (RemoteException e) 
		{
			System.out.println("HelloServeur err: " + e.getMessage());
			e.printStackTrace();
		}

	}
}
