package Controller;


import Model.Save;
import View.PaintWindow;
import org.json.simple.parser.ParseException;

import java.io.IOException;

public class ShapeController {
	private PaintWindow pw;


	public ShapeController(PaintWindow pw) {
		this.pw = pw;
	}


	public void addNewRectangle(String x, String y, String h, String w, String c) throws IOException, ParseException {
		Save save = new Save();
		save.saveRectangle(Integer.parseInt(x), Integer.parseInt(y), Integer.parseInt(h), Integer.parseInt(w), c);
		pw.refresh();
	}

	public void addNewCircle(String x, String y, String r, String c) throws IOException, ParseException {
		Save save = new Save();
		save.saveCircle(Integer.parseInt(x), Integer.parseInt(y), Integer.parseInt(r), c);
		pw.refresh();
	}

	public void addNewLine(String x1, String y1, String x2, String y2, String c) throws IOException, ParseException {
		Save save = new Save();
		save.saveLine(Integer.parseInt(x1), Integer.parseInt(y1), Integer.parseInt(x2), Integer.parseInt(y2), c);
		pw.refresh();
	}

}
