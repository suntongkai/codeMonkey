package com.task;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.FileChannel.MapMode;

public class ReadLine {
	
	private File origin_file;
	
	public ReadLine(String origin_path) {
		origin_file = new File(origin_path);
	}

	public void readLine() {
		BufferedReader read = null;
		try {
			read = new BufferedReader(new FileReader(origin_file));
			String line = null;
			while ((line = read.readLine()) != null) {
				System.out.println(line);
			}
		} catch (IOException e) {			
			e.printStackTrace();
		}
	}
	
	public void mappedBuffer() {
		try {
			RandomAccessFile raf = new RandomAccessFile(origin_file, "r");	    	
			FileChannel fc = raf.getChannel();
			MappedByteBuffer mappedByteBuffer = fc.map(MapMode.READ_ONLY, 0, origin_file.length());
	    	byte[] str = new byte[128];
	    	for (int i = 0; i < origin_file.length(); i += 128) {
                if (origin_file.length() - i >= 128) {
                    for (int j = 0; j < 128; j++) {
                    	str[j] = mappedByteBuffer.get(i + j);
                    }
                } else {
                	str = new byte[(int)(origin_file.length() - i)];
                    for (int j = 0; j < origin_file.length() - i; j++) {                	
                    	str[j] = mappedByteBuffer.get(i + j);                 	
                    }                  
                }
                System.out.print(new String(str));
	    	}
	    	raf.close();
    	} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {  
            e.printStackTrace();  
    	}	    	
	}
	
	public static void main(String[] args) {
		String origin_path = "F:\\code_monkey\\LGL_multhread\\1.txt";
		ReadLine t = new ReadLine(origin_path);
		t.readLine();
		//t.mappedBuffer();
		System.out.println("ok");
	}
}
