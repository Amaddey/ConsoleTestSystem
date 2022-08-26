#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;


string Encrypter(string login);
string Decrypter(string login);
void AddInformation(string name, string surname, string patronymic, string path);

class Account
{
protected:
	string mLogin;
	string mPassword;

public:

	virtual void Registration() = 0;
	virtual void Authorization() = 0;
	virtual int CheckEmpty() = 0;
	virtual void ChangeProfile() = 0;
};

class User : public Account
{
protected:
	//std::string FIO;
	//bool isRegistered;
	//fstream userData("UserData.txt", ios::app | ios::out | ios::in);
	fstream userLogs;
	fstream userPass;
	string pathLog = "UserLogins.txt";
	string pathPass = "UserPasswords.txt";
	int count;
	string DecryptedLogin;
	string DecryptedPassword;
public:

	User()
	{
		count = 0;
	}

	/*User(std::string log,std::string pass)
	{
		mLogin = log;
		mPassword = pass;
	}*/

	void CheckUserLogin(string login);

	void Registration() override;

	void isRegistered();

	void Authorization() override {}

	int CheckEmpty() override
	{
		userLogs.open(pathLog, ios::in | ios::app);
		userPass.open(pathPass, ios::in | ios::app);

		char s;
		int count = 0;
		while (userLogs.get(s))
		{
			count++;
			cout << s;
		}
		cout << "count : " << count << endl;

		userLogs.close();
		return count;
	}

	void ChangeProfile();

};


class Admin : public Account
{
private:
	fstream adminData;
	fstream adminDataEncryption;
	string path = "AdminData.txt";
	string mLogin;
	string mPassword;
	bool adminEntrance;
	string DecryptedLogin;
	string DecryptedPassword;

public:
	Admin()
	{
		adminEntrance = false;
	}

	/*Admin(std::string log,std::string pass)
	{
		mLogin = log;
		mPassword = pass;
	}*/

	void ChangeProfile();

	void Registration() override;

	void Authorization() override;

	int CheckEmpty() override;

	bool getAdminEntrance();
	
};

void CheckType(Account* acc);
