#include <iostream>
#include "News.h"
#include "User.h"
#include "Admin.h"
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

fstream newsFile;
fstream usersFile;
unordered_map<string, User> myMap;

Admin admin("admin", "admin");

void welcomPage();
void readNewsFromFile();
void readUsersFromFile();
void signUp();
void signIn();
void adminMenu();
void userOptions(string username);
vector<News> allNews;
int main()
{  
	readNewsFromFile();
	readUsersFromFile();
	welcomPage();
	return 0;
}
void welcomPage()
{
	cout << "====================================================\n";
	cout << "	 Welcom to News Management System		     \n";
	cout << "====================================================\n";
	cout << "1-Sign up\n2-Sign in\n3-Exit\n\n";
	int choice;
	cin >> choice;
	string username, password;
	if (choice == 1)
	{
		system("cls");
		signUp();
	}
	else if (choice == 2)
	{
		system("cls");
		signIn();
	}
	else if (choice == 3)
	{
			system("cls");
			newsFile.open("newsFile.txt", ios::out);

			for(auto &news : allNews)
			{
				newsFile << news.title << endl;
				newsFile << news.category << endl;
				newsFile << news.description << endl;
				newsFile << news.date.day << " " << news.date.month << " " << news.date.year << endl;
				newsFile << news.spamCount << endl;
				newsFile << news.rate << endl;
				for (const Comment& c : news.comments)
			{
					newsFile << c.username << endl;
					newsFile << c.commentContent << endl;
			}
					newsFile << "END" << endl;
			}
			newsFile.close();
			exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Invalid number\n";
		welcomPage();
	}
	system("pause");
}
void signUp()
{
	string username, password;
	cout << "Username (No spaces): ";
	getline(cin >> ws, username);
	cout << "Password (No spaces): ";
	getline(cin >> ws, password);
	User userTemp(username, password);
	if (myMap.find(username) != myMap.end())
	{
		cout << "This user is existed already! \n";
		cout << ":::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "Please enter another username: \n";
		signUp();
	}
	else
	{
		usersFile.open("usersFile.txt", ios::app);
		usersFile << username << " " << password << endl;
		usersFile.close();
		myMap[username] = userTemp;
		userOptions(username);
	}
}

void signIn()
{
	string username, password;
	cout << "=======Sign in page=======\n";
	cout << "username: "; cin >> username;
	cout << "password: "; cin >> password;
	if (username == admin.username && password == admin.password)
	{
		system("cls");
		adminMenu();
	}
	else
	{
		if (myMap.find(username) != myMap.end() && password == myMap[username].password)
		{
			system("cls");
			userOptions(username);
		}
		else
		{
			cout << "Invalid login\n";
			cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
			welcomPage();
			system("pause");
		}
	}
}
void adminMenu()
{
	re:
		int choice;
		string category;
		cout << "====== Admin menus ======\n";
		cout << "Choose operation you want to do.\n";
		cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "1- Post news\n2- Update news\n3- Remove news\n4- Add category\n5- Display average rate\n6- Sign out\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			cout << "======== Post News ========\n";
			admin.postNews(allNews);
			system("cls");
			goto re;
		}
		case 2:
		{
			system("cls");
			cout << "========== Update News =========\n";
			cout << "Enter the title of the news you want to update\n";
			string title; cin >> title;
			admin.updateNews(allNews, title);
			system("cls");
			goto re;
		}
		case 3:
		{
			system("cls");
			cout << "======= Remove News ========\n";
			cout << "Enter the title of the news you want to remove\n";
			string title; cin >> title;
			admin.removeNews(allNews, title);
			system("cls");
			goto re;
		}
		case 4:
		{
			system("cls");
			cout<<"======= Add Category ========\n";
			cout << "Enter the category: " << endl;
			cin >> category;
			admin.addCategory(category);
			goto re;
		}
		case 5:
		{
			system("cls");
			cout << "===== Average Rate =====\n";
			admin.avgRate(allNews);
			goto re;
		}
		case 6:
		{
			system("cls");
			welcomPage();
			goto re;
		}
		default:
			cout << "Invalid number\n";
			cout << "\n\n";
			goto re;
		}
	
}
void userOptions(string username)
{
		cout << "=========== User page ============\n";
	re:
		int choice;
		cout << "Choice the operation you want\n";
		cout << "1- Show Latest News\n2- Show News by a certain category\n3- Show News by the highest rate\n4- Sign out\n";
		cin >> choice;
		if (!cin)
		{
			cin.clear();
			cin.ignore();
			cout << "Please enter a number! \n\n";
			goto re;
		}
		switch (choice)
		{
		case 1:
			system("cls");
			if (allNews.empty())
			{
				cout << "No News is posted yet.\n";
				system("pause");
				system("cls");
				goto re;
			}
			else
			{
				myMap[username].displayByDate(allNews);
				goto re;
			}
		case 2:
			system("cls");
			if (allNews.empty())
			{
				cout << "No News is posted yet.\n";
				system("pause");
				system("cls");
				goto re;
			}
			else
			{
				myMap[username].displayByCategory(allNews,admin);
				goto re;
			}
		case 3:
			
			if (allNews.empty())
			{
				cout << "No News is posted yet.\n\n";
				system("pause");
				system("cls");
				goto re;
			}
			else
			{
				myMap[username].displayByRate(allNews);
				goto re;
			}
			break;
		case 4:
			system("cls");
			welcomPage();
			break;
		default:
			cout << "Invalid number\n";
			cout << "\n\n";
			goto re;
		}
}
void readNewsFromFile()

{

	newsFile.open("newsFile.txt", ios::in);
	while (!newsFile.eof())
	{
		string line;
		News news;
		int d, m, y;
		int spamC, rt;
		getline(newsFile, line);
		if (line == "")
			break;
		news.title = line;
		getline(newsFile >> ws, line);
		news.category = line;
		getline(newsFile >> ws, line);
		news.description = line;
		newsFile >> d >> m >> y;
		news.date.day = d; news.date.month = m; news.date.year = y;
		newsFile >> spamC; news.spamCount = spamC;
		newsFile >> rt; news.rate = rt;
		while (getline(newsFile >> ws, line))
		{
			Comment comment;
			if (line == "END")
				break;
			comment.username = line;
			getline(newsFile >> ws, line);
			comment.commentContent = line;
			news.comments.push_back(comment);
		}
		allNews.push_back(news);
	}
		newsFile.close();
}
void readUsersFromFile()
{
	usersFile.open("usersFile.txt", ios::in);
	string line;
	while (getline(usersFile, line))
	{
		string key, value;
		stringstream ss(line);
		ss >> key;
		ss >> value;
		User user(key, value);
		myMap.insert(make_pair(key, user));
		myMap[key] = user;
	}
	usersFile.close();
}