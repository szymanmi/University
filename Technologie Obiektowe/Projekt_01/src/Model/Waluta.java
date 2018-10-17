package Model;

public class Waluta {
	private String kodWaluty;
	private String nazwaWaluty;
	private double przelicznik;
	private double kursSredni;

	public Waluta(String nazwaWaluty, String kodWaluty, double kursSredni, double przelicznik) {
		this.kodWaluty = kodWaluty;
		this.nazwaWaluty = nazwaWaluty;
		this.przelicznik = przelicznik;
		this.kursSredni = kursSredni;
	}

	public String getKodWaluty() {
		return kodWaluty;
	}

	public String getNazwaWaluty() {
		return nazwaWaluty;
	}

	public double getPrzelicznik() {
		return przelicznik;
	}

	public double getKursSredni() {
		return kursSredni;
	}

	public void setPrzelicznik(double przelicznik) {
		this.przelicznik = przelicznik;
	}

	public void setKursSredni(double kursSredni) {
		this.kursSredni = kursSredni;
	}
}
