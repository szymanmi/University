import View.Wyswietlacz;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.ParseException;

public class App {
	public static void main(String[] args) throws ParserConfigurationException, SAXException, ParseException, IOException {
		Wyswietlacz wyswietlacz = new Wyswietlacz();
		while(true){
			wyswietlacz.calculate();
		}
	}

}
