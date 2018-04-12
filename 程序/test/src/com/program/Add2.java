package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Add2 {
	
	public Add2() {
		
	}
	
	public void calculate(int n) {
		double sum = 0;
		int up = 2;
		int down = 1;
		String out = "";
		for (int i = 0; i < n; i++) {
			sum = sum + (double)up / down;
			out = out + up + "/" + down + " + ";
			int tmp = up;
			up = up + down;
			down = tmp;
		}
		out = out.substring(0, out.length() - 3) + " = " + sum;
		System.out.println(out);
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入要计算前几项(输入q退出):", sc);
			if (input1 != -1) {
				Add2 add2 = new Add2();
				add2.calculate(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
