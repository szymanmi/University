import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.ParseException;
import java.util.Scanner;

public class Wyswietlacz {
	private Kalkulator kalkulator = new Kalkulator();

	public Wyswietlacz() throws ParserConfigurationException, SAXException, ParseException, IOException {
	}

	public void calculate() {
		String kod1, kod2;
		Scanner scanner = new Scanner(System.in);
		Spr sprawdzacz = new SprTxt();
		do{
			System.out.println("podaj kod pierwszej waluty");
			kod1 = scanner.next();
		}while(!sprawdzacz.sprawdz(kalkulator.getAll(), kod1));

		do{
			System.out.println("podaj kod drugiej waluty");
			kod2 = scanner.next();
		}while(!sprawdzacz.sprawdz(kalkulator.getAll(), kod2));

		System.out.println("Podaj wartosc");
		int val = scanner.nextInt();

		System.out.println(kalkulator.przelicz(kod1, kod2, val));
	}

	public void showAll(){
		for(Waluta w : kalkulator.getAll().getAll()) {
			System.out.println(w.getNazwaWaluty());
			System.out.println(w.getKodWaluty());
			System.out.println();
		}
	}

}



