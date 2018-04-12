package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class PalindromeNumber {
	
	public PalindromeNumber() {
		
	}
	
	public void judge(String num) {
		if (num.length() == 1) {
			System.out.println(num + "是回文数");
		} else {
			int head = 0;
			int tail = num.length() - 1;
			while (head < tail) {
				if (num.charAt(head) != num.charAt(tail)) {
					System.out.println(num + "不是回文数");
					break;
				}
				head++;
				tail--;
			}
			if (head >= tail) {
				System.out.println(num + "是回文数");
			}
		}
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入一个数字(输入q退出):", sc);
			if (input1 != -1) {
				PalindromeNumber pn = new PalindromeNumber();
				pn.judge(String.valueOf(input1));
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
