package com.program;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Size;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class ImageProcess {
	
	private JFrame frame;
	private JMenuItem open;
	private JMenuItem save;
	private JMenuItem saveAs;
	private JMenuItem exit;
	private JMenuItem reverse;
	private JMenuItem clear;
	private JMenuItem average;
	private JMenuItem middle;
	private JMenuItem box;
	private JMenuItem sharpen;
	private JMenuItem DCT;
	private JMenuItem Canny;
	private JMenuItem Sobel;
	private JMenuItem about;
	private JPanel panel;
	private File file;
	private Mat mat;
	private Mat endMat;
	private JLabel label;
	private boolean isOpen = false;
	private JLabel label2;
	private boolean isEdit = false;
	private ArrayList<JLabel> labelList = new ArrayList<JLabel>();
	static final int MaxProcess = 3;
	private int processNum = 0;

	public ImageProcess() {
		init();
		menuAction();
	}
	
	public void init() {
		frame = new JFrame("Image Process");
		frame.setSize(700, 800);
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		JMenu fileMenu = new JMenu("File");
		open = new JMenuItem("Open");
		save = new JMenuItem("Save");
		saveAs = new JMenuItem("Save as");
		exit = new JMenuItem("Exit");
		fileMenu.add(open);
		fileMenu.add(save);
		fileMenu.add(saveAs);
		fileMenu.add(exit);
		JMenu editMenu = new JMenu("Edit");
		reverse = new JMenuItem("reverse");
		JMenu smooth = new JMenu("smooth");
		average = new JMenuItem("average");
		middle = new JMenuItem("middle");
		box = new JMenuItem("box");
		smooth.add(average);
		smooth.add(middle);
		smooth.add(box);
		sharpen = new JMenuItem("sharpen");
		DCT = new JMenuItem("DCT");
		Canny = new JMenuItem("Canny");
		Sobel = new JMenuItem("Sobel");
		clear = new JMenuItem("clear");
		editMenu.add(reverse);
		editMenu.add(smooth);
		editMenu.add(sharpen);
		editMenu.add(DCT);
		editMenu.add(Canny);
		editMenu.add(Sobel);
		editMenu.add(clear);
		JMenu helpMenu = new JMenu("Help");
		about = new JMenuItem("About");
		helpMenu.add(about);
        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        menuBar.add(helpMenu);
        GridLayout gl = new GridLayout();
        panel = new JPanel(gl);
        frame.add(panel);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void menuAction() {
		open.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			panel.remove(label);
        			panel.repaint();
        		}
        		JFileChooser fileChooser = new JFileChooser();
        		int result = fileChooser.showOpenDialog(frame);
        		String fileName = null;
        		if (result == JFileChooser.APPROVE_OPTION) {
        			file = fileChooser.getSelectedFile();
        			fileName = fileChooser.getName(file);
        		}
        		if (result == JFileChooser.CANCEL_OPTION) {
        			return;
        		}
        		if (fileName.endsWith(".jpg") || fileName.endsWith(".JPG") || fileName.endsWith(".jpeg") || fileName.endsWith(".JPEG") || 
                		fileName.endsWith(".gif") || fileName.endsWith(".GIF") || fileName.endsWith(".png") || fileName.endsWith(".PNG") || 
                		fileName.endsWith(".bmp") || fileName.endsWith(".BMP")) {
        			System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        			mat = Imgcodecs.imread(file.toString());
        			endMat = mat.clone();
        			Image image = HighGui.toBufferedImage(mat);
        			label = new JLabel();
        			label.setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
                    panel.add(label);
                    label.setIcon(new ImageIcon(image));
                    isOpen = true;
        		} else {
                	JOptionPane.showMessageDialog(null, "Not a image file!", "Error", JOptionPane.ERROR_MESSAGE);
                }
        	}
		});
		save.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        		    Imgcodecs.imwrite(file.toString(), endMat);
        		    JOptionPane.showMessageDialog(null, "save");
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
		});
		saveAs.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			JFileChooser fileChooser = new JFileChooser();
        			int result = fileChooser.showSaveDialog(frame);
        			if (result == JFileChooser.APPROVE_OPTION) {
        				File f = fileChooser.getSelectedFile();
            		    Imgcodecs.imwrite(f.toString(), endMat);
        			}
        			if (result == JFileChooser.CANCEL_OPTION) {
        				return;
        			}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
		});
		exit.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		System.exit(0);
        	}
        });
		reverse.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        			Mat tmp = endMat.clone();
	        			Core.bitwise_not(tmp, endMat);
	        			showImage();
	        			isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		average.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.blur(tmp, endMat, new Size(9, 9), new Point(-1, -1), Core.BORDER_DEFAULT);
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		middle.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.medianBlur(tmp, endMat, 9);
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		box.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.boxFilter(tmp, endMat, tmp.depth(), new Size(9, 9));
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		sharpen.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.Laplacian(tmp, endMat, 0);
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		DCT.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    /*Mat tmp = endMat.clone();
	        		    
	        		    showImage();
		        		isEdit = true;*/
	        			JOptionPane.showMessageDialog(null, "developing");
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		Canny.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.Canny(tmp, endMat, 40, 200);
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		Sobel.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			processNum++;
	        		if (processNum <= MaxProcess) {
	        		    Mat tmp = endMat.clone();
	        		    Imgproc.Sobel(tmp, endMat, -1, 0, 1);
	        		    showImage();
		        		isEdit = true;
	        		} else {
	        			JOptionPane.showMessageDialog(null, "够了，别再点了!");
	        		}
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
		clear.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isEdit == true) {
        			for (int i = 0; i < labelList.size(); i++) {
        				panel.remove(labelList.get(i));
        			}
        		    panel.repaint();
        		    endMat = mat.clone();
        		    processNum = 0;
        		} else {
        			JOptionPane.showMessageDialog(null, "Edit the image please before clear!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
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
	
	public void showImage() {
		label2 = new JLabel();
	    labelList.add(label2);
		label2.setBorder(BorderFactory.createLineBorder(Color.BLUE, 3));
        panel.add(label2);
		Image image = HighGui.toBufferedImage(endMat);
		label2.setIcon(new ImageIcon(image));
	}
	
	public static void main(String[] args) {
		new ImageProcess();
	}
}
