import java.io.*;
import java.net.*;
import java.util.Arrays;
// import java.lang.*;

public class ClientTCP {
  public static void main(String[] args) throws IOException {

    Socket clientSocket = null;
    PrintWriter out = null;
    BufferedReader in = null;
    int port;

    port = Integer.parseInt(args[1]);
    System.out.println("port : " + port);

    try {
      clientSocket = new  Socket(args[0],port);
      out = new PrintWriter(clientSocket.getOutputStream(),true);
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    } catch (UnknownHostException e) {
      System.err.println("Don't know about host: " + args[0]);
      System.exit(1);
    } catch (IOException e) {
      System.err.println("Couldn't get I/O for " + "the connection to: "
			 + args[0]);
      System.exit(1);
    }

    BufferedReader stdIn = new BufferedReader(
			       new InputStreamReader(System.in));
    String userInput;
    char[] buf = new char[64];
    int r;

    // Lecture de la socket
    r = in.read(buf, 0, 64); // Attention, pas de \n envoye par le serveur
			     // donc pas de messageServeur = in.readLine();
    System.out.print(buf);   // Affichage

    String msg="";
    while ((userInput = stdIn.readLine()) != null) {
      // Envoi sur la socket
    	out.print(userInput);
    	out.flush();
      // ??????
      // Lecture de la socket et affichage
    	buf = new char[64];
    	r = in.read(buf, 0, 64);
    	//msg=Arrays.toString(buf);
  
    	System.out.print("Message recu"+new String(buf));
    }

    out.close();
    in.close();
    stdIn.close();
    clientSocket.close();
  }
}

