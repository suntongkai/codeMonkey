package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Drop {
	
	public Drop() {
		
	}
	
	public void calculate(int height, int time) {
		double distance = height;
		for (int i = 1; i < time; i++) {
			distance = distance + rebound(height, i) * 2;
		}
		System.out.println("第" + time + "次落地时共经过:" + distance + "米");
		System.out.println("第" + time + "次反弹高度是:" + rebound(height, time) + "米");
	}

	public double rebound(int height, int time) {
		return height / (Math.pow(2, time));
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入起始高度(输入q退出):", sc);
			if (input1 != -1) {
				int input2 = tool.inputNum("请输入第几次落地(输入q退出):", sc);
				if (input2 != -1) {
					Drop  drop = new Drop();
					drop.calculate(input1, input2);
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
