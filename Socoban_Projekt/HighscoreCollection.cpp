#include "HighscoreCollection.h"
#include <fstream>

using namespace std;

HighscoreCollection::HighscoreCollection()
{
	Highscore temp[10][10];
	
	//FILE *file = fopen("highscores.dat", "rb");
	//fclose(file);
	//if (file == NULL) //plik nie istnieje - stworzenie nowego
	//{
	//	/*for (int x = 0; x < 10; ++x)
	//	{
	//		for (int y = 0; y < 10; ++y)
	//		{
	//			temp[x][y].PlayerName = "AAA";
	//			temp[x][y].Steps = 10000;
	//			temp[x][y].Time = "99:99:99";
	//		}
	//	}*/

	//	file = fopen("highscores.dat", "wb");
	//	fwrite(temp, sizeof(Highscore), sizeof(temp)/sizeof(Highscore), file);
	//}
	//else
	{
		//fread(temp, sizeof(temp)/sizeof(Highscore), sizeof(Highscore), file);
		fstream myFile;
		myFile.open ("highscores.dat", ios::in | ios::out | ios::binary);
		myFile.read((char*)temp, sizeof(temp));
		myFile.close();
	}
	
	//fclose(file);
}

HighscoreCollection::~HighscoreCollection()
{
}