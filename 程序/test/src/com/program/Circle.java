package com.program;

import java.util.ArrayList;
import java.util.Scanner;

import com.tool.Tool;

public class Circle {
	
	public Circle() {
		
	}
	
	public void run(int n) {
		ArrayList<Integer> circle = new ArrayList<Integer>();
		for (int i = 1; i <= n; i++) {
			circle.add(i);
		}
		int j = 0;// 报数
		int k = 0;
		while (true) {
			j++;
			if (j == 3) {
				j = 0;
				circle.remove(k);
				k--;
			}
			if (circle.size() == 1) {
				break;
			}
			if (k == circle.size() - 1) {
				k = 0;
			} else {
				k++;
			}
		}
		System.out.println("最后留下的是:" + circle.get(0));
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入一圈的人数(输入q退出):", sc);
			if (input1 != -1) {
				Circle circle = new Circle();
				circle.run(input1);
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
