package com.project;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class MainLabel extends JLabel {
	
	private int x1;
	private int y1;
	private int x2;
	private int y2;
	private boolean start = false;
	
	public void setStart(Boolean start) {
		this.start = start;
	}
	
	public void setLocation(int x1, int y1, int x2, int y2) {
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		repaint();
	}
	
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);
		if (start == true) {
			g.setColor(Color.RED);
			g.drawRect(x1, y1, x2 - x1, y2 - y1);
			start = false;
		}
	}
}
