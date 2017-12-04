import java.net.*;
import java.io.*;

public class servertu
{
	public static void main(String[] args)throws IOException
	{ServerSocket s2=new ServerSocket(2346);
	while(true)
	{Socket connectionsocket=s2.accept();
	BufferedReader messagefromloadbalancer=new BufferedReader(new InputStreamReader(connectionsocket.getInputStream()));
	String sentence=messagefromloadbalancer.readLine();
	System.out.println("received from client:"+sentence);}
}