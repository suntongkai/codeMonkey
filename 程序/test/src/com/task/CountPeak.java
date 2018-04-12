package com.task;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class CountPeak {
	
	private String origin_path;
	private String peak_path;
	@SuppressWarnings("unchecked")
	private ArrayList<String>[] peak_position = new ArrayList[24];
	@SuppressWarnings("unchecked")
	private ArrayList<String>[] fold_enrichment = new ArrayList[24];
	private String result_path;
	
	public CountPeak(String origin_path, String peak_path, String result_path) {
		this.origin_path = origin_path;
		this.peak_path = peak_path;
		for (int i = 0; i < peak_position.length; i++) {
			peak_position[i] = new ArrayList<String>();
			fold_enrichment[i] = new ArrayList<String>();
		}
		this.result_path = result_path;
	}

	public void readPeakPosition() {		
		File peak_file = new File(peak_path);
		BufferedReader read = null;
		try {
			read = new BufferedReader(new FileReader(peak_file));
			String line = null;
			while ((line = read.readLine()) != null) {
				line = line.trim();
				line = line.replace(" ", "\t");
				String[] str = line.split("\t");
				String num = str[0].substring(3, str[0].length());				
				if (num.equals("X")) {
					peak_position[22].add(str[4]);
					fold_enrichment[22].add(str[7]);
				} else if (num.equals("Y")) {
					peak_position[23].add(str[4]);
					fold_enrichment[23].add(str[7]);
				} else {
					int n = Integer.valueOf(num);
					peak_position[n - 1].add(str[4]);
					fold_enrichment[n - 1].add(str[7]);
				}
			}
			read.close();
		} catch (IOException e) {			
			e.printStackTrace();
		}
	}
	
	public void calculateRange() {
		File origin_file = new File(origin_path);
		BufferedReader read = null;
		try {
			read = new BufferedReader(new FileReader(origin_file));
			String line = null;
			String old_num = "";
			int tag = 0;		
			while ((line = read.readLine()) != null) {
				line = line.trim();
				line = line.replace(" ", "\t");
				String[] str = line.split("\t");
				String num = str[2].substring(3, str[2].length());
				if (!old_num.equals(num)) {
					tag = 0;
					old_num = num;
				}
				int start = Integer.valueOf(str[3]);
				int end = Integer.valueOf(str[4]);
				if (num.equals("X")) {
					for (int i = tag; i < peak_position[22].size(); i++) {
						int p = Integer.valueOf(peak_position[22].get(i));
						if (start < p && p < end) {
							String content = String.valueOf(p - start) + "\t" + fold_enrichment[22].get(i);
							writeFile(result_path, content);
							tag = i + 1;
						} else if (p > end) {
							break;
						}					
					}
				} else if (num.equals("Y")) {
					for (int i = tag; i < peak_position[22].size(); i++) {
						int p = Integer.valueOf(peak_position[23].get(i));
						if (start < p && p < end) {
							String content = String.valueOf(p - start) + "\t" + fold_enrichment[23].get(i);
							writeFile(peak_path, content);
							tag = i + 1;
						} else if (p > end) {
							break;
						}
					}
				} else {
					int n = Integer.valueOf(num);
					for (int i = tag; i < peak_position[n - 1].size(); i++) {
						int p = Integer.valueOf(peak_position[n - 1].get(i));
						if (start < p && p < end) {
							String content = String.valueOf(p - start) + "\t" + fold_enrichment[n - 1].get(i);
							writeFile(peak_path, content);
							tag = i + 1;
						} else if (p > end) {
							break;
						}
					}
				}
			}
			read.close();
		} catch (IOException e) {			
			e.printStackTrace();
		}
	}
	
	public void writeFile(String f, String s) {
		File file = new File(f);
		try {
	        if(!file.exists()){
			    file.createNewFile();
	        }
		    FileWriter writer = new FileWriter(file, true);
		    writer.write(s + "\n");
		    writer.close();
		} catch (IOException e) {
		    e.printStackTrace();  
		}
	}
	
	public static void main(String[] args) {
		String origin_path = "F:/Origin.txt";
		String  peak_path = "F:/Peak2_2.txt";
		String result_path = "F:/result2.txt";
		CountPeak sp = new CountPeak(origin_path, peak_path, result_path);
		sp.readPeakPosition();
		sp.calculateRange();			
		System.out.println("ok");
	}
}
