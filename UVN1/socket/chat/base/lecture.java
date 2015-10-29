import java.io.*;

import java.net.*;


public class lecture {
    public static void main(String[] args) {
        try {
            BufferedWriter out = new BufferedWriter(new FileWriter(args[0]));
            InetAddress addr = InetAddress.getLocalHost();
            String hostname = addr.getHostName();
            out.write(hostname);
            out.write(args[1]);
            out.close();
        } catch (IOException e) {
        }

        try {
            BufferedReader in = new BufferedReader(new FileReader(args[2]));
            String machine;
            String port;
            machine = in.readLine();
            port = in.readLine();
            System.out.println(machine);
            System.out.println(port);
            in.close();
        } catch (IOException e) {
        }
    }
}
