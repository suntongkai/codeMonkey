package com.program;

import java.util.Arrays;
import java.util.Scanner;

public class Sort2 {
	
	public Sort2() {
		
	}
	
	public void run(String str) {
		System.out.println("原顺序是:");
		System.out.println(str);
		char[] a = str.toCharArray();
		Arrays.sort(a);
		System.out.println("排序后的顺序是:");
		System.out.println(new String(a));
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (true) {
			System.out.println("请输入一行字符(输入q退出):");
			String in = sc.nextLine();
			if (in.equals("q")) {
				break;
			}
			Sort2 sort2 = new Sort2();
			sort2.run(in);
		}
		sc.close();
		System.out.println("over");
	}
}
