import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.io.StringReader;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;

public class ParserXML implements Parser{
	private NodeList listOfWaluty;
	private int totalWaluty;

	public ParserXML(String txt) throws ParserConfigurationException, IOException, SAXException {
		DocumentBuilder db = DocumentBuilderFactory.newInstance().newDocumentBuilder();
		InputSource is = new InputSource();
		is.setCharacterStream(new StringReader(txt));

		Document doc = db.parse(is);
		doc.getDocumentElement().normalize();

		listOfWaluty = doc.getElementsByTagName("pozycja");
		totalWaluty = listOfWaluty.getLength();
	}

	public int getTotalWaluty() {
		return totalWaluty;
	}

	public String[] parseNazwaWaluty() {
		String[] nazwaWaluty = new String[totalWaluty];
		for (int i = 0; i < totalWaluty; i++) {
			Node WalutaNode = listOfWaluty.item(i);
			Element WalutaElement = (Element) WalutaNode;
			NodeList nazwaWalutyList = WalutaElement.getElementsByTagName("nazwa_waluty");
			Element nazwaWalutyElement = (Element) nazwaWalutyList.item(0);
			NodeList textNW = nazwaWalutyElement.getChildNodes();
			nazwaWaluty[i] = ((Node) textNW.item(0)).getNodeValue().trim();
		}
		return nazwaWaluty;
	}

	public String[] parseKodWaluty() {
		String[] kodWaluty = new String[totalWaluty];
		for (int i = 0; i < totalWaluty; i++) {
			Node WalutaNode = listOfWaluty.item(i);
			Element WalutaElement = (Element) WalutaNode;
			NodeList kodWalutyList = WalutaElement.getElementsByTagName("kod_waluty");
			Element kodWalutyElement = (Element) kodWalutyList.item(0);
			NodeList textKW = kodWalutyElement.getChildNodes();
			kodWaluty[i] = ((Node) textKW.item(0)).getNodeValue().trim();
		}
		return kodWaluty;
	}

	public String[] parsePrzelicznikWaluty() {
		String[] przelicznikWaluty = new String[totalWaluty];
		for (int i = 0; i < totalWaluty; i++) {
			Node WalutaNode = listOfWaluty.item(i);
			Element WalutaElement = (Element) WalutaNode;
			NodeList przelicznikWalutyList = WalutaElement.getElementsByTagName("przelicznik");
			Element przelicznikWalutyElement = (Element) przelicznikWalutyList.item(0);
			NodeList textPW = przelicznikWalutyElement.getChildNodes();
			przelicznikWaluty[i] = ((Node) textPW.item(0)).getNodeValue().trim();
		}
		return przelicznikWaluty;
	}

	public String[] parseKursWaluty() {
		String[] kursWaluty = new String[totalWaluty];
		for (int i = 0; i < totalWaluty; i++) {
			Node WalutaNode = listOfWaluty.item(i);
			Element WalutaElement = (Element) WalutaNode;
			NodeList kursSredniList = WalutaElement.getElementsByTagName("kurs_sredni");
			Element kursSredniElement = (Element) kursSredniList.item(0);
			NodeList textKS = kursSredniElement.getChildNodes();
			kursWaluty[i] = ((Node) textKS.item(0)).getNodeValue().trim();
		}
		return kursWaluty;
	}
}
