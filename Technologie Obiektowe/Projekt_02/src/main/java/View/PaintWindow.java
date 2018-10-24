package View;

import javax.swing.*;

import Model.ShapeRepository;
import org.json.simple.parser.ParseException;

import java.io.IOException;

public class PaintWindow extends JFrame {
	private ShapeRepository shapeRepository = new ShapeRepository();
	private DrawPanel panel = new DrawPanel(shapeRepository);

	public PaintWindow() throws IOException, ParseException {
		super("Simple Paint");
		setSize(500, 500);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		add(panel);
		setVisible(true);


	}

	public void refresh() throws IOException, ParseException {
		shapeRepository.reloadData();
		panel.updateData(shapeRepository);
		panel.repaint();
	}
	public DrawPanel getPanel() {
		return panel;
	}
}
