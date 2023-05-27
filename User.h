#include "News.h"
#include "Admin.h"
#include <vector>
#include <list> 
#include <string>
using namespace std;

class User
{
public:
	string username;
	string password;
	User();
	User(string inputUserName, string inputPassword);
	void addComment(News& obj);
	void rateNews(News& obj);
	void spamNews(News& obj);
	void displayAllComments(News obj);
	void displayNews(News &obj);
	void displayByDate(vector<News>&allNews);
	void displayByCategory(vector<News>& allNews, Admin obj);
	void displayByRate(vector<News>& allNews);
};

