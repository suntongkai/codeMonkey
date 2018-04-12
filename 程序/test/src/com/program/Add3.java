package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Add3 {

	public Add3() {
		
	}
	
	public void run(int n) {
		double sum = 0;
		String out = "";
		if (n % 2 == 0) {
			for (int i = 1; i <= n / 2; i++) {
				sum = sum + (double)1 / (2 * i);
				out = out + 1 + "/" +  (2 * i) + " + ";
			}
		} else {
			for (int i = 1; i <= (n + 1) / 2; i++) {
				sum = sum + (double)1 / (2 * i - 1);
				out = out + 1 + "/" + (2 * i - 1) + " + ";
			}
		}
		out = out.substring(0, out.length() - 3) + " = " + sum;
		System.out.println(out);
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入一个数n(输入q退出):", sc);
			if (input1 != -1) {
				Add3 add3 = new Add3();
				add3.run(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
