package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class ConditionalOperator {
	
	public ConditionalOperator() {
		
	}
	
	public void assess(int grade) {
		String level = null;
		level = (grade >= 90) ? "A" : ((grade >= 60 && grade <= 89) ? "B" : "C");
		System.out.println(grade + "对应的等级是:" + level);
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入成绩(输入q退出):", sc);
			if (input1 != -1) {
				ConditionalOperator co = new ConditionalOperator();
				co.assess(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
