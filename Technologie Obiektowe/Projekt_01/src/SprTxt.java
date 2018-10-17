public  class SprTxt implements Spr{
	public boolean sprawdz(KolekcjaWalut kolekcja, String txt) {
		for (int i = 0; i < kolekcja.getTotalWaluty(); i++)
			if (kolekcja.getAll().get(i).getKodWaluty().equals(txt))
				return true;

		return false;
	}



}
