package com.project;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class MagnifyLabel extends JLabel {
	
	private Image image;
	private int locationX;
	private int locationY;
	private boolean start = false;

	public MagnifyLabel(Image image) {
		this.image = image;
	}
	
	public void setLocation(int locationX, int locationY) {
		this.locationX = locationX;
		this.locationY = locationY;
		repaint();
	}
	
	public void setStart(Boolean start) {
		this.start = start;
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if (start == true) {
	        g.drawImage(image, 0, 0, 300, 300, locationX, locationY, locationX + 100, locationY + 100, this);
		}
	}
}
