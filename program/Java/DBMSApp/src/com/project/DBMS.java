package com.project;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * DBMSApp
 * @author codeMonkey_sun
 * @ refer to mysql, but differet from mysql
 */
public class DBMS {
	
	private String newTableName;// new creative table name
	private ArrayList<String> newColumn = new ArrayList<String>();// new creative column name
	
	public DBMS(String in) {
		selectFunction(in);
	}
	
	public void selectFunction(String in) {
		String showTable = "^\\s*((?i)show)\\s+((?i)tables)\\s*;\\s*$";
		Pattern showTableP = Pattern.compile(showTable);
		Matcher showTableM = showTableP.matcher(in);
		String createTable = "^\\s*((?i)create)\\s+((?i)table)\\s+[a-zA-Z0-9_$]+\\s*\\(\\s*[a-zA-Z0-9_$]+\\s+[a-zA-Z]+(\\s*,\\s*[a-zA-Z0-9_$]+\\s+[a-zA-Z]+)*\\s*\\)\\s*;\\s*$";
		Pattern createTableP = Pattern.compile(createTable);
		Matcher createTableM = createTableP.matcher(in);
		String dropTable = "^\\s*((?i)drop)\\s+((?i)table)\\s+[a-zA-Z0-9_$]+\\s*;\\s*$";
		Pattern dropTableP = Pattern.compile(dropTable);
		Matcher dropTableM = dropTableP.matcher(in);
		String insert = "^\\s*((?i)insert)\\s+((?i)into)\\s+[a-zA-Z0-9_$]+\\s*\\(\\s*[a-zA-Z0-9_$]+(\\s*,\\s*[a-zA-Z0-9_$]+)*\\s*\\)\\s*((?i)values)\\s*\\(\\s*(\")*[a-zA-Z0-9]+(\")*(\\s*,\\s*(\")*[a-zA-Z0-9]+(\")*)*\\s*\\)\\s*;\\s*$";
		Pattern insertP = Pattern.compile(insert);
		Matcher insertM = insertP.matcher(in);
		String delete = "^\\s*((?i)delete)\\s+((?i)from)\\s+[a-zA-Z0-9_$]+(\\s+((?i)where)\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*(\\s+((?i)(and|or))\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*)*)*\\s*;\\s*$";
		Pattern deleteP = Pattern.compile(delete);
		Matcher deleteM = deleteP.matcher(in);
		String update = "^\\s*((?i)update)\\s+[a-zA-Z0-9_$]+\\s+((?i)set)\\s+[a-zA-Z0-9_$]+\\s*=\\s*(\")*[a-zA-Z0-9]+(\")*(\\s*,\\s*[a-zA-Z0-9_$]+\\s*=\\s*(\")*[a-zA-Z0-9]+(\")*)*(\\s+((?i)where)\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*(\\s+((?i)(and|or))\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*)*)*\\s*;\\s*$";
		Pattern updateP = Pattern.compile(update);
		Matcher updateM = updateP.matcher(in);
		String select = "^\\s*((?i)select)\\s+(\\*|([a-zA-Z0-9_$]+(\\s*,\\s*[a-zA-Z0-9_$]+)*))\\s+((?i)from)\\s+[a-zA-Z0-9_$]+(\\s+((?i)where)\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*(\\s+((?i)(and|or))\\s+[a-zA-Z0-9_$]+\\s*(=|<>|!=|>|<|>=|<=)\\s*(\")*[a-zA-Z0-9]+(\")*)*)*\\s*;\\s*$";
		Pattern selectP = Pattern.compile(select);
		Matcher selectM = selectP.matcher(in);
		in = in.replaceAll(" +", " ");
		if (showTableM.matches()) {
			showTable();
		} else if (createTableM.matches()) {
			createTable(in);
		} else if (dropTableM.matches()) {
			dropTabel(in);
		} else if (insertM.matches()) {
			insert(in);
		} else if (deleteM.matches()) {
			deleteFrom(in);
		} else if (updateM.matches()) {
			updateSet(in);
		} else if (selectM.matches()) {
			select(in);
		} else {
			System.out.println("invalid commond");
		}
	}
	
	public void showTable() {
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath());
		File[] files = dataFile.listFiles();
		if (files.length == 0) {
			System.out.println("No table");
			return;
		}
		System.out.println(files.length + " tables in database");
		for (int i = 0;i < files.length; i++) {
			String[] fullName = files[i].getName().split("[.]");
			System.out.println(i + 1 + ": " + fullName[0]);
		}
	}
	
	public void createTable(String in) {
		String tableName = getTableName(in, "table");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			System.out.println("Table " + tableName + " already exists!");
		} else {
			newTableName = tableName;
			int start = in.indexOf("(");
			int end = in.lastIndexOf(")");// maybe data type exits ()
			String[] columnArray = getColumnArray(in, start, end);
			setNewColumn(columnArray);
			for (int i = 0; i < columnArray.length; i++) {
				columnArray[i] = columnArray[i].trim();
				writeFile(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt", columnArray[i] +
						(i == columnArray.length - 1 ? "\n" : "\t"));
			}
			System.out.println("Create table success!");
		}
	}
	
	public String getTableName(String in, String flag) {
		String copyIn = in;
		copyIn = copyIn.toLowerCase();
		int index = copyIn.indexOf(flag) + flag.length() + 1;// the first letter of column name
		String tableName = "";
		for (int i = index; in.charAt(i) != ' ' && in.charAt(i) != '(' && in.charAt(i) != ';'; i++) {
			tableName = tableName + in.charAt(i);
		}
		return tableName;
	}
	
	public String[] getColumnArray(String in, int start, int end) {
		String subIn = in.substring(start + 1, end);
		subIn = subIn.trim();
		String[] columnArray = subIn.split(",");
		return columnArray;
	}
	
	public void setNewColumn(String[] columnArray) {
		for (int i = 0; i < columnArray.length; i++) {
			columnArray[i] = columnArray[i].trim();
			String[] strs = columnArray[i].split(" ");
			newColumn.add(strs[0]);
		}
	}
	
	/**
	 * @author sun
	 * @function write file
	 * @param f the file to write
	 * @param s the content to write
	 */
	public void writeFile(String f, String s) {
		File file = new File(f);
		try {
	        if(!file.exists()){
			    file.createNewFile();
	        }
		    FileWriter fw = new FileWriter(file, true);
		    fw.write(s);
		    fw.close();
		} catch (IOException e) {
		    e.printStackTrace();  
		}
	}
	
	public void dropTabel(String in) {
		String tableName = getTableName(in, "table");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			dataFile.delete();
			System.out.println("Drop table success!");
		} else {
			System.out.println("Table " + tableName + " doesn't exist!");
		}
	}
	
	public void insert(String in) {
		String tableName = getTableName(in, "into");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			int start = in.indexOf("(");
			int end = in.indexOf(")");
			String[] columnArray = getColumnArray(in, start, end);
			start = in.lastIndexOf("(");
			end = in.lastIndexOf(")");
			String[] valueArray = getColumnArray(in, start, end);
			if (valueArray.length == columnArray.length) {
				if (!(tableName.equals(newTableName))) {// without buffer
					setNewColumn(dataFile);
				}
				int j = 0;
				String value = "";
				int valueCount = 0;// count if all of columnArray found in newColumn
				for (int i = 0; i < newColumn.size(); i++) {
					for (j = 0; j < columnArray.length; j++) {
						columnArray[j] = columnArray[j].trim();
						if (newColumn.get(i).equals(columnArray[j])) {
							value = value + valueArray[j].trim() + "\t";
							valueCount++;
							break;
						}
					}
					if (j == columnArray.length) {// not find
					    value = value + "NULL" + "\t";
					}
				}
				if (valueCount == valueArray.length) {
					writeFile(dataFile.toString(), value.substring(0, value.length() - 1) + "\n");// remove \t in the end
					System.out.println("Insert success!");
				} else {// give which one is not in newColumn
					for (int i = 0; i < columnArray.length; i++) {
						for (j = 0; j < newColumn.size(); j++) {
							if (columnArray[i].equals(newColumn.get(j))) {
								break;
							}
						}
						if (j == newColumn.size()) {
							System.out.println("Unknown column " + columnArray[i]);
						}
					}
				}
			} else {
				System.out.println("Column count doesn't match value count!");
			}
		} else {
			System.out.println("Table " + tableName + " doesn't exist!");
		}
	}
	
	public void setNewColumn(File dataFile) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader(dataFile));
			String line = reader.readLine();
			String[] strs = line.split("\t");
			setNewColumn(strs);
			reader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void deleteFrom(String in) {
		String tableName = getTableName(in, "from");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			try {
			    BufferedReader reader = new BufferedReader(new FileReader(dataFile));
			    String line = reader.readLine();
			    String copyIn = in;
				copyIn = copyIn.toLowerCase();
				int start = copyIn.indexOf("where");
			    if (start == -1) {// without where
			    	reader.close();
			    	dataFile.delete();
					writeFile(dataFile.toString(), line + "\n");
					System.out.println("Delete success!");
					return;
				}
			    int end = in.indexOf(";");
			    setCondition(start, end);
			    System.out.println("developing...");
			    /*if (!(tableName.equals(newTable))) {// without buffer
					setNewColumn(dataFile);
				}
				int start = copyIn.indexOf("where") + 6;//++++++++++
				int end = in.indexOf("=");
				String condition = in.substring(start, end).trim();
				start = end;
				end = in.indexOf(";");
				String value = in.substring(start + 1, end).trim();
				int index = -1;// condition index
				for (int i = 0; i < newColumn.size(); i++) {
					if (newColumn.get(i).equals(condition)) {
						index = i;
					}
				}
				if (index == -1) {// condition error
					System.out.println("Unknown column" + condition);
					read.close();
					return;
				}
				line = read.readLine();
				File newFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + "temp");
				while (line != null) {
			    	String[] strs = line.split("\t");
			    	if (!(strs[index].equals(value))) {
			    		writeFile(newFile.toString(), line);
			    	}
			    	line = read.readLine();
			    }
				dataFile.delete();
				newFile.renameTo(new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName));*/
			    reader.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} else {
			System.out.println("Table " + tableName + " doesn't exists!");
		}
	}
	
	public void setCondition(int start, int end) {
		
	}
	
	public void updateSet(String in) {
		String tableName = getTableName(in, "update");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			String copyIn = in;
			copyIn = copyIn.toLowerCase();
			int start = copyIn.indexOf("where");
			int end = 0;
		    if (start == -1) {// without where
		    	end = in.indexOf(";");
		    } else {
		    	end = copyIn.indexOf("where");
		    }
			start = copyIn.indexOf("set") + 4;
			String subIn = in.substring(start, end);
			subIn = subIn.trim();
			String[] strs = subIn.split(",");
			ArrayList<String> columnList = new ArrayList<String>();
			ArrayList<String> valueList = new ArrayList<String>();
			for (int i = 0; i < strs.length; i++) {
				String[] columnAndValue = strs[i].split("=");
				columnList.add(columnAndValue[0].trim());
				valueList.add(columnAndValue[1].trim());
			}
			ArrayList<Integer> order = getColumnOrder(tableName, dataFile, columnList);
			try {
			    BufferedReader reader = new BufferedReader(new FileReader(dataFile));
			    String line = reader.readLine();
			    File newFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".temp.txt");
			    writeFile(newFile.toString(), line + "\n");
			    line = reader.readLine();// pay attention
			    while (line != null) {
			    	strs = line.split("\t");
			    	line = "";
			    	int j = 0;
			    	for (int i = 0; i < strs.length ; i++) {
			    		if (i == order.get(j)) {
			    			line = line + valueList.get(j) + "\t";
			    			j++;
			    		} else {
			    			line = line + strs[i] + "\t";
			    		}
			    		if (j == order.size()) {
			    			j = 0;
			    		}
			    	}
			    	writeFile(newFile.toString(), line.trim() + "\n");
			    	line = reader.readLine();
			    }
			    reader.close();
			    dataFile.delete();
				newFile.renameTo(new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt"));
			    System.out.println("Update table success!");
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} else {
			System.out.println("Table " + tableName + " doesn't exists!");
		}
	}
	
	public ArrayList<Integer> getColumnOrder(String tableName, File dataFile, ArrayList<String> columnList) {
		if (!(tableName.equals(newTableName))) {// without buffer
			setNewColumn(dataFile);
		}
		int j = 0;
		ArrayList<Integer> order = new ArrayList<Integer>();
		int valueCount = 0;
		for (int i = 0; i < newColumn.size(); i++) {
			for (j = 0; j < columnList.size(); j++) {
				if (newColumn.get(i).equals(columnList.get(j))) {
					order.add(i);
					valueCount++;
					break;
				}
			}
		}
		if (valueCount != columnList.size()) {
			for (int i = 0; i < columnList.size(); i++) {
				for (j = 0; j < newColumn.size(); j++) {
					if (columnList.get(i).equals(newColumn.get(j))) {
						break;
					}
				}
				if (j == newColumn.size()) {
					System.out.println("Unknown column " + columnList.get(i));
				}
			}
			return null;
		}
		return order;
	}
	
	public void select(String in) {
		String tableName = getTableName(in, "from");
		File dataFile = new File(getClass().getClassLoader().getResource("DataFile").getPath() + "/" + tableName + ".txt");
		if (dataFile.exists()) {
			String copyIn = in;
			copyIn = copyIn.toLowerCase();
			int end = copyIn.indexOf("from");
			String subIn = in.substring(6, end);
			subIn = subIn.trim();
			String[] strs = subIn.split(",");
			ArrayList<String> columnList = new ArrayList<String>();
			for (int i = 0; i < strs.length; i++) {
				columnList.add(strs[i].trim());
			}
			boolean isAll = false;
			ArrayList<Integer> order = null;
			if (columnList.get(0).equals("*")) {
				isAll = true;
			} else {
				order = getColumnOrder(tableName, dataFile, columnList);
			}
			try {
			    BufferedReader reader = new BufferedReader(new FileReader(dataFile));
			    String line = reader.readLine();
			    while (line != null) {
			    	if (isAll == true) {
			    		System.out.println(line);
			    	} else {
			    		strs = line.split("\t");
			    		for (int i = 0; i < order.size(); i++) {
			    			System.out.print(strs[order.get(i)] + (i == order.size() - 1 ? "\n" : "\t"));
			    		}
			    	}
			    	line = reader.readLine();
			    }
			    reader.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} else {
			System.out.println("Table " + tableName + " doesn't exists!");
		}
	}
	
	public static void main(String[] args) {
		String head = "Welcome to use DBMSApp\n"
				+ "Author: codeMonkey_sun\n"
				+ "----------------\n"
				+ "Input SQL statements please\n"
				+ "Input q to exit\n"
				+ "----------------";
		System.out.println(head);
		Scanner sc = new Scanner(System.in);
		while (true) {
			String in = sc.nextLine();
			if (in.equals("q")) {
				System.out.println("exit");
				break;
			}
			if (in.equals("help")) {
				String help = "* DBMSApp\n" + 
						"@author codeMonkey_sun\n" + 
						"@ refer to mysql, but differet from mysql\n" + 
						"@bug" +
						"@1 can not divide a commond into multiple lines for input\n" + 
						"@2 column name is case sensitive\n" + 
						"@3 without checking data type, without column arribute such as default value, when we create a table\n" + 
						"@4 ";
				System.out.println(help);
			}
			new DBMS(in);
		}
		sc.close();
	}
}
