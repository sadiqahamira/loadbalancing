import java.net.*;
import java.io.*;

public class client
{
		public static void main(String[] args) throws IOException
		{Socket myClient=new Socket("192.168.154.128",1234);
		DataOutputStream outtoserver = new DataOutputStream(myClient.getOutputStream());
		BufferedReader infromuser= new BufferedReader(new InputStreamReader(System.in));
		String sentence=infromuser.readLine();
		outtoserver.writeBytes(sentence);
		myClient.close();
		}
}