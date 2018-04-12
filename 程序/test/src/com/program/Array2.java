package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class Array2 {
	
	public Array2() {
		
	}
	
	public void run(int[] data, int move) {
		System.out.println("数组原来的顺序是:");
		display(data);
		int[] tmp = new int[move];
		for (int i = 0; i < move; i++) {
			tmp[i] = data[data.length - move + i];
		}
		for (int i = 0; i < data.length - move; i++) {
			data[data.length - 1 - i] = data[data.length - 1 - move - i];
		}
		for (int i = 0; i < move; i++) {
			data[i] = tmp[i];
		}
		System.out.println("数组移动后的顺序是:");
		display(data);
	}
	
	public void display(int[] data) {
		for (int i = 0; i < data.length - 1; i++) {
			System.out.print(data[i] + ", ");
		}
		System.out.println(data[data.length - 1]);
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
					input1 = tool.inputNum("请输入向后移动几个位置(输入q退出):", sc);
					if (input1 != -1) {
						Array2 array2 = new Array2();
						array2.run(data, input1);
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
