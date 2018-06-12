package com.project;

import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JWindow;
import javax.swing.Timer;

@SuppressWarnings("serial")
public class FileWindow extends JWindow {
	
	private JProgressBar progressBar;
	private int process = 0;
	
	public FileWindow(JFrame window) {
		super(window);
		int x = window.getX() + window.getWidth();
		int y = window.getY();
		this.setBounds(x, y, 300, 150);
		JPanel panel = new JPanel(new GridBagLayout());
		this.setContentPane(panel);
		JLabel fileIcon = new JLabel();
		fileIcon.setIcon(new ImageIcon(getClass().getClassLoader().getResource("img/fileIcon.jpg")));
		progressBar = new JProgressBar();
		progressBar.setMinimum(0);
        progressBar.setMaximum(100);
		JLabel receiveIcon = new JLabel();
		receiveIcon.setIcon(new ImageIcon(getClass().getClassLoader().getResource("img/receiveIcon.jpg")));
		panel.add(fileIcon);
		panel.add(progressBar);
		panel.add(receiveIcon);
		this.setVisible(true);
		startProcessBar();
	}
	
	public void startProcessBar() {
		new Timer(100, new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				process = process + 25;
				if (process > 100) {
					process = 0;
				}
				progressBar.setValue(process);
			}
		}).start();
	}
}
