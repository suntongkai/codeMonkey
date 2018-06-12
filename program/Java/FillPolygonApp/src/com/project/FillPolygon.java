package com.project;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JToolBar;

public class FillPolygon {
	
	private JFrame frame;
	private JMenuItem save;
	private JMenuItem saveAs;
	private JMenuItem exit;
	private JMenuItem clear;
	private JMenuItem about;
	private MainPanel panel;
	private JButton pen;
	private JButton finish;
	private JButton colorPanel;
	private JButton fill;
	private boolean startDraw = false;
	private boolean isFinish = false;
	private Color color;

	public FillPolygon() {
		init();
		menuAction();
		toolBarAction();
	}
	
	public void init() {
		frame = new JFrame("Fill Polygon");
		frame.setSize(700, 800);
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		JMenu fileMenu = new JMenu("File");
		save = new JMenuItem("Save");
		saveAs = new JMenuItem("Save as");
		exit = new JMenuItem("Exit");
		fileMenu.add(save);
		fileMenu.add(saveAs);
		fileMenu.add(exit);
		JMenu editMenu = new JMenu("Edit");
		clear = new JMenuItem("clear");
		editMenu.add(clear);
		JMenu helpMenu = new JMenu("Help");
		about = new JMenuItem("About");
		helpMenu.add(about);
        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        menuBar.add(helpMenu);
        BorderLayout gl = new BorderLayout();
        panel = new MainPanel(gl);
        frame.add(panel);
        JToolBar toolBar = new JToolBar("ToolBar");
        pen = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/pen.png")));
        pen.setToolTipText("click to draw lines");
        toolBar.add(pen);
        finish = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/finish.png")));
        finish.setToolTipText("finish drawing");
        toolBar.add(finish);
        colorPanel = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/colorPanel.jpg")));
        colorPanel.setToolTipText("select color");
        toolBar.add(colorPanel);
        fill = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/fill.jpg")));
        fill.setToolTipText("fill polygon");
        toolBar.add(fill);
        panel.add(toolBar, BorderLayout.PAGE_START);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void menuAction() {
		exit.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		System.exit(0);
        	}
        });
		clear.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		panel.clear();
        		color = null;
        		isFinish = false;
        		panel.setFinish(isFinish);
        		panel.repaint();
        		startDraw = false;
        	}
        });
		about.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		String message = "author: codeMonkey_sun\n"
        				+ "bug:\n"
        				+ " * 1 \n"
        				+ " * 2 \n"
        				+ " * 3 \n"
        				+ " * 4 ";
        		JOptionPane.showMessageDialog(frame, message, "about", JOptionPane.INFORMATION_MESSAGE, 
        				new ImageIcon(getClass().getClassLoader().getResource("img/about.jpg")));
        	}
        });
	}
	
	public void toolBarAction() {
		pen.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		startDraw = true;
        		mouseAction();
        	}
		});
		finish.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (panel.getPointNum() > 2) {
        			isFinish = true;
        		    panel.setFinish(isFinish);
        		} else {
        			JOptionPane.showMessageDialog(null, "Draw more points please!");
        		}
        	}
		});
		colorPanel.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		color = JColorChooser.showDialog(frame, "select color", null);
        		if (color == null) {
        			return;
        		}
        	}
		});
		fill.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (color != null) {
        			panel.setColor(color, true);
        		} else {
        			JOptionPane.showMessageDialog(null, "Select color please!");
        		}
        	}
		});
	}
	
	public void mouseAction() {
		panel.addMouseListener(new MouseListener() {
            public void mouseEntered(MouseEvent e) {
            	//System.out.println("进入");
			}
			public void mousePressed(MouseEvent e) {
				if (startDraw == true && isFinish == false) {
				    panel.setPoint(e.getX(), e.getY());
				}
				//System.out.println("按下");
			}
			public void mouseClicked(MouseEvent e) {
				//System.out.println("点击");
			}
			public void mouseReleased(MouseEvent e) {
				//System.out.println("松开");
			}
            public void mouseExited(MouseEvent e) {
                //System.out.println("移出");
			}
		});
		/*panel.addMouseMotionListener(new MouseMotionListener() {
			public void mouseMoved(MouseEvent e) {
				//System.out.println("移动");
			}
			public void mouseDragged(MouseEvent e) {
				//System.out.println("拖动");
			}
		});*/
	}
	
	public static void main(String[] args) {
		new FillPolygon();
	}
}
