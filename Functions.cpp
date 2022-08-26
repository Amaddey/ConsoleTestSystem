#include "Header.h"

//Another functions - Another functions - Another functions - Another functions

void CheckType(Account* acc)
{
	if (typeid(*acc) == typeid(Admin))
	{
		cout << "This is an admin type\n";
	}
	else if(typeid(*acc) == typeid(User)){
		cout << "This is a user type\n";
	}
}

string Encrypter(string login)
{
	string elogin;
	for (int i = 0; i < login.size(); i++)
	{
		elogin += login[i] + 3;
	}
	return elogin;
}


string Decrypter(string login)
{
	string elogin;
	for (int i = 0; i < login.size(); i++)
	{
		elogin += login[i] - 3;
	}
	return elogin;
}

void AddInformation(string name, string surname, string patronymic, string path)
{
	ofstream out(path, ios::app | ios::out);
	out << name << " " << surname << " " << patronymic << "|" << "0" << "|" << "0" << endl;
	out.close();
}

//User Functions // User Functions // User Functions // User Functions

void User::CheckUserLogin(string login)
{
	userLogs.open(pathLog, ios::app | ios::in);

	login = Encrypter(login);

	string str;
	while (getline(userLogs, str))
	{
		if (str == login)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
			cout << "Пользователь с таким логином уже существует\n";
			SetConsoleTextAttribute(hConsole, 7);
			exit(0);
			break;
		}
	}

	userLogs.close();
}

void User::Registration() 
{
	string log, pass;
	cout << "Login :";
	getline(cin, log);
	cout << "Pass :";
	getline(cin, pass);

	CheckUserLogin(log);

	userLogs.open(pathLog, ios::app | ios::out);
	userPass.open(pathPass, ios::app | ios::out);


	string elogin = Encrypter(log);
	string epass = Encrypter(pass);

	userLogs << elogin << "\n";
	userPass << epass << "\n";

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 10);
	cout << "Данные успешно записаны\n";
	SetConsoleTextAttribute(console, 7);
	userLogs.close();
	userPass.close();
}


void User::isRegistered()
{
	//d2 r2

	string log, pass;
	cout << "Login :";
	getline(cin, log);
	cout << "Pass :";
	getline(cin, pass);



	string ecryptl = Encrypter(log);
	string ecryptp = Encrypter(pass);


	userLogs.open(pathLog, ios::app | ios::in);
	userPass.open(pathPass, ios::app | ios::in);

	string l;
	string p;
	bool isRegistered = false;

	while (getline(userLogs, l))
	{
		if (l == ecryptl)
		{
			while (getline(userPass, p))
			{
				if (p == ecryptp)
				{
					isRegistered = true;
					break;
				}
			}
			break;
		}
	}

	if (isRegistered)
	{
		cout << "Вы успешно зашли\n";
	}


	userLogs.close();
	userPass.close();
}



//Admin functions - Admin functions - Admin functions - Admin functions - Admin functions - Admin functions

void Admin::Registration()
{
	adminData.open(path, ios::out);

	cout << "----- Регистрация админа -----\n";
	cout << "Log :";
	getline(cin, mLogin);
	cout << "Pass :";
	getline(cin, mPassword);

	string elog = Encrypter(mLogin);
	string epass = Encrypter(mPassword);

	adminData << elog << '\n';
	adminData << epass << '\n';

	cout << "----- Admin has registered -----\n";
	adminData.close();
}

void Admin::Authorization()
{

	cout << "Админ уже зарегистрирован\n";
	cout << "Log :";
	getline(cin, mLogin);
	cout << "Pass :";
	getline(cin, mPassword);

	bool logIsTrue = false;
	bool passIsTrue = false;
	int countInLoop = 0;
	adminData.open(path, ios::app | ios::in);
	string l;
	while (getline(adminData, l))
	{
		l = Decrypter(l);
		if (mLogin == l && countInLoop == 0)
		{
			DecryptedLogin = l;
			logIsTrue = true;
		}

		/*if (logIsTrue && countInLoop == 0) {
			cout << "\nЛогины совпадают";
		}*/

		countInLoop++;
		if (countInLoop == 1)
		{
			continue;
		}

		if (mPassword == l)
		{
			DecryptedPassword = l;
			passIsTrue = true;
		}
		/*if (passIsTrue) {
			cout << "\nПароли совпадают";
		}*/
		break;
	}

	adminData.close();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	if (passIsTrue && logIsTrue)
	{
		SetConsoleTextAttribute(hConsole, 10);

		cout << "\nВы успешно вошли в систему \n";
		adminEntrance = true;
		SetConsoleTextAttribute(hConsole, 7);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		if (!logIsTrue) cout << "\nНекорректный логин\n";
		if (!passIsTrue) cout << "\nНекорректный пароль\n";
		SetConsoleTextAttribute(hConsole, 7);
	}

}

int Admin::CheckEmpty()
{
	adminData.open(path, ios::in | ios::app);

	char s;
	int count = 0;
	while (adminData.get(s))
	{
		count++;
		cout << s;
	}
	cout << "count : " << count << endl;

	adminData.close();
	return count;
}

bool Admin::getAdminEntrance()
{
	return adminEntrance;
}


void Admin::ChangeProfile()
{
		adminData.open(path, ios::in | ios::app);

		cout << "1 - Замена логина\n";

		string str,current;
		while (getline(adminData, str))
		{
			current = str;
			break;
		}

		current = Decrypter(current);

		cout << "Текущий логин админа - " << current << endl;

		while (getline(adminData, str))
		{
			current = str;

			break;
		}

		current = Decrypter(current);

		cout << "Текущий пароль админа - " << current << endl;

		adminData.close();
}

void User::ChangeProfile()
{
	userLogs.open(pathLog, ios::app | ios::in);
	userPass.open(pathPass, ios::app | ios::in);


	cout << "Все логины пользователей по порядку\n";
	string strL, strP;
	while (getline(userLogs,strL))
	{
		strL = Decrypter(strL);
		cout << strL << endl;
	}

	cout << "Все пароли пользователей по порядку\n";
	string strL, strP;
	while (getline(userPass, strP))
	{
		strP = Decrypter(strP);
		cout << strP << endl;
	}




	userLogs.close();
	userPass.close();
}
