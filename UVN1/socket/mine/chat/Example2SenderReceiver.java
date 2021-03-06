import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.*;

/**
 * This example illustrates a process which sends then receives
 * using a datagram socket.
 * @author M. L. Liu
 */
public class Example2SenderReceiver {
// An application which sends then receives a message using
// connectionless datagram socket.
// Four command line arguments are expected, in order: 
//    <domain name or IP address of the receiver>
//    <port number of the receiver's datagram socket>
//    <port number of this process's datagram socket>
//    <message, a string, to send>

	//args[0]  -- client id 
	//args[1]  -- port number
	//args[2]  -- dest id
	//args[3]  -- message
	public static void main(String[] args) {
		if (args.length != 4)
			System.out
					.println("This program requires four command line arguments");
		else {
			try {
				BufferedWriter out = new BufferedWriter(new FileWriter(args[0]));
				InetAddress address = InetAddress.getLocalHost();
				String hostname = address.getHostName();
				out.write(hostname);
				out.write("\n");
				out.write(args[1]);    //port number
				out.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			try {
				System.out.println("delaying for 5 seconds");
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			try {
				
				//InetAddress receiverHost = InetAddress.getByName(args[0]);
				//int receiverPort = Integer.parseInt(args[1]);
				//int myPort = Integer.parseInt(args[2]);
				String message = args[3];
				int myPort = Integer.parseInt(args[1]);				
				
				BufferedReader in = new BufferedReader(new FileReader(args[2]));
				String hostdest = in.readLine();
				InetAddress receiverHost = InetAddress.getByName(hostdest);
				int receiverPort = Integer.parseInt(in.readLine());
				MyDatagramSocket mySocket = new MyDatagramSocket(myPort);				
				// Now send a message to the other process.
				mySocket.sendMessage(receiverHost, receiverPort, message);				
				System.out.println(mySocket.receiveMessage());

				
				mySocket.close();
			} // end try
			catch (Exception ex) {
				ex.printStackTrace();
			} // end catch
		} // end else
	} // end main

} //end class

