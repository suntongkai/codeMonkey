package com.program;

import java.util.ArrayList;
import java.util.Scanner;

import com.tool.Tool;

public class PerfectNumber {
	
	public PerfectNumber() {
		
	}

	public void findPerfectNumber(int size) {
		ArrayList<Integer> list = new ArrayList<Integer>();
		System.out.println(size + "以内所有完数是:");
		for (int i = 1; i <= size; i++) {
			for (int j = 1; j < i; j++) {
				if (i % j == 0) {
					list.add(j);
				}
			}
			int sum = 0;
			for (int k = 0; k < list.size(); k++) {
				sum = sum + list.get(k);
			}
			if (sum == i) {
				System.out.print(i + " = ");
				for (int k = 0; k < list.size() - 1; k++) {
					System.out.print(list.get(k) + " + ");
				}
				System.out.println(list.get(list.size() - 1));
			}
			list.clear();
		}
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入查找范围是多少以内(输入q退出):", sc);
			if (input1 != -1) {
				PerfectNumber pn = new PerfectNumber();
				pn.findPerfectNumber(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
