package com.task;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * 按行读取标记文件中标记位置，累加数据文件中对应位置的数
 * @author sun
 *
 */
public class Accumulate {
	
	private String input_path1;
	private String input_path2;
	private int sum = 0;

	public Accumulate(String input_path1, String input_path2) {
		this.input_path1 = input_path1;
		this.input_path2 = input_path2;
	}
	
	public void calculate() {
		File input_file1 = new File(input_path1);
		File input_file2 = new File(input_path2);
		BufferedReader read1 = null;
		BufferedReader read2 = null;
		String line1 = null;
		String line2 = null;
		try {
			read1 = new BufferedReader(new FileReader(input_file1));
			read2 = new BufferedReader(new FileReader(input_file2));
			while ((line1 = read1.readLine()) != null && (line2 = read2.readLine()) != null) {
				line1 = line1.trim();				
				line1 = line1.replace(" ", "\t");
				String[] str1 = line1.split("\t");
				line2 = line2.trim();				
				line2 = line2.replace(" ", "\t");
				String[] str2 = line2.split("\t");
				for (int i = 0; i < str2.length; i++) {
					if (Integer.valueOf(str2[i]) == 1) {
						sum = sum + Integer.valueOf(str1[i]);
					}
				}				
			}
			read1.close();
			read2.close();	
		} catch (IOException e) {			
			e.printStackTrace();
		}
	}
	
	public void show() {
		System.out.println("sum:" + sum);
	}
	
	public static void main(String []args) {
		if (args.length == 2) {
			long t = System.currentTimeMillis();
			Accumulate test = new Accumulate(args[0], args[1]);
			test.calculate();
			test.show();
			t = System.currentTimeMillis() - t;
			System.out.println("run time:" + t + "ms");
        } else {
            System.out.println("Usage: java -cp *.jar com.Task datafilepath1 flagfilepath2");           
            System.exit(0);
        }
	}
}
