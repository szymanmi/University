package View;

import javax.swing.*;

import Model.*;
import Model.Rectangle;
import Model.Shape;

import java.awt.*;
import java.util.List;
public class DrawPanel extends JPanel {
	private List<Shape> list;

	public DrawPanel(ShapeRepository shapeRepository) {
		this.list = shapeRepository.getList();
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		for(Shape shape : list){
			if(Rectangle.class == shape.getClass()){
				Rectangle temp = (Rectangle)shape;
				g.setColor(temp.getColor());
				g.fillRect(temp.getX(), temp.getY(), temp.getWidth(), temp.getHeight());
			}

			if(Line.class == shape.getClass()) {
				Line temp = (Line)shape;
				g.setColor(temp.getColor());
				g.drawLine(temp.getPoint1().getX(),temp.getPoint1().getY(), temp.getPoint2().getX(), temp.getPoint2().getY());
			}

			if(Circle.class == shape.getClass()){
				Circle temp = (Circle)shape;
				g.setColor(temp.getColor());
				g.fillOval(temp.getX(), temp.getY(), temp.getRadius(), temp.getRadius());
			}

		}
	}

	public void updateData(ShapeRepository shapeRepository){
		this.list = shapeRepository.getList();
	}
}
