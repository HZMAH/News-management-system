#pragma once
#include <vector>
#include <list>
#include <iostream>
using namespace std;
struct Date {
	int day, month, year;
};
struct Comment {
	string username;
	string commentContent;
};
class News
{
public:
	News();
	string title;
	string description;
	string category;
	Date date;
	list<Comment> comments;
	int rate;
	int spamCount;
	int numOfRatedUsers;
	list <string> spamUserNames;
};