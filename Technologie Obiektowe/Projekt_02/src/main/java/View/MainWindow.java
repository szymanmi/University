package View;

import Controller.ShapeController;
import org.json.simple.parser.ParseException;

import javax.swing.*;
import java.io.IOException;

public class MainWindow extends JFrame {

	public MainWindow() throws IOException, ParseException {
		super("Simple Paint");
		setSize(500, 300);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		PaintWindow pw = new PaintWindow();
		pw.setVisible(true);

		ShapeController controller = new ShapeController(pw);

		JPanel mainPanel = new JPanel();

		//Rectangle
		JPanel newRectanglePanel = new JPanel();

		JButton drawRectButton = new JButton("Rysuj prostokat");
		JTextField rX = new JTextField(5);
		JTextField rY = new JTextField(5);
		JTextField rH = new JTextField(5);
		JTextField rW = new JTextField(5);
		JTextField rC = new JTextField(5);

		newRectanglePanel.add(rX);
		newRectanglePanel.add(rY);
		newRectanglePanel.add(rH);
		newRectanglePanel.add(rW);
		newRectanglePanel.add(rC);
		newRectanglePanel.add(drawRectButton);

		drawRectButton.addActionListener(e -> {
			try {
				controller.addNewRectangle(rX.getText(), rY.getText(), rH.getText(), rW.getText(), rC.getText());
			} catch (IOException | ParseException e1) {
				e1.printStackTrace();
			}
		});
		mainPanel.add(newRectanglePanel);

		//Circle
		JPanel newCirclePanel = new JPanel();
		JButton drawCircleButton = new JButton("Rysuj Kolo");
		JTextField cX = new JTextField(5);
		JTextField cY = new JTextField(5);
		JTextField cR = new JTextField(5);
		JTextField cC = new JTextField(5);

		newCirclePanel.add(cX);
		newCirclePanel.add(cY);
		newCirclePanel.add(cR);
		newCirclePanel.add(cC);
		newCirclePanel.add(drawCircleButton);

		drawCircleButton.addActionListener(e -> {
			try {
				controller.addNewCircle(cX.getText(), cY.getText(), cR.getText(), cC.getText());
			} catch (IOException | ParseException e1) {
				e1.printStackTrace();
			}
		});
		mainPanel.add(newCirclePanel);

		//Line
		JPanel newLinePanel = new JPanel();
		JButton drawLineButton = new JButton("Rysuj Linie");
		JTextField lX1 = new JTextField(5);
		JTextField lY1 = new JTextField(5);
		JTextField lX2 = new JTextField(5);
		JTextField lY2 = new JTextField(5);
		JTextField lC = new JTextField(5);

		newLinePanel.add(lX1);
		newLinePanel.add(lY1);
		newLinePanel.add(lX2);
		newLinePanel.add(lY2);
		newLinePanel.add(lC);
		newLinePanel.add(drawLineButton);

		drawLineButton.addActionListener(e -> {
			try {
				controller.addNewLine(lX1.getText(), lY1.getText(), lX2.getText(), lY2.getText(), lC.getText());
			} catch (IOException | ParseException e1) {
				e1.printStackTrace();
			}
		});
		mainPanel.add(newLinePanel);





		add(mainPanel);
		setVisible(true);
	}

	public static void main(String[] args) throws IOException, ParseException {
		MainWindow mainWindow = new MainWindow();
	}
}
