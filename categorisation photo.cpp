// categorisation photo.cpp : définit le point d'entrée pour l'application console.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include <filesystem>



#include <stdio.h>
#include <io.h>

#include <string>



#define NUM_IMGS 392

namespace fs = std::experimental::filesystem;


using namespace cv;
using namespace std;

int test_dossier(const char* path)
{
	int test = _access(path, 00);
	return test;

}


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


int main()
{
	string choix;
	cout << "vouler vous catégoriser ou créer un set?" << endl;
	cout << "(cat /set)" << endl;

	cin >> choix;
	if (strcmp(choix.c_str(), "cat") == 0)
	{

		std::string path = "E:\\projet face recogn\\images faces";

		/*
		cv:Mat image;
		string path_image;


		string lunette;
		string sex;
		string barbe;

		for (int A=0;A==392;A++)
		{

		image = imread(path_image, CV_LOAD_IMAGE_COLOR);

		cout << "SEX ?" << endl;
		cin >> sex;

		cout << "LUNETTE ?" << endl;
		cin >> lunette;

		cout << "BARBE ?" << endl;
		cin >> barbe;

		}
		getchar();


		*/



		string lunette;
		string sex;
		string barbe;

		string path_image;

		Mat image;

		std::string folder_path = "E:\\projet face recogn\\images faces";
		string ImagePath;
		for (auto & p : fs::directory_iterator(folder_path))
		{

			ImagePath = (folder_path + "\\" + getFileName(p.path().string()) + "\\" + getFileName(p.path().string() + "-1.jpg"));



			// load image
			image = imread(ImagePath, CV_LOAD_IMAGE_COLOR);


			if (image.empty())
			{
				cout << "!!! failed to load" << path_image << endl;
				continue;
			}


			namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
			imshow("Display window", image);
			waitKey(1);

			cout << "SEX ?" << endl;
			cout << "1==>Homme   0==>Femme" << endl;
			cin >> sex;

			cout << "LUNETTE ?" << endl;
			cout << "1==>oui   0==>non" << endl;
			cin >> lunette;

			if (sex == "1")
			{
				cout << "BARBE ?" << endl;
				cout << "1==>oui   0==>non" << endl;
				cin >> barbe;
			}
			else barbe = "0";
			/*

			Cette partie créait un fichier .cvs cat par dossier. Mais ca fait plein de fichier qui s'appele cat.txt et qui flingue les copier-coller. on pourrait les nommer avec le nom du dossier mais ces fichiers ne servent a rien...
			ofstream txtfile(p.path().string() + "\\" + "cat.txt");

			if (txtfile.is_open())
			{
			txtfile << sex + "," + lunette + "," + barbe + "," << std::endl;

			txtfile.close();
			}
			else cout << "Unable to open file";
			*/



			cvDestroyWindow("Display window");


			ofstream maintxtfile(folder_path + "\\" + "maincat.txt", ios::app);
			if (maintxtfile.is_open())
			{
				maintxtfile << p.path().string() + "," + sex + "," + lunette + "," + barbe + "," << std::endl;

				maintxtfile.close();
			}
			else cout << "Unable to open file";

		}



	}
	else
	{
		int crit;
		cout << "sur quel critère créer un set?" << endl;
		cout << "(1 ==> sexe   //  2 ==> lunette  //  3 ==> barbe)" << endl;

		cin >> crit;

		string setname;
		cout << "comment voulez vous appeller votre set?" << endl;
		cin >> setname;
		

		int tauxValidationSet;
		cout << "Quel poucentage pour le validation test? " << endl;
		cin >> tauxValidationSet;
		

		std::string folder_path = "E:\\projet face recogn\\images faces";
		//fs::create_directory(folder_path + "\\data");
		//fs::create_directory(folder_path + "\\data\\" + setname + "\\train");
		//fs::create_directory(folder_path + "\\data\\" + setname + "\\valid");

		cout << folder_path + "\\data\\" + setname + "\\train" + "\\1" << endl;
		fs::create_directory(folder_path + "\\data");
		fs::create_directory(folder_path + "\\data\\" + setname);
		fs::create_directory(folder_path + "\\data\\" + setname + "\\train");
		fs::create_directory(folder_path + "\\data\\" + setname + "\\valid");

		fs::create_directory(folder_path + "\\data\\" + setname + "\\train" + "\\1");
		fs::create_directory(folder_path + "\\data\\"+setname +"\\train"+ "\\0");

		fs::create_directory(folder_path + "\\data\\" + setname + "\\valid" + "\\1");
		fs::create_directory(folder_path + "\\data\\" + setname + "\\valid" + "\\0");
		




		const int L = 391;
		const int C = 4;
		string tableau[L][C];

		// on récupere le tablea du fichier csv
		ifstream infile(folder_path + "\\maincat.txt");


		string line="init";
		string val;
		int pos;
		int pos_mem = 0;
		int i = 0;

		if (infile.is_open())
		{
			
			while (line!="")
			{

				getline(infile, line);
				if (line == "")
				{
					break;
				}
				pos = pos_mem = 0;
				for (int j = 0; j<4; j++)
				{
					pos = line.find(",", pos_mem);
					tableau[i][j] = line.substr(pos_mem, pos - pos_mem);
					pos_mem = pos + 1;
				}
				i++;
			}
			


			/*
			for (int i = 0; i < 391; i++)  //a remplacer par while (getline return != "")
			{
				getline(infile, line);
				if (line == "")
				{
					break;
				}
				pos = pos_mem = 0;
				for (int j = 0; j<4; j++)
				{
					pos = line.find(",", pos_mem);
					tableau[i][j] = line.substr(pos_mem, pos - pos_mem);
					pos_mem = pos + 1;
				}



			}

			*/



		}

		//on copie colle le contenu des dossiers dans les dossiers 1 ou 0
		int cat_one = 0;
		int cat_zero = 0;

		for (int l = 0; l < i; l++)
		{
			if (stoi(tableau[l][crit]) == 1)
			{
				for (auto & p : fs::directory_iterator(tableau[l][0]))
				{
				fs:copy(p, folder_path + "\\data\\" + setname + "\\train" + "\\1");
					cat_one++;
				}
			}

			else
				for (auto & p : fs::directory_iterator(tableau[l][0]))
				{
					fs::copy(p, folder_path + "\\data\\" + setname + "\\train" + "\\0");
					cat_zero++;
				}
			cout << l << endl;
		}




		srand(time(NULL));
		vector<string> vect1;
		for (auto & p : fs::directory_iterator(folder_path + "\\data\\" + setname + "\\train" + "\\1"))
		{
			vect1.push_back(p.path().string());
		}

		int l1 = vect1.size()-1;




		for (int filecount=0;filecount<tauxValidationSet*0.01*cat_one;filecount++)
		{
				int r; //random entre 0 et l
			
				double R = ((rand() % 100 + 1)*0.01);
				r = R * l1;
				cout << r << endl;
				cout << l1 << endl;
				fs::copy(vect1[r], folder_path + "\\data\\" + setname + "\\valid" + "\\1");
				fs::remove(vect1[r]);
				vect1.erase(vect1.begin()+r);
				l1 = l1 - 1;
		}

		int fileCount = 0;
		vector<string> vect0;
		for (auto & p : fs::directory_iterator(folder_path + "\\data\\" + setname + "\\train" + "\\0"))
		{
			vect0.push_back(p.path().string());
		}

		int l2 = vect0.size()-1;

		for (int filecount = 0; filecount<tauxValidationSet*0.01*cat_zero; filecount++)
		{
			int r; //random entre 0 et l
		
			double R = ((rand() % 100 + 1) *0.01);
			r = R * l2;
			cout << r << endl;
			cout << l2 << endl;
			fs::copy(vect0[r], folder_path + "\\data\\" + setname + "\\valid" + "\\0");
			fs::remove(vect0[r]);
			vect0.erase(vect0.begin() + r);
			l2 = l2 - 1;
		}




		/*
		for (auto & p : fs::directory_iterator(folder_path + "\\data\\" + setname + "\\train" + "\\0"))
		{

			if (fileCount < (tauxValidationSet*0.01*cat_zero))
			{
				fs::copy(p, folder_path + "\\data\\" + setname + "\\valid" + "\\0");
				fs::remove(p);
				fileCount++;
			}
		}
		*/
		getchar();







	




	}


	return 0;
}

/*



for (int i = 0; i < NUM_IMGS; i++)
{

path_image = path + "\\" + to_string(i) + "\\" + "1.jpg";

// load image
image = imread(path_image, CV_LOAD_IMAGE_COLOR);

if (image.empty())
{
cout << "!!! failed to load" << path_image << endl;
continue;
}
namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
imshow("Display window", image);
waitKey(3000);

cout << "SEX ?" << endl;
cin >> sex;

cout << "LUNETTE ?" << endl;
cin >> lunette;

cout << "BARBE ?" << endl;
cin >> barbe;


ofstream txtfile (path + "\\" + to_string(i) + "\\" +"cat.txt");

if (txtfile.is_open())
{
txtfile << sex + "," + lunette + "," + barbe + "," << std::endl;

txtfile.close();
}
else cout << "Unable to open file";




cvDestroyWindow("Display window");

}


return 0;
}

*/

