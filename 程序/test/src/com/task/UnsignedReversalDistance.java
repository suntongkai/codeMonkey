package com.task;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class UnsignedReversalDistance {
	
	private String input_path;
	private String output_path;
	private int length = 0;
	private int show_sequence = 0;
	private String[] sequence;
	private int breakpoint = 0;
	private int pi_min = 0;
	private int start_increasing_strip = 0;// 第一个increasing strip的下标起点
	private int end_increasing_strip = 0;// 第一个increasing strip的下标终点
	private int distance = 0;
	
	public UnsignedReversalDistance(String input_path, String output_path) {
		this.input_path = input_path;
		this.output_path = output_path;
	}

	public void readInput() {// 默认输入文件格式内容无误
		File input_file = new File(input_path);
		BufferedReader read = null;
		String line = null;
		try {
			read = new BufferedReader(new FileReader(input_file));
			line = read.readLine();
			line = line.trim();
			line = line.replace(" ", "\t");
			String[] str = line.split("\t");
			length = Integer.valueOf(str[0]);				
			show_sequence = Integer.valueOf(str[1]);				
			line = read.readLine();
			line = line.trim();
			line = line.replace(" ", "\t");
			sequence = line.split("\t");
			read.close();
		} catch (IOException e) {			
			e.printStackTrace();
		}
	}

	public void compute2Approximation() {
		String origin_sequence = stringArrayToString(sequence);
		ArrayList<String> result_list = new ArrayList<String>();
		int index_pi_min = getBreakpointAndPimin();
		while (breakpoint > 0) {
			if (index_pi_min != 0) {// 有decreasing strip
				if (pi_min == 1) {
					result_list.add(reverse(-1, index_pi_min));// 从开头reverse要从下标-1开始
					distance++;
				} else {
					for (int i = 0; i < sequence.length; i++) {	
						if (pi_min - 1 == Integer.valueOf(sequence[i])) {
							result_list.add(reverse(index_pi_min, i));
							distance++;
							break;
						}
					}
				}
			} else {
				result_list.add(reverse(start_increasing_strip - 1, end_increasing_strip));// reverse increasing strip起始点下标要-1
				distance++;
			}
			index_pi_min = getBreakpointAndPimin();
		}
		writeFile(output_path, String.valueOf(distance));
		writeFile(output_path, origin_sequence);
		if (show_sequence == 1) {
			for (int i = 0; i < result_list.size();i ++) {
				writeFile(output_path, result_list.get(i));
			}
		}
	}
	
	public int getBreakpointAndPimin() {
		int n = 0;		
		if (Integer.valueOf(sequence[0]) > 1) {
			n++;
		}
		if (Integer.valueOf(sequence[sequence.length - 1]) < sequence.length) {
			n++;
		}	
		pi_min = length;
		int index_pi_min = 0;
		int lock = 0;
		int old_lock = 0;
		start_increasing_strip = 0;
		end_increasing_strip = 0;
		for (int i = 0; i < sequence.length - 1; i++) {			
			if (Math.abs(Integer.valueOf(sequence[i]) - Integer.valueOf(sequence[i + 1])) > 1) {
				n++;
				lock++;
			} else {		
				if (Integer.valueOf(sequence[i]) - Integer.valueOf(sequence[i + 1]) > 0) {
					if (pi_min > Integer.valueOf(sequence[i + 1])) {
						pi_min = Integer.valueOf(sequence[i + 1]);
						index_pi_min = i + 1;
					}
				} else {
					if (lock == 0) {// 只执行一次
						lock++;						
						start_increasing_strip = i;
						end_increasing_strip = i + 1;
					} else if (lock - old_lock == 1) {
						lock++;
						old_lock++;
						end_increasing_strip = i + 1;
					}
				}
			}	
		}
		breakpoint = n;
		return index_pi_min;	
	}
	
	public String reverse(int index_pi_min, int index_pi_min_1) {// reverse 区间(a,b)中的(a-1,b)
		if (index_pi_min > index_pi_min_1) {
			for (int i = index_pi_min_1 + 1, j = 0; j < (index_pi_min - index_pi_min_1) / 2; i++, j++) {
				String str = sequence[i];
				sequence[i] = sequence[index_pi_min - j];
				sequence[index_pi_min - j] = str;
			}
		} else {
			for (int i = index_pi_min + 1, j = 0; j < (index_pi_min_1 - index_pi_min) / 2; i++, j++) {
				String str = sequence[i];
				sequence[i] = sequence[index_pi_min_1 - j];
				sequence[index_pi_min_1- j] = str;
			}
		}
		return stringArrayToString(sequence);
	}
	
	public void writeFile(String f, String s) {
		File file = new File(f);
		try {
	        if(!file.exists()){
			    file.createNewFile();
	        }
		    FileWriter writer = new FileWriter(file, true);
		    writer.write(s + "\r\n");
		    writer.close();
		} catch (IOException e) {
		    e.printStackTrace();  
		}
	}
	
	public String stringArrayToString(String[] str) {
		String s = "";
		for (int i = 0; i < str.length - 1; i++) {
			s = s + str[i] + " ";
		}
		s = s + str[str.length - 1];
		return s;
	}
	
	public void compute4Approximation() {
		
	}
	
	public static void main(String []args) {
		if (args.length == 2) {
			long t = System.currentTimeMillis();
			UnsignedReversalDistance urd = new UnsignedReversalDistance(args[0], args[1]);
			urd.readInput();
			urd.compute2Approximation();
			t = System.currentTimeMillis() - t;
			System.out.println("run time:" + t + "ms");
        } else {
            System.out.println("Usage: java -cp *.jar com.Main inputfilepath ouputfilepath");           
            System.exit(0);
        }		
	}
}
