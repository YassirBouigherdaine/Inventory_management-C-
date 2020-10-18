#include"storeclass.h"



// selling item and get the bill

void store::sellingProduct()
{
	system("cls");

	int id, exist, mouv;
	std::string date;
	std::string voucherType = "out";

	std::cout << "\n\n\t\t Enter ID : ";
	std::cin >> id;

	exist = searchItem(id);
	if (exist)
	{
		std::fstream file("storeFile.txt", std::ios::out | std::ios::in | std::ios::binary);
		std::ofstream newFile("productMouvement.txt", std::ios::app | std::ios::binary);

		std::cout << "\n\n\t\t Enter date: ";
		std::cin >> date;                                   //day/mon/year
		std::cout << "\n\n\t\t Enter sold amount: ";
		std::cin >> mouv;                                   //sold amount

		if (mouv < remainStock)                             // to prevent stockouts
		{
			//register selling operation
			newFile << id << "\t" << date << "\t" << voucherType << "\t" << mouv << "\t" << std::endl;

			while (file.read((char*)this, sizeof(store)))
			{
				if (id == item_id)
				{
					itemSoldnum += mouv;

					//place the file pointer to the required postion 
					unsigned __int64 pos = file.tellg();
					file.seekp(pos - sizeof(store), std::ios::beg);
					file.write((char*)this, sizeof(store));
					break;
				}
			}

			std::cout << "\n\t\t\t the operation was registred successfully\n";
			std::cin.get();
			std::cout << "\n\t\t\t Press [ENTER] to view the bill";
			std::cin.get();

			system("cls");

			double price = item_Cost + (item_Cost * 0.3);            // profit margin = 30%
			
			// the bill
			std::cout << "\n ************\n";
			std::cout << " store name ";
			std::cout << "\n ************\n";
			std::cout << "\n                                                   Date: " << date;
			std::cout << "\n\n-----------------------------------Bill no: ------------------------------------\n";
			std::cout << "\n--------------------------------------------------------------------------------\n";
			std::cout << "\n\t\tItem name\t\tPrice  \t\tAmount  \t\t              \n";
			std::cout << "\n--------------------------------------------------------------------------------\n";
			std::cout << "\t\t " << item_name << "\t\t\t" << price << " \t\t   " << mouv << " \t\t " << "\n\n";
			std::cout << "\n--------------------------------------------------------------------------------\n";
			std::cout << "                                        Toltal:             " << price * mouv << "      \n";
			std::cout << "--------------------------------------------------------------------------------\n\n";
			std::cout << "\n\t\t\t Thank you for shopping \n";
		}
		else
		{
			std::cout << "\n\t\t\t the operation cannot be completed\n";
			std::cin.get();
		}

		file.close();
		newFile.close();
	}
	else
	{
		std::cout << "\n\n\t\t\t  Item not found\n";
		std::cin.get();
	}

	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}
