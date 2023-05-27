#include "User.h"
#include "News.h"
#include <string>
#include <iterator>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

User::User()
{
	username = "";
	password = "";
}
User::User(string inputUserName, string inputPassword)
{
	username = inputUserName;
	password = inputPassword;
}
void User::addComment(News& obj)
{
	Comment userComment;
	cout << "\nEnter Your Comment\n";
	getline(cin>>ws ,userComment.commentContent);
	userComment.username = username;
	obj.comments.push_back(userComment);
	system("pause");
}
void User::rateNews(News& obj)
{
	float newRate = 0.0;
	do
	{
		cout << "\nEnter Your Rate (Please Enter A Number from  1 to 5)\n";
	re:
		cin >> newRate;
		if (!cin)
			{
				cin.clear();
				cin.ignore();
				cout << "Enter valid rate (1 : 5)\n";
				goto re;
			}
	} while (newRate > 5 || newRate < 1);
	obj.numOfRatedUsers++;
	obj.rate = ceil(((obj.rate * (obj.numOfRatedUsers - 1)) + newRate) / obj.numOfRatedUsers);
	system("pause");
}
void User::displayAllComments(News obj)
{
	if (obj.comments.empty())
	{
		cout << "NO comments is written yet\n";
	}
	else
	{
		list<Comment>::iterator it = obj.comments.begin();
		while (it != obj.comments.end())
		{
			cout << "Username: " <<it->username << endl;
			cout << "Comment: "<<it->commentContent << endl;
			cout << "--------------------------------\n";
			it++;
		}
	}
	system("pause");
}

void User::displayByDate(vector<News> &allNews)
{
	for (int i = 0; i < allNews.size(); i++)
	{
		for (int j = i; j < allNews.size(); j++)
		{
	
		if ((allNews.at(i).date.year < allNews.at(j).date.year) ||
			(allNews.at(i).date.year == allNews.at(j).date.year && allNews.at(i).date.month < allNews.at(j).date.month) ||
			(allNews.at(i).date.year == allNews.at(j).date.year && allNews.at(i).date.month == allNews.at(j).date.month && allNews.at(i).date.day < allNews.at(j).date.day))
		{
			swap(allNews.at(i), allNews.at(j));
		}
		}
	}
	for (auto& news : allNews)
	{
		displayNews(news);
		cin.get();
	}
}

void User::displayByRate(vector<News>&allNews)
{
	for (int i = 0; i < allNews.size(); i++)
	{
		for (int j = i; j < allNews.size(); j++)
		{
			if (allNews.at(i).rate < allNews.at(j).rate)
				swap(allNews.at(i), allNews.at(j));
		}
	}
	for (int i = 0; i < allNews.size(); i++)
	{
			displayNews(allNews.at(i));
	}
	system("pause");
}

void User::spamNews(News& obj)
{

	obj.spamCount++;
	obj.spamUserNames.push_back(username);
	cout << "You spammed successfully\n";
	system("pause");
}

void User::displayNews(News& obj)
{
	bool isSpam = false;
	if ((obj.rate >= 2 || obj.rate == 0) && obj.spamUserNames.empty())
	{
		system("cls");
		cout << "Title: " << obj.title << endl;
		cout << "Category: " << obj.category << endl;
		cout << "Description: \n";
		cout << obj.description << endl;
		cout << obj.date.day << "-" << obj.date.month << "-" << obj.date.year << endl;
		cout << "Rate: " << obj.rate << endl;
		cout << "Number of people who spammed: " << obj.spamCount << endl;
		int choice =0;
		do
		{ 
		cout << "********************************************"<<endl;
	re:
		cout << "Enter The Number Which You Want To Choice\n";
		cout << "1- Comment \n2- Rate \n3- Display all comments \n4- Spam \n5- Skip to next news\n";
		cin >> choice;
		if (!cin)
		{
			cin.clear();
			cin.ignore();
			cout << "Please enter a number! \n\n";
			goto re;
		}
		if (choice == 1)
				addComment((obj));
		else if (choice == 2)
				rateNews((obj));
		else if (choice == 3)
				displayAllComments((obj));
		else if (choice == 4)
				spamNews((obj));
		else if(choice == 5)
				system("cls");
		else
		{
				cout << "Invalid Numbeeer\n";
				cout << "\n\n";
				system("pause");
		}
		}while (choice != 5);
	}
	else if((obj.rate >= 2 || obj.rate == 0) && !(obj.spamUserNames.empty()))
	{
		auto it = obj.spamUserNames.begin();
		while (it != obj.spamUserNames.end())
		{
			if ((*it) == username)
			{
				isSpam = true;
				break;
			}
			it++;
		}
		if (!isSpam)
		{
			system("cls");
			cout << "Title: " << obj.title << endl;
			cout << "Category: " << obj.category << endl;
			cout << "Description: \n";
			cout << obj.description << endl;
			cout << obj.date.day << "-" << obj.date.month << "-" << obj.date.year << endl;
			cout << "Rate: " << obj.rate << endl;
			cout << "Number of people who spammed: " << obj.spamCount << endl;
			int choice = 0;
			do
			{
				cout << "********************************************" << endl;
				cout << "Enter The Number Which You Want To Choice\n";
				cout << "1- Comment \n2- Rate \n3- Display all comments \n4- Spam \n5- Skip to next news\n";
				cin >> choice;
				if (choice == 1)
					addComment((obj));
				else if (choice == 2)
					rateNews((obj));
				else if (choice == 3)
					displayAllComments((obj));
				else if (choice == 4)
					spamNews((obj));
				else if (choice == 5)
					system("cls");
				else
				{
					cout << "Invalid Numbeeer\n";
					cout << "\n\n";
					system("pause");
				}
			} while (choice != 5);
			
		}
	}
}
void User::displayByCategory(vector<News> &allNews, Admin obj)
{
	cout << "Please Enter The Category That You Want." << endl;
	cout << "----------------------------------------------\n";
	for (int i = 0; i < allNews.size(); i++)
	{
		obj.categories.insert(allNews.at(i).category);
	}
	set<string>::iterator it = obj.categories.begin();
	while (it != obj.categories.end())
	{
		cout << (*it) << endl;
		it++;
	}
	string choice;
	cin >> choice;
	bool foundcategory = false;
	vector<News>::iterator itc = allNews.begin();
	while (itc != allNews.end())
	{
		if ((*itc).category == choice)
		{
			displayNews(*itc);
			foundcategory = true;
		}
		itc++;
	}
	if (!foundcategory)
	{
		cout << "No news is posted in this category yet\n";
	}
}
