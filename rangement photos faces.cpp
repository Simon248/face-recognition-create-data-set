// rangement photos faces.cpp : définit le point d'entrée pour l'application console.
/*But du programme: 
J'ai un dossier avec des photos de 391 personnes, 20 photos par personnes A PEU PRES!!! (donc +/- 3 ce qui fait qu'un simple compteur bug)
je veux creer des dossiers barbe / pas barbe ou homme / femme lunette / pas lunette pour pouvoir entrainer différent réseau de neuronnes
l'idée est de créer un dossier par personne et d'y joindre un fichier txt au format csv decrivant la personne selon ces critères
chaque photo a un nom du type : identifiant_de_la_personne.i (avec i itération sur les 20 photos)
bien sûr identifiant de la personnes n'a pas toujours la même taille
je vais donc créer des dossiers nommé nom de la personne et y copier les 20 (+/- X) photos de la personne.


*/

#include "stdafx.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <io.h>

#include <string>


using namespace std;
namespace fs = std::experimental::filesystem;



string getFileName(const string& s) {

	char sep = '/';
	
#ifdef _WIN32
	sep = '\\';
#endif


	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {

		



		return(s.substr(i + 1, s.length() - i));
	}

	return("");
}

int test_dossier(const char* path)
{
	int test = _access(path, 00);
	return test;

}



int main()
{

	std::string folder_path = "E:\\projet face recogn\\images faces";
	string filePath;
	string fileName;
	size_t pos;
	string fileID;
	string Dir;
	for (auto & p : fs::directory_iterator(folder_path))
	{
		filePath = p.path().string();
		fileName = getFileName(filePath);

		pos = fileName.find(".");
		fileID = fileName.substr(0, pos);

		Dir = folder_path + "\\" + fileID;

		int test =test_dossier(Dir.c_str());
		if (test == -1)
		{
			fs::create_directory(Dir);

		}
		else if (test == 0)
		{
			
		}

		else cout << "error" << endl;

		string newPath;
		if(fileName.substr(pos + 1)!="jpg")
		{
		newPath= Dir + "\\" + fileID + "-" + fileName.substr(pos + 1);
		}
		else newPath = Dir + "\\" + fileID +".jpg";

	fs:copy(p, newPath);







	}

	return 0;
}

/*


std::string folder_path = "E:\\projet face recogn\\images faces";

string currentpath;

vector<fs::path>listephoto;


int photoCount = 0;
int Dir = 0;
string newDir ;
string newPath;

string filePath;
string fileName;

for (auto & p : fs::directory_iterator(folder_path))
{
filePath = p.path;
fileName =  getFileName(filePath);

if (photoCount == 20 || (photoCount == 0 && Dir == 0))
{

photoCount = 0;
newDir = folder_path + "//" + to_string(Dir);
fs::create_directory(newDir);
Dir++;
}
//listephoto.push_back(p);
newPath = to_string(photoCount);
newPath = newDir + "\\" + newPath+".jpg";
fs:copy(p,newPath);


photoCount++;


}


getchar();





return 0;

*/