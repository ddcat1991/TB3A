
public interface Compte extends java.rmi.Remote 
{

	void debiter(double montant)
		throws java.rmi.RemoteException;

	void crediter(double montant)
		throws java.rmi.RemoteException;

	double lire_solde()
		throws java.rmi.RemoteException;

};


