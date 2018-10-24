package Model;

import org.json.simple.parser.ParseException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ShapeRepository {
	private List<Shape> list = new ArrayList<>();
	private Load load = new Load();

	public ShapeRepository() throws IOException, ParseException {
		list = load.loadData();
	}

	public void reloadData() throws IOException, ParseException {
		list = load.loadData();
	}
	public List<Shape> getList() {
		return list;
	}
}
