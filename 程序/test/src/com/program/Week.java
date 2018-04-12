package com.program;

import java.util.Scanner;

public class Week {

	private String week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	
	public Week() {
		
	}
	
	public void whichDay(Scanner sc) {
		int n = 1;
		String prefix = "";
		while (true) {
			System.out.println("请输入第" + n + "个字母(输入q退出):");
			n++;
			String in = sc.nextLine();
			prefix = prefix + in;
			boolean quit = false;
			switch (prefix) {
				case "M":
					System.out.println("您要输入的应该是:" + week[0]);
					prefix = "";
					n = 1;
					break;
				case "T":
					break;
				case "W":
					System.out.println("您要输入的应该是:" + week[2]);
					prefix = "";
					n = 1;
					break;
				case "F":
					System.out.println("您要输入的应该是:" + week[4]);
					prefix = "";
					n = 1;
					break;
				case "S":
					break;
				case "Tu":
					System.out.println("您要输入的应该是:" + week[1]);
					prefix = "";
					n = 1;
					break;
				case "Th":
					System.out.println("您要输入的应该是:" + week[3]);
					prefix = "";
					n = 1;
					break;
				case "Sa":
					System.out.println("您要输入的应该是:" + week[5]);
					prefix = "";
					n = 1;
					break;
				case "Su":
					System.out.println("您要输入的应该是:" + week[6]);
					prefix = "";
					n = 1;
					break;
				default:
					if (in.equals("q")) {
						quit = true;
					} else {
						System.out.println("不存在以" + prefix + "开头的那一天!");
						prefix = "";
						n = 1;
					}
			}
			if (quit == true) {
				break;
			}
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Week week = new Week();
		week.whichDay(sc);
		sc.close();
		System.out.println("over");
	}
}
