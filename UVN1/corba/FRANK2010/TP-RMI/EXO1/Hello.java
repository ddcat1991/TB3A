
// Definition de l'interface de l'objet distant
//
// Cette interface doit etre publique
// sinon les clients auront des pbs !!!
//

public interface Hello extends java.rmi.Remote 
{
	String lireMessage() throws java.rmi.RemoteException;
}


