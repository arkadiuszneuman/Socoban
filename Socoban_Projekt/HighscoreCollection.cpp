#include "HighscoreCollection.h"
#include <fstream>
#include <sstream>

using namespace std;

HighscoreCollection::HighscoreCollection()
{
	if (!IsHighscoreExists())
	{
		SaveHighscore();
	}
	else
	{
		LoadHighscore();
	}
}

bool HighscoreCollection::IsHighscoreExists()
{
	ifstream ifile("highscores.dat");
	return ifile;
}

void HighscoreCollection::SaveHighscore()
{
	fstream myFile("highscores.dat", ios::out | ios::binary);
	myFile.write((char*)&highscores, sizeof(highscores));
	myFile.close();
}

void HighscoreCollection::LoadHighscore()
{
	fstream myFile("highscores.dat", ios::in | ios::binary);
	myFile.read((char*)&highscores, sizeof(highscores));
	myFile.close();
}

bool HighscoreCollection::IsQualified(int mapNo, int steps, std::string time)
{
	if (highscores[mapNo][9].Steps > steps)
	{
		return true;
	}
	else if (highscores[mapNo][9].Steps == steps)
	{
		if (IsFaster(time, highscores[mapNo][9].Time))
		{
			return true;
		}
	}

	return false;
}

void HighscoreCollection::AddHighscore(int mapNo, std::string playerName, std::string time, int steps)
{
	int i;
	for (i = 9; i >= 0; --i)
	{
		if (highscores[mapNo][i].Steps > steps)
		{
			continue;
		}
		else if (highscores[mapNo][i].Steps == steps)
		{
			if (IsFaster(time, highscores[mapNo][i].Time))
			{
				continue;
			}
		}

		break;
	}

	++i;
	for (int x = 9; x > i; --x)
	{
		highscores[mapNo][x] = highscores[mapNo][x - 1];
	}

	highscores[mapNo][i].PlayerName = playerName;
	highscores[mapNo][i].Time = time;
	highscores[mapNo][i].Steps = steps;

	SaveHighscore();
}

bool HighscoreCollection::IsFaster(const string &time1, const string &time2)
{
	vector<string> splited1 = SplitString(time1, ':');
	vector<string> splited2 = SplitString(time2, ':');

	int time1h, time1m, time1s, time2h, time2m, time2s;

	istringstream iss1(splited1[0]);
	iss1 >> time1h;
	istringstream iss2(splited1[1]);
	iss2 >> time1m;
	istringstream iss3(splited1[2]);
	iss3 >> time1s;
	istringstream iss4(splited2[0]);
	iss4 >> time2h;
	istringstream iss5(splited2[1]);
	iss5 >> time2m;
	istringstream iss6(splited2[2]);
	iss6 >> time2s;

	if (time1h < time2h)
	{
		return true;
	}
	else if (time1h == time2h)
	{
		if (time1m < time2m)
		{
			return true;
		}
		else if (time1m == time2m)
		{
			if (time1s < time2s)
			{
				return true;
			}
		}
	}

	return false;
}

vector<string> HighscoreCollection::SplitString(const string &s, char delim) 
{
	std::vector<string> elems;

	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}

	return elems;
}
