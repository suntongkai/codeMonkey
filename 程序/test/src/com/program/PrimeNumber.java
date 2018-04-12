package com.program;

import java.util.ArrayList;
import java.util.Scanner;

import com.tool.Tool;

public class PrimeNumber {
	
	public PrimeNumber() {
		
	}
	
	public void findPrimeNumber(int start, int end) {
		if (start <= end) {
			int num = 0;
			ArrayList<Integer> list = new ArrayList<Integer>();
			for (int i = start; i <= end; i++) {
				if (isPrimeNumber(i) == true) {
					num++;
					list.add(i);
				}
			}
			System.out.println(start + "-" + end + "之间素数的个数是:" + num);
			for (int i = 0; i < list.size() - 1; i++) {
				System.out.print(list.get(i) + ", ");
			}
			System.out.println(list.get(list.size() - 1));
		} else {
			System.out.println("输入的数范围有误!");
		}
	}
	
	public boolean isPrimeNumber(int num) {
		if (num == 1) {
			return false;
		} else if (num == 2) {
			return true;
		} else {
			double divisor = Math.ceil(Math.sqrt(num));
			for (int i = 2; i <= divisor; i++) {
				if (num % i == 0) {
					return false;
				}
			}
		}
		return true;// 循环结束返回值
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入起始数字(输入q退出):", sc);
			if (input1 != -1) {
				int input2 = tool.inputNum("请输入结束数字(输入q退出):", sc);
				if (input2 != -1) {
					PrimeNumber pn = new PrimeNumber();
					pn.findPrimeNumber(input1, input2);
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
