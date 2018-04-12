package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Encrypt {
	
	public Encrypt() {
		
	}
	
	public void run(String data) {
		if (data.length() == 4) {
			int[] num = new int[4];
			for (int i = 0; i < data.length(); i++) {
				num[i] = (Integer.valueOf(String.valueOf(data.charAt(i))) + 5) % 10;
			}
			System.out.println("加密后的数据是:" +  num[3] + num[2] + num[1] + num[0]);
		} else {
			System.out.println("题目要求是四位的整数!");
		}
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入数据(输入q退出):", sc);
			if (input1 != -1) {
				Encrypt encrypt = new Encrypt();
				encrypt.run(String.valueOf(input1));
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
