package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class DrawDiamond {
	public DrawDiamond() {
		
	}

	public void draw(int n) {
		if (n % 2 != 0) {
			for (int i = 1; i <= (n + 1) / 2; i++) {
				for (int j = i; j <= n / 2; j++) {
					System.out.print(" ");
				}
				for (int j = 0; j < i * 2 - 1; j++) {
					System.out.print("*");
				}
				System.out.println();
			}
			for (int i = n / 2; i > 0; i--) {
				for (int j = i; j <= n / 2; j++) {
					System.out.print(" ");
				}
				for (int j = 0; j < i * 2 - 1; j++) {
					System.out.print("*");
				}
				System.out.println();
			}
		} else {
			System.out.println("不能是偶数!");
		}
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入总行数(输入q退出):", sc);
			if (input1 != -1) {
				DrawDiamond dd = new DrawDiamond();
				dd.draw(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
