package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Add {
	
	public Add() {
		
	}
	
	public void calculate(int a, int num) {
		long sum = 0;
		String out = "";
		for (int i = 1; i <= num; i++) {
			long adder = 0;
			for (int j = 0; j < i; j++) {
				adder = adder + a * (long)Math.pow(10, j);
			}
			sum = sum + adder;
			out = out + adder + " + ";
		}
		out = out.substring(0, out.length() - 3) + " = " + sum;
		System.out.println(out);
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入a(输入q退出):", sc);
			if (input1 != -1) {
				int input2 = tool.inputNum("请输入相加的数的个数(输入q退出):", sc);
				if (input2 != -1) {
					Add add = new Add();
					add.calculate(input1, input2);
				} else {
					break;
				}
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
