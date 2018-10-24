package Model;

import java.awt.*;

public class Circle implements Shape {
	private int radius;
	private int x;
	private int y;
	private Color color;

	public Circle(int x, int y, int radius, Color color) {
		this.radius = radius;
		this.x = x;
		this.y = y;
		this.color = color;
	}

	public int getRadius() {
		return radius;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public double getArea() {
		return Math.PI * radius * radius;
	}

	@Override
	public Color getColor() {
		return color;
	}
}
