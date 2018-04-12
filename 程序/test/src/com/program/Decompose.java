package com.program;

import java.util.ArrayList;
import java.util.Scanner;

import com.tool.Tool;

public class Decompose {
	
	public Decompose() {
		
	}
	
	public void run(int num) {
		int factor = minFactor(num);
		ArrayList<Integer> list = new ArrayList<Integer>();
		int n = num;
		while (factor != n) {
			list.add(factor);
			n = n / factor;
			factor = minFactor(n);
		}
		list.add(factor);
		System.out.print(num + " = ");
		for (int i = 0; i < list.size() - 1; i++) {
			System.out.print(list.get(i) + " * ");
		}
		System.out.println(list.get(list.size() - 1));
	}

	public int minFactor(int num) {
		for (int i = 2; i < num; i++) {
			if (num % i == 0) {
				return i;
			}
		}
		return num;
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入要分解的正整数(输入q退出):", sc);
			if (input1 != -1) {
				Decompose decompose = new Decompose();
				decompose.run(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
