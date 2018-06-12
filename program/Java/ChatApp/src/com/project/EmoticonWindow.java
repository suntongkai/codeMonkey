package com.project;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JWindow;

import com.project.data.EmoticonData;

@SuppressWarnings("serial")
public class EmoticonWindow extends JWindow {
	
	private boolean isOpen = false;
	private ArrayList<EmoticonData> emoticonList = new ArrayList<EmoticonData>();

	public EmoticonWindow(MainWindow window) {
		super(window);
		this.setSize(525, 225);
		this.setLocationRelativeTo(window);
		JPanel panel = new JPanel();
		this.setContentPane(panel);
		panel.setOpaque(true);// 设置控件不透明
		GridLayout gridLayout = new GridLayout(3,7);
		panel.setLayout(gridLayout);
		JLabel[] icon = new JLabel[21];
		for (int i = 0; i < icon.length; i++) {
			icon[i] = new JLabel();
			icon[i].setIcon(new ImageIcon(getClass().getClassLoader().getResource("img/" + String.valueOf(i + 1) + ".png").getFile()));
			icon[i].setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
			icon[i].setToolTipText(String.valueOf(i + 1));
			icon[i].addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					getObj().dispose();
					isOpen = false;
					((JLabel)e.getSource()).setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
					int pos = window.getSendArea().getCaretPosition();
					Icon selectIcon = ((JLabel)e.getSource()).getIcon();
					window.getSendArea().insertIcon(selectIcon);
					EmoticonData emoticonData = new EmoticonData(pos, ((JLabel)e.getSource()).getToolTipText());
					emoticonList.add(emoticonData);
					//System.out.println("点击");
				}
				public void mouseEntered(MouseEvent e) {
					((JLabel)e.getSource()).setBorder(BorderFactory.createLineBorder(Color.BLUE, 2));
					//System.out.println("进入");
				}
				public void mouseExited(MouseEvent e) {
					((JLabel)e.getSource()).setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
					//System.out.println("离开");
				}
			});
			panel.add(icon[i]);
		}
		this.setAlwaysOnTop(true);
	}
	
	private JWindow getObj() {
		return this;
	}
	
	public boolean isOpen() {
		return isOpen;
	}

	public void setOpen(boolean isOpen) {
		this.isOpen = isOpen;
	}
	
	public ArrayList<EmoticonData> getEmoticonList() {
		return emoticonList;
	}

	public String emoticonListString() {
		String str = "";
		for (int i = 0; i < emoticonList.size(); i++) {
			int pos = emoticonList.get(i).getPos();
			String num = emoticonList.get(i).getNum();
			str = str + pos + "+" + num + ",";
		}
		return str;
	}
	
	public void clearEmoticonList() {
		emoticonList.clear();
	}
}
