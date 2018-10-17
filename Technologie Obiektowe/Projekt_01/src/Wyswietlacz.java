import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.ParseException;
import java.util.Scanner;

public class Wyswietlacz {
	private Kalkulator kalkulator = new Kalkulator();

	private Wyswietlacz() throws ParserConfigurationException, SAXException, ParseException, IOException {
	}

	private void calculate() {
		String kod1, kod2;
		Scanner scanner = new Scanner(System.in);
		Spr sprawdzacz = new SprTxt();
		do{
			System.out.println("podaj kod1");
			kod1 = scanner.next();
		}while(!sprawdzacz.sprawdz(kalkulator.getAll(), kod1));

		do{
			System.out.println("podaj kod2");
			kod2 = scanner.next();
		}while(!sprawdzacz.sprawdz(kalkulator.getAll(), kod2));

		System.out.println("Podaj wartosc");
		int val = scanner.nextInt();

		System.out.println(kalkulator.przelicz(kod1, kod2, val));
	}

	private void showAll(){
		for(Waluta w : kalkulator.getAll().getAll()) {
			System.out.println(w.getNazwaWaluty());
			System.out.println(w.getKursSredni());
			System.out.println();
		}
	}

	public static void main(String[] args) throws ParserConfigurationException, SAXException, ParseException, IOException {
		Wyswietlacz wyswietlacz = new Wyswietlacz();
		wyswietlacz.showAll();
		wyswietlacz.calculate();
	}
}



