#include "Admin.h"
#include "News.h"
#include "User.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <set>
using namespace std;
Admin::Admin()
{
	username = "";
	password = "";
}
Admin::Admin(string username, string password)
{
	this->username = username;
	this->password = password;
}
int Admin::getIndex(vector<News> allNews, string title)
{
	auto it = allNews.begin();
	int index = 0;
	while (it != allNews.end())
	{
		if (it->title == title)
		{
			return index;
		}
		else
		{
			it++;
			index++;
		}
	}
	return -1;
}

void Admin::postNews(vector<News>& allNews)
{
	char answer = {};
	do {
		News newNews;
		cout << "Enter the title: ";
		getline(cin >> ws , newNews.title);
		cout << "Enter the category: " << endl;
		for (int i = 0; i < allNews.size(); i++)
		{
			categories.insert(allNews.at(i).category);
		}
		auto it = categories.begin();
		while(it!= categories.end())
		{
			cout << (*it) << endl;
			it++;
		}
		cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
		getline(cin >> ws, newNews.category);
		bool flag = false;
		while (it != categories.end()) {
			if (newNews.category == *it)
			{
				flag = true;
			}
			it++;
		}
		int x;
		if (!flag)
		{
			cout << "You entered a category that doesn't exist, \nPlease press 1 to add a category or 0 to post anther news\n";
			cin >> x;
			if (x == 1)
			{
				addCategory(newNews.category);
			}
			else
			{
				cout << "Post another news\n";
				cout << "---------------------------\n";
				postNews(allNews);
			}
		}
		cout << "Enter the description\n";
		getline(cin >>ws , newNews.description);
		cout << "Enter the date (dd mm yyyy):\n";
		cin >> newNews.date.day >> newNews.date.month >> newNews.date.year;
		while(newNews.date.day > 31 || newNews.date.month > 12 || newNews.date.year > 2023) {
			cout << "Invalid date!" << endl <<"Enter the date again : "<<endl;
			cin >> newNews.date.day >> newNews.date.month >> newNews.date.year;
		}
		allNews.push_back(newNews);
		cout << "If you wnat to post again press y else press n ??\n";
		cin >> answer;
		} while (answer == 'y' || answer == 'Y');
}
void Admin::updateNews(vector<News>& allNews, string title)
{
	char answer = {};
	int index = getIndex(allNews, title);
	if (index == -1)
		cout << "The News which you want to be updated does not exist\n";
	else
	{
		int choice;
		do
		{
			cout << "Choose an option to update\n ";
			cout << "================================\n";
			cout << "1- Title \n2- Category\n3- Description\n4- Date\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "Enter New title\n";
				getline(cin >> ws, allNews.at(index).title);
				cout << "\nThe News title is updated successfully\n";
				break;
			case 2:
				cout << "Enter New category\n";
				getline(cin >> ws, allNews.at(index).category);
				cout << "\nThe News category is updated successfully\n";
				break;
			case 3:
				cout << "Enter New description\n";
				getline(cin >> ws, allNews.at(index).description);
				cout << "\nThe News description is updated successfully\n";
				break;
			case 4:
				cout << "Enter New date (dd mm yyyy)\n";
				cin >> allNews.at(index).date.day >> allNews.at(index).date.month >> allNews.at(index).date.year;
				cout << "\nThe News date is updated successfully\n";
				break;
			default:
				cout << "\nInvalid number\n";
				answer = 'y';
				continue;
			}
			cout << "If you wnat to update again press y else press n \n\n??";
			cin >> answer;
		} while (answer == 'y' || answer == 'Y');
	}
}

void Admin::removeNews(vector<News>& allNews, string title)
{
	int index = getIndex(allNews, title);
	if (index == -1)
		cout << "The News which you want to be delete does not exist\n";
	else
	{
		allNews.erase(allNews.begin() + index);
		cout << "\nThe News is removed successfully\n";
	}
}
void Admin::addCategory(string cat) {
	char choice;
	do 
	{
		categories.insert(cat);
		cout << "Added successfully!" << endl;
		cout << "Do you want to add another one (press y to post another or n to end)? " << endl;
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}
void Admin::avgRate(vector<News> allNews) {
	string title;
	bool isExist = false;
	cout << "Enter the title :" << endl;
	cin >> title;
	auto it = allNews.begin();
	while (it != allNews.end())
	{
		if (it->title == title) {
			cout << it->rate<<endl;
			isExist = true;
			break;
		}
		it++;
	}
	if (!isExist)
	{
		cout << "This title doesn't exist\n\n";
	}
}