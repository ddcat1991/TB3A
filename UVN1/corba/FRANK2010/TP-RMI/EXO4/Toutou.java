
public class Toutou implements PileDonnee
{

	// L'age et la taille d'un chien
	// 
	private int age;
	private int taille;


	public Toutou(int a, int t)
	{
		age=a;	
		taille=t;
	}

	public void affiche()
	{
		System.out.println("Le chien a " + age + " ans et mesure " + taille + " centimetres");
	}
  


}
