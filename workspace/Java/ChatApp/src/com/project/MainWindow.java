package com.project;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;

@SuppressWarnings("serial")
public class MainWindow extends JFrame {

	private JMenuItem open;
	private JMenuItem exit;
	private JMenuItem about;
	private JTextPane receiveArea;
	private JTextPane sendArea;
	private JButton clear;
	private JButton emoticon;
	private JButton send;
	
	public MainWindow(String title) {
		super(title);
		this.setSize(400, 500);
		this.setLayout(null);
		JMenuBar menuBar = new JMenuBar();
		this.setJMenuBar(menuBar);
		JMenu fileMenu = new JMenu("File");
		open = new JMenuItem("Open");
		exit = new JMenuItem("Exit");
		fileMenu.add(open);
		fileMenu.add(exit);
		JMenu helpMenu = new JMenu("Help");
		about = new JMenuItem("About");
		helpMenu.add(about);
		receiveArea = new JTextPane();
		sendArea = new JTextPane();
		JScrollPane receivePanel = new JScrollPane(receiveArea);
		JScrollPane sendPanel = new JScrollPane(sendArea);
		receivePanel.setBounds(50, 30, 280, 200);
		clear = new JButton("Clear");
		clear.setBounds(250, 230, 80, 30);
		sendPanel.setBounds(50, 280, 280, 100);
		emoticon = new JButton("Emoticon");
		emoticon.setBounds(150, 380, 90, 30);
		send = new JButton("Send");
		send.setBounds(250, 380, 80, 30);
		this.add(receivePanel);
		this.add(clear);
		this.add(sendPanel);
		this.add(emoticon);
		this.add(send);
		menuBar.add(fileMenu);
		menuBar.add(helpMenu);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        menuAction();
        buttonAction();
	}
	
	public void menuAction() {
		exit.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		System.exit(0);
        	}
        });
		about.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		String message = "author: codeMonkey_sun\n"
        				+ "bug:\n"
        				+ " * 1 the chat window is too small\n"
        				+ " * 2 if we send files with the same name, ...\n"
        				+ " * 3 \n"
        				+ " * 4 ";
        		JOptionPane.showMessageDialog(getObj(), message, "about", JOptionPane.INFORMATION_MESSAGE, 
        				new ImageIcon(getClass().getClassLoader().getResource("img/about.jpg")));
        	}
        });
	}

	public void buttonAction() {
		clear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				receiveArea.setText("");
			}
		});
	}
	
	public JTextPane getReceiveArea() {
		return receiveArea;
	}

	public JTextPane getSendArea() {
		return sendArea;
	}

	public JButton getEmoticon() {
		return emoticon;
	}

	public JButton getSend() {
		return send;
	}
	
	public JMenuItem getOpen() {
		return open;
	}
	
	private JFrame getObj() {
		return this; 
	}
}
