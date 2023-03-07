#pragma once
#include <string>
#include <vector>
using namespace std;
class player {
public:
	string name;
	int score;
}n;
class word
{
public:
	string name;
	string meaning;
};
class hangman
{
private:
	int numofrand;
	int wtry;
	int score;
	string cword;
	string wtmp;
	string cmean;
	string hiden_word;
	vector<word> data;
public:
	hangman();
	void category();
	void random_word();
	void game_continue();
	bool checkwin(string s);
	bool checkchar(char s);
	void file_Score();
};

