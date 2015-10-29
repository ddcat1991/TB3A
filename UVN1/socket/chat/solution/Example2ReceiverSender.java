import java.io.*;
import java.net.*;


public class Example2ReceiverSender {
    public static void main(String[] args) {

        String machinedist;
        String portdist;

        // This code takes the first argument and writes the arguments
        // on how to contact the current process : its machine name + port
        try {
            BufferedWriter out = new BufferedWriter(new FileWriter(args[0]));
            InetAddress addr = InetAddress.getLocalHost();
            String hostname = addr.getHostName();

            System.out.println("" );
            System.out.println("___________________________________________________________________________" );
            System.out.println("Writing  my ID in file : " + args[0]);
            System.out.println("I'm running on host " + hostname +
                " and waiting on port " + args[1]);
            System.out.println("___________________________________________________________________________" );
            out.write(hostname);
            out.write("\n");
            out.write(args[1]);
            out.close();
        } catch (IOException e) {
        }

        // we need to be sure that the other process has written its address
        try {
            System.out.println("");
            System.out.println("delaying for 5 seconds");
            System.out.println("");
            Thread.sleep(5000);
        } catch (Exception ex) {
        }

        try {
            BufferedReader in = new BufferedReader(new FileReader(args[2]));
            machinedist = in.readLine();
            portdist = in.readLine();
            in.close();

            System.out.println("" );
            System.out.println("___________________________________________________________________________" );
            System.out.println("I'll contact  host " + machinedist +
                " on port " + portdist);
            System.out.println("___________________________________________________________________________" );

            InetAddress receiverHost = InetAddress.getByName(machinedist);
            int receiverPort = Integer.parseInt(portdist);
            int myPort = Integer.parseInt(args[1]);

            String message = args[3];
            MyDatagramSocket mySocket = new MyDatagramSocket(myPort);

            // instantiates a datagram socket for both sending
            // and receiving data
            // First wait to receive a datagram from the socket
            for (int i = 0; i < 10; i++) {
                System.out.println(mySocket.receiveMessage());

                // Now send a message to the other process.
                mySocket.sendMessage(receiverHost, receiverPort, message);
            }

            // the communication is over and we can release the socket : a ressource 
            mySocket.close();
        } // end try
        catch (Exception ex) {
            ex.printStackTrace();
        } //end catch
    } //end main 
} //end class
