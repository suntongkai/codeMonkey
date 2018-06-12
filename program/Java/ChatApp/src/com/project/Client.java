package com.project;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JTextPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyledDocument;

import com.project.data.EmoticonData;

public class Client {
	
	private MainWindow mainWindow;
	private JTextPane receiveArea;
	private Socket clientSocket;
	private StyledDocument doc;
	private SimpleAttributeSet attrset=new SimpleAttributeSet();
	private JTextPane sendArea;
	private PrintWriter pw;
	private int receiveSize = 0;
	private FileWindow fileWindow;
	private String picList = "";
	private String sendPicList = "";
	private String receivePicList = "";
	
	public Client() {
		mainWindow = new MainWindow("Client");
		receiveArea = mainWindow.getReceiveArea();
        receiveArea.setText("close and start server first!\n");
        try {
        	InetAddress address = InetAddress.getLocalHost();
        	String ip = address.getHostAddress();
			clientSocket = new Socket(ip, 8081);
        	receiveArea.setText("connect success!\n");
			BufferedReader br = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			doc = receiveArea.getStyledDocument();
			sendArea = mainWindow.getSendArea();
			pw = new PrintWriter(clientSocket.getOutputStream(), true);
			menuAction();
	        buttonAction();
	        boolean finishReceive = true;
	        ArrayList<EmoticonData> emoticonList = null;
	        String message = "";
	        while (true) {
				String line = br.readLine();
				if (finishReceive == true) {
					receivePicList = line;
					emoticonList = getEmoticonList(br.readLine());
					finishReceive = false;
					if (receiveSize == -1) {
						String fileName = br.readLine();
						String filePath = getClass().getClassLoader().getResource("file/").getFile() + "/" + fileName;
						DataInputStream dis = new DataInputStream(clientSocket.getInputStream());
						FileOutputStream fos = new FileOutputStream(filePath);
					    int length = 0;
    					byte[] buf = new byte[1024];
    					while (dis.available() > 0) {
    						length = dis.read(buf, 0, buf.length);
    						fos.write(buf, 0, length);
    						fos.flush();
    					}
					    fos.close();
					    doc.insertString(doc.getLength(), "Receive " + setTime() + "\n", attrset);
						doc.insertString(doc.getLength(), "Receive file " + fileName + "\n", attrset);
						doc.insertString(doc.getLength(), "File path: " + filePath + "\n", attrset);
						finishReceive = true;
					}
				} else {
					message = message + line + "\n";
					receiveSize--;
					if (receiveSize == 0) {
						message = message.substring(0, message.length() - 1);// remove the last \n
						addReceive("Receive " + setTime() + "\n", message, emoticonList, receivePicList, 1);
						finishReceive = true;
						message = "";
						receivePicList = "";
					}
				}
			}
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (BadLocationException e) {
			e.printStackTrace();
		}
	}
	
	public void menuAction() {
		JMenuItem open = mainWindow.getOpen();
		open.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		JFileChooser fileChooser = new JFileChooser();
        		int result = fileChooser.showOpenDialog(mainWindow);
        		if (result == JFileChooser.APPROVE_OPTION) {
        			File file = fileChooser.getSelectedFile();
        			String fileName = fileChooser.getName(file);
        			if (fileName.endsWith(".jpg") || fileName.endsWith(".JPG") || fileName.endsWith(".jpeg") || fileName.endsWith(".JPEG") || 
                    		fileName.endsWith(".gif") || fileName.endsWith(".GIF") || fileName.endsWith(".png") || fileName.endsWith(".PNG") || 
                    		fileName.endsWith(".bmp") || fileName.endsWith(".BMP")) {
        				int pos = sendArea.getCaretPosition();
        				picList = picList + pos + "+" + file.toString() + ",";
        				sendPicList = sendPicList + pos + "+" + fileName + ",";
        				sendArea.insertIcon(new ImageIcon(file.toString()));
        			} else {
        				sendFile(fileName, file);
        			}
    			}
        		if (result == JFileChooser.CANCEL_OPTION) {
        			return;
        		}
        	}
		});
	}
	
	public void sendFile(String fileName, File file) {
		fileWindow = new FileWindow(mainWindow);
		long t = System.currentTimeMillis() / 1000;
		pw.println("\n-1\n" + fileName);
		try {
			FileInputStream fis = new FileInputStream(file);
			int length = 0;
			byte[] buf = new byte[1024];
			DataOutputStream dos = new DataOutputStream(clientSocket.getOutputStream());
			while ((length = fis.read(buf, 0, buf.length)) != -1) {
				dos.write(buf, 0, length);
				dos.flush();
			}
			fis.close();
			t = t - System.currentTimeMillis() / 1000;
			if (t < 1) {
				new Timer().schedule(new TimerTask(){
					public void run() {
						fileWindow.dispose();
						try {
							doc.insertString(doc.getLength(), "Send " + setTime() + "\n", attrset);
							doc.insertString(doc.getLength(), "Send file " + fileName + "\n", attrset);
						} catch (BadLocationException e) {
							e.printStackTrace();
						}
					}
				}, 500);
			} else {
				fileWindow.dispose();
				doc.insertString(doc.getLength(), "Send " + setTime() + "\n", attrset);
				doc.insertString(doc.getLength(), "Send file " + fileName + "\n", attrset);
			}
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		} catch (IOException e1) {
			e1.printStackTrace();
		} catch (BadLocationException e1) {
			e1.printStackTrace();
		}
	}
	
	public void buttonAction() {
		JButton emoticon = mainWindow.getEmoticon();
		EmoticonWindow emoticonWindow = new EmoticonWindow(mainWindow);
		emoticon.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (emoticonWindow.isOpen() == false) {
					emoticonWindow.setOpen(true);
					emoticonWindow.setVisible(true);
				} else {
					emoticonWindow.setOpen(false);
					emoticonWindow.dispose();
				}
			}
		});
		JButton send = mainWindow.getSend();
		send.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (emoticonWindow.emoticonListString().length() > 0 || sendArea.getText().length() > 0) {
					int lineNum =  count(sendArea.getText());
					String message = sendPicList + "\n" + emoticonWindow.emoticonListString() + lineNum + "\n" + sendArea.getText();
					pw.println(message);
					if (!picList.equals("")) {
						String[] picArray = picList.split(",");
						for (int i = 0; i < picArray.length; i++) {
							String[] picStrs = picArray[i].split("[+]");
							sendFile(picStrs[1]);
						}
					}
					String head = "Send " + setTime() + "\n";
					addReceive(head, sendArea.getText(), emoticonWindow.getEmoticonList(), picList, 0);
					sendArea.setText("");
					emoticonWindow.clearEmoticonList();
					picList = "";
					sendPicList = "";
				}
			}
		});
	}

	public int count(String str) {
		int num = 0;
		String[] strs = str.split("\n");
		num = strs.length;
		return num;
	}

	public ArrayList<EmoticonData> getEmoticonList(String str) {
		ArrayList<EmoticonData> emoticonList = new ArrayList<EmoticonData>();
		String[] emoticonArray = str.split(",");
		for (int i = 0; i < emoticonArray.length - 1; i++) {
			String[] emoticonStrs = emoticonArray[i].split("[+]");
			int pos = Integer.valueOf(emoticonStrs[0]);
			String num = emoticonStrs[1];
			emoticonList.add(new EmoticonData(pos, num));
		}
		receiveSize = Integer.valueOf(emoticonArray[emoticonArray.length - 1]);
		return emoticonList;
	}
	
	public void sendFile(String file) {
		try {
			FileInputStream fis = new FileInputStream(file);
			int length = 0;
			byte[] buf = new byte[1024];
			DataOutputStream dos = new DataOutputStream(clientSocket.getOutputStream());
			while ((length = fis.read(buf, 0, buf.length)) != -1) {
				dos.write(buf, 0, length);
				dos.flush();
			}
			fis.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
	
	public String setTime() {
		Calendar calendar = Calendar.getInstance();
		int hour = calendar.get(Calendar.HOUR_OF_DAY);
		int minute = calendar.get(Calendar.MINUTE);
		int second = calendar.get(Calendar.SECOND);
		String h = (hour > 9) ? "" + hour : "0" + hour;
		String m = (minute > 9) ? "" + minute : "0" + minute;
		String s = (second > 9) ? "" + second : "0" + second;
		return h + ":" + m + ":" + s;
	}
	
	/**
	 * 
	 * @param head
	 * @param text
	 * @param emoticonList
	 * @param picMessageList
	 * @param type 0 for add after sending and 1 for add after receiving
	 */
	public void addReceive(String head, String text, ArrayList<EmoticonData> emoticonList, String picList, int type) {
		try {
			int relpos = doc.getLength() + head.length();
			doc.insertString(doc.getLength(), head + text + "\n", attrset);
			for (int i = 0; i < emoticonList.size(); i++) {
				receiveArea.setCaretPosition(relpos + emoticonList.get(i).getPos());
				doc.remove(relpos + emoticonList.get(i).getPos(), 1);
				receiveArea.insertIcon(new ImageIcon(getClass().getClassLoader().getResource("img/" + emoticonList.get(i).getNum() + ".png")));
			}
			if (!picList.equals("")) {
				String[] picArray = picList.split(",");
				for (int i = 0; i < picArray.length; i++) {
					String[] picStrs = picArray[i].split("[+]");
					receiveArea.setCaretPosition(relpos + Integer.valueOf(picStrs[0]));
					doc.remove(relpos + Integer.valueOf(picStrs[0]), 1);
					if (type == 0) {
						receiveArea.insertIcon(new ImageIcon(picStrs[1]));
					}
					if (type == 1) {
						receiveArea.insertIcon(new ImageIcon(getClass().getClassLoader().getResource("file/" + picStrs[1])));
					}
				}
			}
		} catch (BadLocationException e1) {
			e1.printStackTrace();
		}
	}
	
	public void receivePic(String receivePicList) {
		if (!receivePicList.equals("")) {
			String[] picArray = receivePicList.split(",");
			for (int i = 0; i < picArray.length; i++) {
				String[] picStrs = picArray[i].split("[+]");
				String filePath = getClass().getClassLoader().getResource("file/").getFile() + "/" + picStrs[1];
				try {
					DataInputStream dis = new DataInputStream(clientSocket.getInputStream());
					FileOutputStream fos = new FileOutputStream(filePath);
				    int length = 0;
					byte[] buf = new byte[1024];
					while (dis.available() > 0) {
						length = dis.read(buf, 0, buf.length);
						fos.write(buf, 0, length);
						fos.flush();
					}
				    fos.close();
				} catch (UnknownHostException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public static void main(String[] args) {
		new Client();
	}
}
