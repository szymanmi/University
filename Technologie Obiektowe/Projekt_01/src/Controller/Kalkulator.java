package Controller;

import Model.KolekcjaWalut;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.ParseException;

public class Kalkulator {
	private KolekcjaWalut kolekcja = new KolekcjaWalut();

	public Kalkulator() throws ParserConfigurationException, SAXException, ParseException, IOException {


	}

	public double przelicz(String w1, String w2, double val) {
		return val * kolekcja.searchForWaluta(w1).getKursSredni() / kolekcja.searchForWaluta(w2).getKursSredni();
	}

	public KolekcjaWalut getAll(){
		return kolekcja;
	}

}
