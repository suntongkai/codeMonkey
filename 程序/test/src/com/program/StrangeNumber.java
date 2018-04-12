package com.program;

public class StrangeNumber {
	
	public StrangeNumber() {
		
	}

	public void findStrangeNumber() {
		System.out.println("满足条件的数是:");
		for (int i = 0; i < 10000; i++) {
			if (Math.sqrt(i + 100) % 1 == 0 && Math.sqrt(i + 100 + 168) % 1 == 0) {
				System.out.println(i);
			}
		}
	}
	
	public static void main(String[] args) {
		StrangeNumber sn = new StrangeNumber();
		sn.findStrangeNumber();
		System.out.println("over");
	}
}
