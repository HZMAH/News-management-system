#pragma once
#include <string>
#include "News.h"
#include <vector>
#include <set>
using namespace std;
class Admin
{
		int getIndex(vector<News> allNews, string title);
	public:
		string username;
		string password;
		set<string> categories;
		Admin();
		Admin(string, string);
		void postNews(vector<News>& allNews);
		void updateNews(vector<News>& allNews, string title);
		void removeNews(vector<News>& allNews, string title);
		void addCategory(string cat);
		void avgRate(vector<News> allNews);
};

