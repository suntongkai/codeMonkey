package com.project;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.util.ArrayList;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class MainPanel extends JPanel {
	
	private ArrayList<Point> pointList = new ArrayList<Point>();
	private boolean isFinish = false;
	private Color color;
	private boolean hasColor = false;
	
	public MainPanel(BorderLayout gl) {
		super(gl);
	}
	
	public void setPoint(int x, int y) {
		pointList.add(new Point(x, y));
		repaint();
	}
	
	public int getPointNum() {
		return pointList.size();
	}
	
	public void setFinish(Boolean isFinish) {
		this.isFinish = isFinish;
		repaint();
	}
	
	public void setColor(Color color, Boolean hasColor) {
		this.color = color;
		this.hasColor = hasColor;
		repaint();
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if (pointList.size() > 1) {
		    for (int i = 1; i < pointList.size(); i++) {
			   g.drawLine(pointList.get(i - 1).x, pointList.get(i - 1).y, pointList.get(i).x, pointList.get(i).y);
		    }
		    if (isFinish == true) {
				g.drawLine(pointList.get(0).x, pointList.get(0).y, pointList.get(pointList.size() - 1).x, pointList.get(pointList.size() - 1).y);
			}
		}
		if (hasColor == true) {
			Polygon polygon = new Polygon();
		    for (int i = 0; i < pointList.size(); i++) {
		    	polygon.addPoint(pointList.get(i).x, pointList.get(i).y);
		    }
		    g.setColor(color);
		    g.fillPolygon(polygon);
		}
	}
	
	public void clear() {
		pointList.clear();
		hasColor = false;
	}
}
