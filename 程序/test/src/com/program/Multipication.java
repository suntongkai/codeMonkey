package com.program;

public class Multipication {
	
	public Multipication() {
		
	}
	
	public void display() {
		for (int i = 1; i <= 9 ; i++) {
			for (int j = 1; j < i; j++) {
				System.out.print(j + " * " + i + " = " + j * i + '\t');
			}
			System.out.println(i + " * " + i + " = " + i * i);
		}
	}

	public static void main(String[] args) {
		Multipication m = new Multipication();
		m.display();
	}
}
