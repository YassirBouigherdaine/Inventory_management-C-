#include"storeclass.h"


//register & login & main menu functions 

 
//making acount for staff
void store::creatStaffAcount()
{
	system("cls");

	std::string admin_password , user_name , pass_word;

	std::ofstream fout;
	fout.open("staffDetails.txt", std::ios::app | std::ios::binary);

	//only admin can creat an acount
	while (admin_password != "1234")
	{
		std::cout << "\n\n\t\t\tadmin password : ";
		std::cin >> admin_password;

		system("cls");
	}
	
	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t*                   CREAT ACOUNT                 *\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\n\n\t\tusername : ";
	std::cin >> user_name;
	std::cout << "\n\t\tpassword : ";
	std::cin >> pass_word;

	fout << user_name << std::endl << pass_word;
	fout.close();

	login();
}


//check staff username & password 
bool checklogin(std::string userName , std::string passWord)
{
	bool access;
	std::string user_name;
	std::string pass_word;

	std::ifstream fin;
	fin.open("staffDetails.txt", std::ios::in | std::ios::binary);
	fin >> user_name >> pass_word;

	if (userName == user_name && passWord == pass_word)
	{
		access = true;
	}
	else
	{
		access = false;
	}

	fin.close();
	return (access);
}

// login function
void store::login()
{
	start:

	int option;
	std::string userName;
	std::string passWord;
	bool access = false;

	system("cls");
	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t*                     WELCOME                    *\n";
	std::cout << "\t\t**************************************************\n";
	std::cout << "\n\n\t\t\t\t[1] register\n";
	std::cout << "\t\t\t\t[2] login\n";
	std::cout << "\n\t\t\t Enter your choice: ";
	std::cin >> option;

	if (option == 1)
	{
		creatStaffAcount();
	}
	else if (option == 2)
	{
		system("cls");

		while (access == false)
		{
			std::cout << "\t\t**************************************************\n";
			std::cout << "\t\t**************************************************\n";
			std::cout << "\t\t*                                                *\n";
			std::cout << "\t\t*              STORE SYSTEM MANAGEMENT           *\n";
			std::cout << "\t\t*                     WELCOME                    *\n";
			std::cout << "\t\t*                                                *\n";
			std::cout << "\t\t**************************************************\n";
			std::cout << "\t\t**************************************************\n\n";
			std::cout << "\t\t\t\tusername: ";
			std::cin >> userName;
			std::cout << "\t\t\t\tpassword: ";
			std::cin >> passWord;

			access = checklogin(userName, passWord);

			if (!access)
			{
				std::cout << "\n\t\t\t Invalid username or password\n";
				std::cout << "\n\t\t\t Press [Enter] to continue";
				std::cin.get();
				std::cin.get();
				system("cls");
			}
			else
			{
				std::cout << "\n\n\t\t\t\t***welcome "<<userName <<"***"<< std::endl;
				std::cin.get();
				std::cout << "\n\t\t\t\tPress [Enter] to continue";
				std::cin.get();
				
				system("cls");
				main_menu();
			}
		}	
	}
	else
	{
		std::cin.get();
		std::cout << "\n\t\t\tInvalid choice\n";
		std::cout << "\n\t\t\tPress [Enter] to try again\n";
		std::cin.get();
		goto start;
	}
}
	
// main menu function
void store::main_menu()
{
	int option;
	do
	{
		system("cls");
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**                                              **\n";
		std::cout << "\t\t*              STORE SYSTEM MANAGEMENT           *\n";
		std::cout << "\t\t*                      HOME                      *\n";
		std::cout << "\t\t**                                              **\n";
		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t**************************************************\n\n\n";
		std::cout << "\t\t\t\t   [1] Selling\n";
		std::cout << "\t\t\t\t   [2] Product\n";
		std::cout << "\t\t\t\t   [3] Inventory\n";

		std::cout << "\n\t\t\t Enter your choice: ";
		std::cin >> option;

		switch (option)
		{
			// selling a product and make the bill
		    case 1: sellingProduct();
			        break;

			// functions related to the product
		    case 2: productOptions();
			        break;

			// functions related to the inventory
		    case 3: inventoryOptions();
			        break;

		    default: std::cout << "\n\t\t\t Invalid choice\n";
			         std::cout << "\n\t\t\tPress [Enter] to try again\n";
			         std::cin.get();
			         std::cin.get();
			         break;
		}

	} while (true);
}




