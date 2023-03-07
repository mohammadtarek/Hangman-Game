#include "hangman.h"
#include <vector>
#include<string>
#include <iostream>
#include <fstream>
using namespace std;

hangman::hangman(){}
fstream Scores;
void hangman::category()
{
	fstream file;
	word temp;
	cout << "Enter category?" << endl;
	cout << "1-Movies" << endl;
	cout << "2-Songs" << endl;
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		file.open("m.txt");
		break;

	case 2:
		file.open("s.txt");
		break;
	default:
		break;
	}
	while (true)
	{
		getline(file, temp.name);
		if (temp.name == "pause")
			break;
		getline(file, temp.meaning);
		data.push_back(temp);
	}
	file.close();
}

bool hangman::checkwin(string s) {

	if (s == cword)
		return true;
	else
		return false;
}

bool hangman::checkchar(char s) {
	bool flag = false;
	for (int i = 0; i < cword.size(); i++) {
		if (s ==wtmp[i]) {
			hiden_word[i] = s;
			wtmp[i] = '0';
			flag = true;
		}
	}
	return flag;
}


void hangman::random_word()
{
	numofrand = rand() % data.size();
	cword = data[numofrand].name;
	wtmp = cword;
	cmean = data[numofrand].meaning;
	hiden_word = cword;
	for (int i = 0; i < cword.size(); i++)
	{
		hiden_word[i] = '#';
		if (cword[i] == ' ')
			hiden_word[i] = ' ';

	}
	wtry = 0;
}

void hangman::game_continue()
{
	Scores.open("Scores.txt", ios::app);
	cout << "please enter player's name: ";
	cin >> n.name;
	string ans;
	bool resume = true;
	category();
	random_word();
	while (resume)
	{
		cout << cmean << endl;
		cout << "Enter Word :";
		
		getline(cin,ans);
		if (wtry < 3)
		{
			
			if (checkwin(ans))
			{
				n.score += 10;
				cout << "right answer !" << endl;
				random_word();
			}
			else
			{
				cout << "try again" << endl;
				wtry++;
				
				
			}
		}
		else if (wtry >= 3 && wtry < 6)
		{
			cout << hiden_word << endl;
			cout << "enter a character : " << endl;
			cin >> ans;
			while (ans.length() > 1)
			{	
				cout << "you should enter only one charcter"<<endl;
				cout << "enter a character : " << endl;
				cin >> ans;
				
			}

			if (checkchar(ans[0]))
			{
				if (checkwin(hiden_word))
				{
					n.score += 10;
					cout << "right answer!" << endl;
					random_word();
				}
			}
			else
			{
				wtry++;
				cout << "try again" << endl;
				continue;
			}
		}
		else
		{
			cout << "GAME OVER !" << endl;
			cout << "Your score is " << n.score << endl;
			file_Score();
			resume = false;
		}
	}
}

void hangman::file_Score() {

	Scores << "Name\t\tScore\n__________________________________________________________________________________________________\n";

	Scores << n.name << "\t\t"
		<< n.score << endl
		<< "__________________________________________________________________________________________________" << endl;
}