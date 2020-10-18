#pragma once
#include<iostream>
#include<fstream>
#include<string>



// class store 

class  store
{
private:

	int item_id;
	std::string item_name;
	float item_Cost;
	int originalStock;
	int itemReceivNum;
	int itemSoldnum;
	int remainStock;

public:
	
	//staff functions
	void creatStaffAcount();
	void login(); 

	// global functions
	void main_menu();
	void sellingProduct();
	void inventoryOptions();
	void productOptions();

	//inventory functions
	void displayAll();
	void displayItem();
	void displayProductMouv();
	
	//product functions
	void creatItem();
	int searchItem(int);
	void modifyProduct(); 
	void editData(int);
	void receivingProduct(int);
	void deleteItem(int);
};

