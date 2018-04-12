package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Evennum {
	
	public Evennum() {
		
	}
	
	public void run(int n) {
		if (n % 2 == 0) {
			PrimeNumber pn = new PrimeNumber();
			for (int i = 2; i < n / 2; i++) {
				if (pn.isPrimeNumber(i)) {
					if (pn.isPrimeNumber(n - i)) {
						System.out.println(n + " = " + i + " + " + (n - i));
					}
				}
			}
		} else {
			System.out.println("让你输偶数，没看到?");
		}
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入一个偶数(输入q退出):", sc);
			if (input1 != -1) {
				Evennum evennum = new Evennum();
				evennum.run(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
