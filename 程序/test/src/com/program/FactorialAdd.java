package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class FactorialAdd {
	
	public FactorialAdd() {
		
	}

	public void calculate(int n) {
		int sum = 0;
		Factorial f = new Factorial();
		String out = "";
		for (int i = 1; i <= n; i++) {
			sum = sum + f.calculate(i);
			out = out + i + "!" + " + ";
		}
		out = out.substring(0, out.length() - 3) + " = " + sum;
		System.out.println(out);
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入累加到几的阶乘(输入q退出):", sc);
			if (input1 != -1) {
				FactorialAdd fa = new FactorialAdd();
				fa.calculate(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
