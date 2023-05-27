#include <iostream>
using namespace std;
#include "News.h"
News::News()
{
	title = "";
	description = "";
	category = "";
	date.day = 0; date.month = 0; date.year = 0;
	spamCount = 0;
	rate = 0;
}