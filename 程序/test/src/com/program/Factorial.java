package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Factorial {
	
	public Factorial() {
		
	}
	
	public int calculate(int n) {
		if (n == 1) {
			return 1;
		}
		return n * calculate(n - 1);
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入要计算阶乘的数(输入q退出):", sc);
			if (input1 != -1) {
				Factorial factorial = new Factorial();
				int result = factorial.calculate(input1);
				System.out.println(input1 + "! = " + result);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
