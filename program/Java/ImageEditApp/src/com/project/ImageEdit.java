package com.project;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JToolBar;
import javax.swing.SwingConstants;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Size;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

/**
 * 
 * @author codeMonkey_sun
 * bug: 
 * 1 can not read file in Chinese name 
 * 2 image after zooming would be blurred
 */
public class ImageEdit {

	private JFrame frame;
	private JMenuItem open;
	private JMenuItem save;
	private JMenuItem saveAs;
	private JMenuItem exit;
	private JMenuItem magnify;
	private JMenuItem about;
	private JPanel panel;
	private JButton zoomIn;
	private JButton zoomOut;
	private JButton rotate;
	private JButton crop;
	private JButton delete;
	private File file;
	private Mat mat;
	private Mat endMat;
	private Mat copyMat;
	private BufferedImage image;
	private MainLabel label;
	private boolean isOpen = false;
	private MagnifyLabel ml;
	private boolean isMagnify = false;
	private int scale = 0;
	private int maxScale = 5;
	private int minScale = -4;
	private boolean zoomLock = false;
	private double angle = 0;
	private boolean rotateLock = false;
	private int x1 = 0;// crop rectangle
	private int y1 = 0;
	private int x2 = 0;
	private int y2 = 0;
	
	public ImageEdit() {
		init();
		menuAction();
	}
	
	public void init() {
		frame = new JFrame("Image Edit");
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
		magnify = new JMenuItem("magnify");
		editMenu.add(magnify);
		JMenu helpMenu = new JMenu("Help");
		about = new JMenuItem("About");
		helpMenu.add(about);
        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        menuBar.add(helpMenu);
        BorderLayout gl = new BorderLayout();
        panel = new JPanel(gl);
        frame.add(panel);
        JToolBar toolBar = new JToolBar("ToolBar");
        zoomIn = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/zoomIn.png")));
        zoomIn.setToolTipText("zoom in");
        toolBar.add(zoomIn);
        zoomOut = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/zoomOut.png")));
        zoomOut.setToolTipText("zoom out");
        toolBar.add(zoomOut);
        rotate = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/rotate.png")));
        rotate.setToolTipText("rotate");
        toolBar.add(rotate);
        crop = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/crop.png")));
        crop.setToolTipText("crop");
        toolBar.add(crop);
        delete = new JButton(new ImageIcon(getClass().getClassLoader().getResource("img/delete.png")));
        delete.setToolTipText("delete");
        toolBar.add(delete);
        panel.add(toolBar, BorderLayout.PAGE_START);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void menuAction() {
		open.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			panel.remove(label);
        			if (isMagnify == true) {
        				panel.remove(ml);
        			}
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
					copyMat= mat.clone();
                    image = (BufferedImage)HighGui.toBufferedImage(mat);
                    label = new MainLabel();
                    label.setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
                    panel.add(label, BorderLayout.WEST);
                    label.setIcon(new ImageIcon(image));
                    //label.setHorizontalAlignment(SwingConstants.LEFT);// X
                    label.setVerticalAlignment(SwingConstants.TOP);// Y
                    isOpen = true;
                    toolBarAction();
                    label.addMouseWheelListener(new MouseWheelListener() {
        				public void mouseWheelMoved(MouseWheelEvent e) {
        					if (isMagnify == true) {
                			    panel.remove(ml);
                			    panel.repaint();
                			}
        					if(e.getWheelRotation() == -1){// forward
        						if (scale > minScale) {
        	        		        scale = scale - 1;
        	        		        zoom();// zoomOut
        	        			} else {
        	        				JOptionPane.showMessageDialog(null, "Can not zoom out!");
        	        			}
        					}
        					if(e.getWheelRotation() == 1) {// backward
        						if (scale < maxScale) {
        	        		        scale = scale + 1;
        	        		        zoom();// zoom in
        	        			} else {
        	        				JOptionPane.showMessageDialog(null, "Can not zoom in!");
        	        			}
        					}
        				}
        			});
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
        magnify.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isOpen == true) {
        			ml = new MagnifyLabel(image);
        			ml.setBorder(BorderFactory.createTitledBorder("magnify image"));
        			panel.add(ml, BorderLayout.CENTER);
        			panel.validate();
        			mouseAction();
        			isMagnify = true;
        		} else {
        			JOptionPane.showMessageDialog(null, "Open a image file please!", "Error", JOptionPane.ERROR_MESSAGE);
        		}
        	}
        });
        about.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		String message = "author: codeMonkey_sun\n"
        				+ "bug:\n"
        				+ " * 1 Can not read file in Chinese name\n"
        				+ " * 2 Image after zooming would be blurred\n"
        				+ " * 3 There is a blcak background after ratatingn\n"
        				+ " * 4 For different size of image, magnify performed not pretty good";
        		JOptionPane.showMessageDialog(frame, message, "about", JOptionPane.INFORMATION_MESSAGE, 
        				new ImageIcon(getClass().getClassLoader().getResource("img/about.jpg")));
        	}
        });
	}
	
	public void mouseAction() {
		/*label.addMouseListener(new MouseListener() {
            public void mouseEntered(MouseEvent e) {
            	//System.out.println("进入");
			}
			public void mousePressed(MouseEvent e) {
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
		});*/
		label.addMouseMotionListener(new MouseMotionListener() {
			public void mouseMoved(MouseEvent e) {
				ml.setStart(true);
				ml.setLocation(e.getX(), e.getY());
				//System.out.println("移动");
			}
			public void mouseDragged(MouseEvent e) {
				//System.out.println("拖动");
			}
		});
	}
	
	public void toolBarAction() {
		zoomIn.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isMagnify == true) {
        		    panel.remove(ml);
        		    panel.repaint();
        		}
        		if (scale < maxScale) {
    		        scale = scale + 1;
    		        zoom();
    			} else {
    				JOptionPane.showMessageDialog(null, "Can not zoom in!");
    			}
        	}
		});
		zoomOut.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isMagnify == true) {
        		    panel.remove(ml);
        		    panel.repaint();
        		}
    			if (scale > minScale) {
    		        scale = scale - 1;
    		        zoom();
    			} else {
    				JOptionPane.showMessageDialog(null, "Can not zoom out!");
    			}
        	}
		});
		rotate.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isMagnify == true) {
        		    panel.remove(ml);
        		    panel.repaint();
        		}
        		Point center = new Point(endMat.width() / 2.0, endMat.height() / 2.0);
        		angle = angle + 45;
        		if (angle > 360) {
        			angle = angle - 360;
        		}
        		if (rotateLock == false) {
        			mat = endMat.clone();
        			rotateLock = true;
        		}
        		Mat trans = Imgproc.getRotationMatrix2D(center, angle, 1.0);// anticlockwise
        		Imgproc.warpAffine(mat, endMat, trans, endMat.size(), Imgproc.INTER_NEAREST);
        		image = (BufferedImage)HighGui.toBufferedImage(endMat);
        		label.setIcon(new ImageIcon(image));
        		zoomLock = false;
        	}
        });
        crop.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		if (isMagnify == true) {
        		    panel.remove(ml);
        		    panel.repaint();
        		}
        		label.addMouseListener(new MouseListener() {
                    public void mouseEntered(MouseEvent e) {
                    	//System.out.println("进入");
        			}
        			public void mousePressed(MouseEvent e) {
        				x1 = e.getX();
        				y1 = e.getY();
        				//System.out.println("按下");
        			}
        			public void mouseClicked(MouseEvent e) {
        				//System.out.println("点击");
        			}
        			public void mouseReleased(MouseEvent e) {
        				x2 = e.getX();
        				y2 = e.getY();// deal with click
        				if (x1 >= x2 || y1 >= y2) {
        					return;
        				}
        				Rect rect = new Rect(x1, y1, x2 - x1, y2 - y1);
        				Mat tmpMat = new Mat(endMat, rect);
        				image = (BufferedImage)HighGui.toBufferedImage(tmpMat);
        				label.setIcon(new ImageIcon(image));
        				endMat = tmpMat.clone();
        				copyMat = tmpMat.clone();
        				//System.out.println("松开");
        			}
                    public void mouseExited(MouseEvent e) {
                        //System.out.println("移出");
        			}
        		});
        		label.addMouseMotionListener(new MouseMotionListener() {
        			public void mouseMoved(MouseEvent e) {
        				//System.out.println("移动");
        			}
        			public void mouseDragged(MouseEvent e) {
        				x2 = e.getX();
        				y2 = e.getY();
        				label.setStart(true);
        				label.setLocation(x1, y1, x2, y2);
        				//System.out.println("拖动");
        			}
        		});
        	}
        });
        delete.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		file.delete();
        		panel.remove(label);
        		if (isMagnify == true) {
        		    panel.remove(ml);
        		}
        		panel.repaint();
        		JOptionPane.showMessageDialog(null, "Delete");
        	}
        });
	}
	
	public void zoom() {
		if (zoomLock == false) {
			mat = endMat.clone();
			zoomLock = true;
		}
		Imgproc.resize(mat, endMat, new Size(copyMat.width() * (1 + 0.2 * scale), copyMat.height() * (1 + 0.2 * scale)));
		image = (BufferedImage)HighGui.toBufferedImage(endMat);
		label.setIcon(new ImageIcon(image));
		rotateLock = false;
		angle = 0;
	}
	
	public static void main(String[] args) {
		new ImageEdit();
	}
}
