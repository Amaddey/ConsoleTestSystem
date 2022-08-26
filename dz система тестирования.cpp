#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	Account* account[2];

	fstream userData;

	Admin adminVar;
	User userVar;

	cout << "1 - Вход для админа\n";
	cout << "2 - Вход для тестируемого\n";
	cout << "enter : ";
	int globalchoice;
	cin >> globalchoice;
	cin.ignore(123, '\n');

	if (globalchoice == 1)
	{
		if (adminVar.CheckEmpty() == 0)
		{
			adminVar.Registration();
		}
		else
		{
			adminVar.Authorization();
			if (adminVar.getAdminEntrance() == true)
			{
				system("pause");
				system("cls");
				cout << "\nМеню администратора \n";
				cout << "\n1 - замена пароля\n";
				cout << "\n0 - выйти\n";
				cout << "input :";
				int choice;
				cin >> choice;

				if (choice == 1)
				{

					//system("pause");
					system("cls");
					cout << "\nChange Profile\n";
					cout << "1 - Admin\\ 2 - User\n";
					cout << "input :";
					int choice;
					cin >> choice;

					if (choice == 1)
					{
						
						adminVar.ChangeProfile(); 
					}
					else if (choice == 2)
					{
						userVar.ChangeProfile();
					}
					else
					{
						cout << "Error\n";
					}
				}

				//cout << "\nВ дороботке для экзамена...\n";
			}
		}
	}
	else if (globalchoice == 2)
	{
		cout << "Вы уже зарегистрированны?\n";
		cout << "1 - да/ 0 - нет\n";
		cout << "input :";
		int choiceReg;
		cin >> choiceReg;
		cin.ignore();
		if (choiceReg == 1)
		{
			userVar.isRegistered();
		}
		else if (choiceReg == 0)
		{
	 	  userVar.Registration();
		}

	}
	else
	{
		cout << "Error\n";
	}	

	return 0;
}
