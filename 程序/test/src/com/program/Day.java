package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Day {
	
	public final int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	public Day() {
		
	}

	public void dayOfYear(int year, int month, int day) {
		if (year > 10000) {
			System.out.println(year + "年还早着呢, 拒绝计算!");
		} else if (month > 12) {
			System.out.println("你家一年有" + month + "个月?");
		} else if (day > this.month[month - 1]) {
			System.out.println("你家" + month + "月有" + day + "天?");
		} else {
			int total = day;
			for (int i = 0; i < month - 1; i++) {
				total = total + this.month[i];
				if (year % 4 == 0 && year % 100  != 0 || year % 400 == 0) {
					if (i == 1) {
						total = total + 1;
					}
				}
			}
			System.out.println(month + "月" + day + "日" + "是" + year + "年的第"+ total + "天");
		}
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入年(输入q退出):", sc);
			if (input1 != -1) {
				int input2 = tool.inputNum("请输入月(输入q退出):", sc);
				if (input2 != -1) {
					int input3 = tool.inputNum("请输入日(输入q退出):", sc);
					if (input3 != -1) {
						Day day = new Day();
						day.dayOfYear(input1, input2, input3);
					} else {
						break;
					}
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
