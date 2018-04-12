package com.program;

import java.util.Scanner;

public class CountChar {
	
	public CountChar() {
		
	}
	
	public void count(String str) {
		int letter = 0;
		int space = 0;
		int number = 0;
		int other = 0;
		for (int i = 0; i < str.length(); i++) {
			if ((str.charAt(i) >= 'a' && str.charAt(i) <='z') || (str.charAt(i) >= 'A' && str.charAt(i) <='Z')) {
				letter++;
			} else if (str.charAt(i) == ' ') {
				space++;
			} else if (str.charAt(i) >= '0' && str.charAt(i) <= '9') {
				number++;
			} else {
				other++;
			}
		}
		System.out.println("英文字母个数是:" + letter);
		System.out.println("空格个数是:" + space);
		System.out.println("数字个数是:" + number);
		System.out.println("其他字符个数是:" + other);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			System.out.println("请输入一行字符(输入q退出):");
			String in = sc.nextLine();
			if (in.equals("q")) {
				break;
			}
			CountChar cc = new CountChar();
			cc.count(in);
		}
		sc.close();
		System.out.println("over");
	}
}
