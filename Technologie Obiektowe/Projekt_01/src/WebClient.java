import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.Scanner;

public class WebClient {

	private int totalWaluty;
	private NodeList listOfWaluty;
	private String[][] stringWaluty = new String[4][];

	public WebClient() throws IOException, ParserConfigurationException, SAXException {
		URL url = new URL("http://www.nbp.pl/kursy/xml/lasta.xml");
		InputStream stream = url.openStream();
		Scanner s = new Scanner(stream).useDelimiter("\\A");
		String result = s.hasNext() ? s.next() : "";


		Parser parser = new ParserXML(result);
		totalWaluty = parser.getTotalWaluty();


		stringWaluty[0] = parser.parseNazwaWaluty();
		stringWaluty[1] = parser.parseKodWaluty();
		stringWaluty[2] = parser.parseKursWaluty();
		stringWaluty[3] = parser.parsePrzelicznikWaluty();
	}

	public String[][] getStringWaluty() {
		return stringWaluty;
	}

	public int getTotalWaluty() {
		return totalWaluty;
	}



	public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
		WebClient web = new WebClient();

	}
}
