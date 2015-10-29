import java.net.*;
import java.io.*;
import java.util.*;

/**
 * A wrapper class of Socket which contains 
 * methods for sending and receiving messages
 * @author M. L. Liu
 */
public class MyStreamSocket extends Socket {
   private Socket  socket;
   private BufferedReader input;
   private PrintWriter output;

   MyStreamSocket(InetAddress acceptorHost,
                  int acceptorPort ) throws SocketException,
                                   IOException{
      socket = new Socket(acceptorHost, acceptorPort );
      setStreams( );

   }

   MyStreamSocket(Socket socket)  throws IOException {
      this.socket = socket;
      setStreams( );
   }

   private void setStreams( ) throws IOException{
      // get an input stream for reading from the data socket
      InputStream inStream = socket.getInputStream();
      input = 
         new BufferedReader(new InputStreamReader(inStream));
      OutputStream outStream = socket.getOutputStream();
      // create a PrinterWriter object for character-mode output
      output = 
         new PrintWriter(new OutputStreamWriter(outStream));
   }

   public void sendMessage(String message)
   		          throws IOException {	
      output.println(message);   
      //The ensuing flush method call is necessary for the data to
      // be written to the socket data stream before the
      // socket is closed.
      output.flush();               
   } // end sendMessage

   public String receiveMessage( )
		throws IOException {	
      // read a line from the data stream
      String message = input.readLine( );  
      return message;
   } //end receiveMessage
   
   public String[] receiveMessageTokens( int nb)
	throws IOException {	
 // read a line from the data stream
   	int count = 0;
    String message = input.readLine( );  
    System.out.println("message received " + message);
    
    String[] tokens = message.split("\\s");
    for (int x=0; x<tokens.length; x++)
        System.out.println(tokens[x]);
   return tokens;
} //end receiveMessage


} //end class
