package Model;

import java.awt.*;

public class Rectangle implements Shape{
	private int x;
	private int y;
	private int height;
	private int width;
	private Color color;

	public Rectangle(int x, int y, int height, int width, Color color) {
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.color = color;
	}


	public double getArea(){
		return 5;
	}

	public double getPerimeter(){
		return 5;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public int getHeight() {
		return height;
	}

	public int getWidth() {
		return width;
	}

	@Override
	public Color getColor() {
		return color;
	}
}
