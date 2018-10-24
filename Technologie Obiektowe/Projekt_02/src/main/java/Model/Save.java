package Model;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Save {

	public void saveRectangle(int x, int y, int h, int w, String c) throws IOException, ParseException {
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(new FileReader("src/main/java/data.json"));
		JSONObject jsonObject = (JSONObject) obj;


		JSONArray array = (JSONArray) jsonObject.get("Rectangle");

		JSONObject temp = new JSONObject();

		temp.put("X", x);
		temp.put("Y", y);
		temp.put("H", h);
		temp.put("W", w);
		temp.put("C", c);

		array.add(temp);


		jsonObject.put("Rectangle", array);


		try (FileWriter file = new FileWriter("src/main/java/data.json")) {

			file.write(jsonObject.toJSONString());
			file.flush();

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void saveCircle(int x, int y, int r, String c) throws IOException, ParseException {
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(new FileReader("src/main/java/data.json"));
		JSONObject jsonObject = (JSONObject) obj;


		JSONArray array = (JSONArray) jsonObject.get("Circle");

		JSONObject temp = new JSONObject();

		temp.put("X", x);
		temp.put("Y", y);
		temp.put("R", r);
		temp.put("C", c);

		array.add(temp);


		jsonObject.put("Circle", array);


		try (FileWriter file = new FileWriter("src/main/java/data.json")) {

			file.write(jsonObject.toJSONString());
			file.flush();

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void saveLine(int x1, int y1, int x2, int y2, String c) throws IOException, ParseException {
		JSONParser parser = new JSONParser();
		Object obj = parser.parse(new FileReader("src/main/java/data.json"));
		JSONObject jsonObject = (JSONObject) obj;


		JSONArray array = (JSONArray) jsonObject.get("Line");

		JSONObject temp = new JSONObject();

		temp.put("X1", x1);
		temp.put("Y1", y1);
		temp.put("X2", x2);
		temp.put("Y2", y2);
		temp.put("C", c);

		array.add(temp);


		jsonObject.put("Line", array);


		try (FileWriter file = new FileWriter("src/main/java/data.json")) {

			file.write(jsonObject.toJSONString());
			file.flush();

		} catch (IOException e) {
			e.printStackTrace();
		}

	}


}
