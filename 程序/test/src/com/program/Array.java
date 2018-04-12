package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Array {
	
	public Array() {
		
	}
	
	public void run(int[] data) {
		int maxIndex = 0;
		int minIndex = 0;
		int max = 0;
		int min = Integer.MAX_VALUE;
		String out = "";
		for (int i = 0; i < data.length; i++) {
			out = out + data[i] + ", ";
			if (data[i] > max) {
				max = data[i];
				maxIndex = i;
			}
			if (data[i] < min) {
				min = data[i];
				minIndex = i;
			}
		}
		out = out.substring(0, out.length() - 2);
		System.out.println("数组原来顺序是:");
		System.out.println(out);
		System.out.println("数组修改后的顺序是:");
		System.out.print(data[maxIndex] + ", ");
		for (int i = 1; i < data.length - 1; i++) {
			if (i == maxIndex) {
				System.out.print(data[0] + ", ");
			}
			else if (i == minIndex) {
				System.out.print(data[data.length - 1] + ", ");
			} else {
				System.out.print(data[i] + ", ");
			}
		}
		System.out.println(data[minIndex]);
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入数组的长度(输入q退出):", sc);
			if (input1 != -1) {
				int[] data = new int[input1];
				boolean quit = false;
				for (int i = 0; i < input1; i++) {
					data[i] = tool.inputNum("请输入第" + (i+1) + "个数(输入q退出):", sc);
					if (data[i] == -1) {
						quit = true;
						break;
					}
				}
				if (quit == false) {
					Array array = new Array();
					array.run(data);
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
