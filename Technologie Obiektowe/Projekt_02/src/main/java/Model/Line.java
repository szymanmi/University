package Model;

import java.awt.*;

public class Line implements Shape{
	private Point point1;
	private Point point2;
	private Color color;



	public Line(Point point1, Point point2, Color color) {
		this.point1 = point1;
		this.point2 = point2;
		this.color = color;
	}

	public Point getPoint1() {
		return point1;
	}

	public Point getPoint2() {
		return point2;
	}

	@Override
	public Color getColor() {
		return color;
	}
}
