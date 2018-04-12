package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Rabbit {
	
	public Rabbit() {
		
	}
	
	public void numOfRabbit(int month) {
		int num = 2;
		if (month == 1 || month == 2) {
			num = 1;
		} else if (month == 3) {
			num = 2;
		} else {
			int m = 4;
			int oneAdd = 1;// 前一个月的增加数
			int twoAdd = 0;// 前第二个月的增加数
			while (m <= month) {
				num = num + oneAdd + twoAdd;
				int add = oneAdd + twoAdd;
				twoAdd = oneAdd;
				oneAdd = add;
				m++;
			}
		}
		System.out.println("经过" + month + "个月兔子数是:" + num + "对");
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入经过了几个月(输入q退出):", sc);
			if (input1 != -1) {
				Rabbit rabbit = new Rabbit();
				rabbit.numOfRabbit(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
