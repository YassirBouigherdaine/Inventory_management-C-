#include"storeclass.h"

// inventory functions



void store::inventoryOptions()
{
	system("cls");

	int option;
	std::cout << "\n\n\t\t**************************************************\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t\t\t   [1] Inventory list\n";
	std::cout << "\t\t\t\t   [2] show mouvements of products\n";
	std::cout << "\t\t\t\t   [3] product details\n";
	std::cout << "\t\t\t\t   [4] Exit\n";
	std::cout << "\n\t\t**************************************************\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\n\t\t\t Enter your choice: ";
	std::cin >> option;

	switch (option)
	{
	case 1: displayAll();
		break;

	case 2: displayProductMouv();
		break;

	case 3: displayItem();
		break;

	case 4: break;
		break;

	default: std::cout << "\n\t\t\t Invalid choice\n";
		std::cin.get();
		std::cout << "\n\t\t\tPress [Enter] to try again\n";
		std::cin.get();
		break;
	}

}


// inventory list
void store::displayAll()
{
	system("cls");

	std::ifstream fin;
	fin.open("storeFile.txt", std::ios::in | std::ios::binary);
    fin.read((char*)this, sizeof(store));

	if (fin.is_open())
	{
		std::cout << "\n----------------------------------INVENTORY LIST-------------------------------------------\n";
		std::cout << "-------------------------------------------------------------------------------------------\n";
		std::cout << "    \t\t ID \t\t NAME \t\t COST \t\t  REMAIN STOCK \t\n";
		std::cout << "-------------------------------------------------------------------------------------------\n";

		while (!fin.eof())
		{
			remainStock = (originalStock + itemReceivNum) - itemSoldnum;    //to show the current remain stock

			std::cout << "    \t\t " << item_id << "\t\t " << item_name << "\t\t  " << item_Cost << "\t\t\t" << remainStock << std::endl;
			std::cout << "-------------------------------------------------------------------------------------------\n";

			fin.read((char*)this, sizeof(store));
		}
	}
	else
	{
		std::cout << "\n\t\tError occurred in opening the file\n";
	}
	
	fin.close();

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


// show item details
void store::displayItem()
{
	std::ifstream fin;
	fin.open("storeFile.txt", std::ios::in | std::ios::binary);

	if (fin.is_open())
	{
		int id;
		int exist = 0;
		std::cout << "\n\t\t Enter ID : ";
		std::cin >> id;

		system("cls");

		exist = searchItem(id);

		while (!fin.eof())
		{
			if (exist)
			{
				fin.read((char*)this, sizeof(store));

				if (item_id == id)
				{
					std::cout << "\n----------------------------------PRODUCT DETAILS----------------------------------------------------------\n";
					std::cout << "---------------------------------------------------------------------------------------------------------\n";
					std::cout << "\tID\tNAME\t  COST\t  ORIGINAL STOCK\tRECIEVING\tSALES \t    REMAIN STOCK\t\n";
					std::cout << "--------------------------------------------------------------------------------------------------------\n";

					remainStock = (originalStock + itemReceivNum) - itemSoldnum;

					std::cout << "\t" << item_id << "\t" << item_name << "\t  " << item_Cost << "\t\t" << originalStock << "\t\t  " << itemReceivNum << "\t\t   " << itemSoldnum << "\t\t" << remainStock << std::endl;

					// advertising to avoid exceptions and risks
					if (remainStock <= 10)
					{
						std::cout << "\n\n\t\t\t you should contact the supplier\n";
					}

					break;
				}
			}
			else
			{
				std::cout << "\n\n\t\t\t Item not found";
				break;
			}
		}
	   
	}
	else
	{
		std::cout << "\n\t\tError occurred in opening the file\n";
	}

	fin.close();

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}


// display mouvements of products
void store::displayProductMouv()
{
	int Id, mouv;
	std::string date, voucherType;

	std::ifstream fread;
	fread.open("productMouvement.txt", std::ios::in | std::ios::binary);

	if (fread.good())
	{
		system("cls");

		fread >> Id >> date >> voucherType >> mouv;

		std::cout << "\n----------------------------------MOUVEMENTS OF PRODUCTS-------------------------------------------------\n";
		std::cout << "\n\t\t\tID" << "\t Date  " << "\t  " << "  Voucher type" << "\t" << "Amount\n";
		std::cout << "---------------------------------------------------------------------------------------------------------\n";

		while (!fread.eof())
		{
			std::cout << "\t\t\t" << Id << "\t" << date << "\t" << voucherType << "\t\t " << mouv << std::endl;
			std::cout << "---------------------------------------------------------------------------------------------------\n";
			fread >> Id >> date >> voucherType >> mouv;
		}
	}
	else
	{
		std::cout << "\n\t\tError occurred in opening the file\n";
	}

	fread.close();
	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}
