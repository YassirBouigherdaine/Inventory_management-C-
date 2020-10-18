#include"storeclass.h"


//product functions


void store::productOptions()
{
	system("cls");

	int option;
	std::cout << "\n\n\t\t**************************************************\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t\t\t   [1] Creat a product\n";
	std::cout << "\t\t\t\t   [2] Modify product\n";
	std::cout << "\t\t\t\t   [3] Exit\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\n\t\t\t Enter your choice: ";
	std::cin >> option;

	switch (option)
	{
	case 1: creatItem();
		break;

	case 2: modifyProduct();
		break;

	case 3: break;
		break;

	default: std::cout << "\n\t\t\t Invalid choice\n";
		std::cin.get();
		std::cout << "\n\t\t\tPress [Enter] to try again\n";
		std::cin.get();
		break;
	}
}


//check if the item exists in the inventory
int store::searchItem(int id)
{
	int exist = 0;

	std::ifstream fin;
	fin.open("storeFile.txt", std::ios::in | std::ios::binary);

	while (!fin.eof())
	{
		fin.read((char*)this, sizeof(store));

		if (item_id == id)
		{
			exist = 1;
		}
	}

	fin.close();
	return (exist);
}


//creating a new item to be stored in the inventory
void store::creatItem()
{
	system("cls");

	int id, exist = 0;

	std::cout << "\n\n\t\tEnter item details :\n";
	std::cout << "\n\t\t Enter ID : ";
	std::cin >> id;

	exist = searchItem(id);

	if (!exist)
	{
		std::ofstream fout;
		fout.open("storeFile.txt", std::ios::app | std::ios::binary);

		item_id = id;
		std::cout << "\n\t\t Item name: ";
		std::cin >> item_name;
		std::cout << "\n\t\t Item cost: ";
		std::cin >> item_Cost;
		std::cout << "\n\t\t Original stock:";
		std::cin >> originalStock;
		std::cout << "\n\t\t Recieved:";
		std::cin >> itemReceivNum;
		std::cout << "\n\t\t sold:";
		std::cin >> itemSoldnum;

		remainStock = originalStock;                      // at the beginning remainStock = originalStock

		fout.write((char*)this, sizeof(store));

		std::cout << "\n\t\t\t Item has been created successfully\n";
		std::cin.get();
		fout.close();
	}
	else
	{
		std::cout << "\n\n\t\t\tthe item is already registered\n";
		std::cin.get();
	}
	
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();	
}


//modifying record of product
void store::modifyProduct()
{
	int id , choice , exist = 0;

	std::cout << "\n\t\t Enter ID : ";
	std::cin >> id;

	exist = searchItem(id);

	if (exist)
	{
		system("cls");

		std::cout << "\n\n\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t\t\t [1] recieving product\n";
		std::cout << "\t\t\t\t [2] edit product\n";
		std::cout << "\t\t\t\t [3] Delete product\n";
		std::cout << "\t\t\t\t [3] Exit\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\n\t\t\t Enter your choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case 1: receivingProduct(id);
			break;

		case 2:  editData(id);
			break;

		case 3: deleteItem(id);
			break;

		case 4: break;
			break;

		default: std::cout << "\n\t\t\t Invalid choice\n";
			std::cout << "\n\t\t\tPress [Enter] to try again\n";
			std::cin.get();
			break;
		}
	}
	else
	{
		std::cout << "\n\n\t\t\t  Item not found\n";
		std::cin.get();
		std::cout << "\n\t\t\t Press [ENTER] to continue";
		std::cin.get();
	}
} 

//editing received amount
void store::receivingProduct(int id)
{
	int mouv;
	std::string date;
	std::string voucherType ="in";

	std::fstream file("storeFile.txt", std::ios::out | std::ios::in | std::ios::binary);
	std::ofstream newFile("productMouvement.txt", std::ios::app | std::ios::binary);

	std::cout << "\n\n\t\t Enter date: ";
	std::cin >> date;                                   //day/mon/year
	std::cout << "\n\n\t\t Enter received amount: ";
	std::cin >> mouv;                                   //received amount

	//register receiving operation
	newFile << id << "\t" << date << "\t" << voucherType << "\t" << mouv << "\t" << std::endl;

	while (file.read((char*)this, sizeof(store)))
	{
		if (id == item_id)
		{
			itemReceivNum += mouv;
			//place the file pointer to the required postion 
			unsigned __int64 pos = file.tellg();
			file.seekp(pos - sizeof(store), std::ios::beg);
			file.write((char*)this, sizeof(store));
			break;
		}
	}

	file.close();
	newFile.close();

	std::cin.get();
	std::cout << "\n\t\t\t operation has been registered successfully\n";
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


//editing data of product
void store::editData(int id)
{
	std::fstream file;
	file.open("storeFile.txt", std::ios::in | std::ios::out | std::ios::binary);

	if (file.good())
	{
		while (file.read((char*)this, sizeof(store)))
		{
			if (id == item_id)
			{
				system("cls");

				std::cout << "\n\n\t\tEnter news details : ";

				std::cout << "\n\n\t\t ID: ";
				std::cin >> item_id;
				std::cout << "\n\t\t Item name: ";
				std::cin >> item_name;
				std::cout << "\n\t\t Item cost: ";
				std::cin >> item_Cost;
				std::cout << "\n\t\t Original stock:";
				std::cin >> originalStock;
				std::cout << "\n\t\t Recieved:";
				std::cin >> itemReceivNum;
				std::cout << "\n\t\t sold:";
				std::cin >> itemSoldnum;

				remainStock = (originalStock + itemReceivNum) - itemSoldnum;

				//place the file pointer to the required postion 
				int pos = -1 * static_cast<int>(sizeof(store));
				file.seekp(pos, std::ios::cur);
				file.write((char*)this, sizeof(store));

				std::cin.get();
				std::cout << "\n\t\t\t Item modified successfully\n";
				break;
			}
		}
	}
	else
	{
		std::cout << "\n\t\tError occurred in opening the file\n";
	}

	file.close();
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

// delete mouvement of product
void deleteProdMouv(int id)
{
	int Id;
	int mouv;
	std::string date, voucherType;

	std::ifstream fread("productMouvement.txt", std::ios::in | std::ios::binary);
	std::ofstream anotherFile("tempoFile.txt", std::ios::out | std::ios::binary);

	while (!fread.eof())
	{
		fread >> Id >> date >> voucherType >> mouv;

		if (Id != id)
		{
			anotherFile << Id <<"\t"<< date <<"\t"<< voucherType <<"\t"<< mouv << "\t" << std::endl;
		}
	}

	fread.close();
	anotherFile.close();
	remove("productMouvement.txt");
	rename("tempoFile.txt", "productMouvement.txt");
}



// delete product from inventory
void store::deleteItem(int id)
{
	std::fstream fin("storeFile.txt", std::ios::in | std::ios::binary);
	std::fstream newFile("tempFile.txt", std::ios::app | std::ios::binary);

	while (fin.read((char*)this, sizeof(store)))
	{
		if (item_id != id)
		{
			newFile.write((char*)this, sizeof(store));
		}
	}

	fin.close();
	newFile.close();
	remove("storeFile.txt");
	rename("tempFile.txt", "storeFile.txt");

	// deleting mouvements of product
	 deleteProdMouv(id);

	std::cout << "\n\t\t\t Item was deleted successfully\n";
	std::cin.get();
	std::cout << "\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}



