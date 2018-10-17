import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class KolekcjaWalut {
	private List<Waluta> list = new ArrayList<Waluta>();
	private int totalWaluty;

	KolekcjaWalut() throws ParserConfigurationException, SAXException, IOException, ParseException {
		WebClient client = new WebClient();
		totalWaluty = client.getTotalWaluty();

		String[][] stringWaluty = client.getStringWaluty();
		NumberFormat format = NumberFormat.getInstance(Locale.FRANCE);
		for (int i = 0; i < totalWaluty; i++) {
			list.add(new Waluta(stringWaluty[0][i], stringWaluty[1][i], format.parse(stringWaluty[2][i]).doubleValue(), Double.parseDouble(stringWaluty[3][i])));
		}

	}

	public int getTotalWaluty() {
		return totalWaluty;
	}

	public List<Waluta> getAll() {
		return list;
	}

	public Waluta searchForWaluta(String kod) {
		int i;
		for (i = 0; i < totalWaluty; i++) {
			if (list.get(i).getKodWaluty().equals(kod))
				break;
		}
		return list.get(i);
	}

}
