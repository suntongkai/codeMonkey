package com.program;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

import com.tool.Tool;

public class Sort {
	
	public Sort() {
		
	}

	public boolean isSort(ArrayList<Integer> list) {
		int flag = 0;// 升序
		if (list.get(0) > list.get(1)) {
			flag = 1;// 降序
		}
		for (int i = 1; i < list.size(); i++) {
			if (flag == 0 && list.get(i - 1) > list.get(i)) {
				return false;
			}
			if (flag == 1 && list.get(i - 1) < list.get(i)) {
				return false;
			}
		}
		return true;
	}
	
	public void display(ArrayList<Integer> list) {
		for (int i = 0; i < list.size() - 1; i++) {
			System.out.print(list.get(i) + ", ");
		}
		System.out.println(list.get(list.size() - 1));
	}
	
	public void run(ArrayList<Integer> list) {
		System.out.print("原来顺序是:");
		display(list);
		Collections.sort(list);// 升序
		System.out.print("排序后顺序是:");
		display(list);
	}
	
	public void insert(int n, ArrayList<Integer> list) {
		int index = Collections.binarySearch(list, n);// 第一个大于n的索引
		if (index == 0) {
			list.add(0, n);
		} else if (index > 0) {
			list.add(index, n);
		} else {
			list.add(-index - 1, n);
		}
		System.out.println("插入后顺序是:");
		display(list);
	}
	
	public static void main(String[] args) {
		Tool tool = new Tool();
		Scanner sc = new Scanner(System.in);
		int num = 0;
		while (true) {
			num = tool.inputNum("请输入待排序的数的个数(输入q退出):", sc);
			if (num != -1) {
				ArrayList<Integer> list = new ArrayList<Integer>();
				int n = 1;
				boolean quit = false;
				while (true) {
					int input1 = tool.inputNum("请输入第" + n + "个数(输入q退出):", sc);
					if (input1 != -1) {
						list.add(input1);
						if (n == num) {
							Sort sort = new Sort();
							if (sort.isSort(list) == true) {
								System.out.println("输入顺序有序:");
								sort.display(list);
								input1 = tool.inputNum("请输入插入的数(输入q退出):", sc);
								if (input1 != -1) {
									sort.insert(input1, list);
								} else {
									quit = true;
									break;
								}
							} else {
								sort.run(list);
							}
							break;
						}
						n++;
					} else {
						quit = true;
						break;
					}
				}
				if (quit == true) {
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
