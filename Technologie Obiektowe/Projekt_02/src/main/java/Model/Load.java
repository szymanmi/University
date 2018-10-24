package Model;


import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.awt.*;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Load {

	public List<Shape> loadData() throws IOException, ParseException {
		List<Shape> list = new ArrayList<>();
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(new FileReader("src/main/java/data.json"));
		JSONObject jsonObject = (JSONObject) obj;

		// Rectangle
		JSONArray array = (JSONArray) jsonObject.get("Rectangle");
		for (int i = 0; i < array.size(); i++) {
			JSONObject o = (JSONObject) array.get(i);
			int x = Math.toIntExact((long) o.get("X"));
			int y = Math.toIntExact((long) o.get("Y"));
			int h = Math.toIntExact((long) o.get("H"));
			int w = Math.toIntExact((long) o.get("W"));
			Color c = stringToColor((String)o.get("C"));
			list.add(new Rectangle(x, y, h, w, c));
		}

		// Line
		array = (JSONArray) jsonObject.get("Line");
		for (int i = 0; i < array.size(); i++) {
			JSONObject o = (JSONObject) array.get(i);
			int x1 = Math.toIntExact((long) o.get("X1"));
			int y1 = Math.toIntExact((long) o.get("Y1"));
			int x2 = Math.toIntExact((long) o.get("X2"));
			int y2 = Math.toIntExact((long) o.get("Y2"));
			Color c = stringToColor((String)o.get("C"));

			list.add(new Line(new Point(x1, y1), new Point(x2, y2), c));
		}

		//Circle
		array = (JSONArray) jsonObject.get("Circle");
		for (int i = 0; i < array.size(); i++) {
			JSONObject o = (JSONObject) array.get(i);
			int x = Math.toIntExact((long) o.get("X"));
			int y = Math.toIntExact((long) o.get("Y"));
			int r = Math.toIntExact((long) o.get("R"));
			Color c = stringToColor((String)o.get("C"));

			list.add(new Circle(x, y, r, c));
		}

		return list;
	}
	private Color stringToColor(String X) {
		if(X.equals("black")) {
			return Color.black;
		}else if(X.equals("blue")) {
			return Color.blue;
		}else if(X.equals("cyan")) {
			return Color.cyan;
		}else if(X.equals("darkGray")) {
			return Color.darkGray;
		}else if(X.equals("gray")) {
			return Color.gray;
		}else if(X.equals("green")) {
			return Color.green;
		}else if(X.equals("yellow")) {
			return Color.yellow;
		}else if(X.equals("lightGray")) {
			return Color.lightGray;
		}else if(X.equals("magenta")) {
			return Color.magenta;
		}else if(X.equals("orange")) {
			return Color.orange;
		}else if(X.equals("pink")) {
			return Color.pink;
		}else if(X.equals("red")) {
			return Color.red;
		}else if(X.equals("white")) {
			return Color.white;
		}
		return null;
	}

}
