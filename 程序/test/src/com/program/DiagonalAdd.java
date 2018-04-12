package com.program;

import java.util.Scanner;

import com.tool.Tool;

public class DiagonalAdd {
	
	public DiagonalAdd() {
		
	}
	
	public void add(int[][] data) {
		int sum = 0;
		int index = data.length - 1;
		for (int i = 0; i < data.length; i++) {
			for (int j = 0; j < data[0].length; j++) {
				if (i == j) {
					sum = sum + data[i][j];
				}
			}
			sum = sum + data[i][index];
			index--;
		}
		if (data.length % 2 != 0) {
			sum = sum - data[data.length / 2][data.length / 2];
		}
		System.out.println("对角线元素之和是:" + sum);
	}

	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		while (true) {
			int input1 = tool.inputNum("请输入方阵是几阶(输入q退出):", sc);
			if (input1 != -1) {
				int[][] data = new int[input1][input1];
				boolean quit = false;
				for (int i = 0; i < input1; i++) {
					int j = 0;
					for (j = 0; j < input1; j++) {
						data[i][j] = tool.inputNum("请输入第" + (i+1) +  "行第" + (j+1) + "列(输入q退出):", sc);
						if (data[i][j] == -1) {
							quit = true;
							break;
						}
					}
					if (quit == true) {
						break;
					}
				}
				if (quit == true) {
					break;
				} else {
					DiagonalAdd dd = new DiagonalAdd();
					dd.add(data);
				}
			} else {
				break;
			}
		}
		sc.close();
		System.out.println("over");
	}
}
