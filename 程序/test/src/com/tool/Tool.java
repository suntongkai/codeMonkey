package com.tool;

import java.util.Scanner;

public class Tool {
	
	public Tool() {
		
	}

	/**
	 * @author sun
	 * @判断一个String对象是否是一个正整数
	 * @param str 
	 * @return
	 */
	public boolean isNum(String str) {
		if (str.charAt(0) == '0') {
			if (str.length() == 1) {
				System.out.println("输入的数不能为0!");
			} else {
				System.out.println("输入的数不能以0开头!");
			}
			return false;
		} else {
			for (int i = 0; i < str.length(); i++) {
				if (!(str.charAt(i) >= '0' &&  str.charAt(i) <= '9')) {
					System.out.println("输入的不是正整数!");
					return false;
				}
			}
		}
		return true;
	}
	
	public int inputNum(String str, Scanner sc) {
		int num = -1;
		while (true) {
			System.out.println(str);
			String in = sc.nextLine();
			if (in.equals("q")) {
				break;
			}
			if (isNum(in) == true) {
				num = Integer.valueOf(in);
				break;
			}
		}
		return num;
	}
}
