
public class Matou implements PileDonnee
{

	// Le nom et la couleur du chat 
	// 
	private String nom;
	private String couleur;


	public Matou(String n, String c)
	{
		nom=n;
		couleur=c;
	}

	public void affiche()
	{
		System.out.println("Le chat se nomme " + nom + " et sa couleur est " + couleur);
	}
  


}
