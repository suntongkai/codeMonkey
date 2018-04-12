package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class EuclideanAlgorithm {
	
	private int num1 = 0;
	private int num2 = 0;
	private int maxDiv = 0;
	
	public EuclideanAlgorithm(int num1, int num2) {
		this.num1 = num1;
		this.num2 = num2;
	}

	public void maxCommonDivisor(int num1, int num2) {
		if (num1 > num2) {
			if (num1 % num2 == 0) {
				maxDiv = num2;
				System.out.println(this.num1 + "和" + this.num2 + "的最大公约数是:" + maxDiv);
			} else {
				maxCommonDivisor(num2, num1 % num2);
			}
		} else {
			if (num2 % num1 == 0) {
				maxDiv = num1;
				System.out.println(this.num1 + "和" + this.num2 + "的最大公约数是:" + maxDiv);
			} else {
				maxCommonDivisor(num1, num2 % num1);
			}
		}
	}
	
	public void minCommonMultiple(int num1, int num2) {
		int minMul = num1 * num2 / maxDiv;
		System.out.println(this.num1 + "和" + this.num2 + "的最小公倍数是:" + minMul);
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入一个正整数(输入q退出):", sc);
			if (input1 != -1) {
				int input2 = tool.inputNum("请输入另一个正整数(输入q退出):", sc);
				if (input2 != -1) {
					EuclideanAlgorithm ea = new EuclideanAlgorithm(input1, input2);
					ea.maxCommonDivisor(input1, input2);
					ea.minCommonMultiple(input1, input2);
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
