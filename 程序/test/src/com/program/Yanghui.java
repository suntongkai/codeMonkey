package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Yanghui {
	
	public Yanghui() {
		
	}
	
	public void display(int n) {
		
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入要要输出的行数(输入q退出):", sc);
			if (input1 != -1) {
				Yanghui yanghui = new Yanghui();
				yanghui.display(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
