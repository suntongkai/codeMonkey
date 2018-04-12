package com.program;

public class NarcissisticNumber {
	
	public NarcissisticNumber() {
		
	}
	
	public void findNarcissisticNumber() {
		System.out.println("水仙花数是:");
		for (int i = 100; i <= 999; i++) {
			int a = i / 100;
			int b = (i % 100) / 10;
			int c = i % 10;
			if (Math.pow(a, 3) + Math.pow(b, 3) + Math.pow(c, 3) == i) {
				System.out.println(i+ " = " + a + "^3" + " + " + b + "^3" + " + " + c + "^3");
			}
		}
	}

	public static void main(String[] args) {
		NarcissisticNumber nn = new NarcissisticNumber();
		nn.findNarcissisticNumber();
		System.out.println("over");
	}
}
