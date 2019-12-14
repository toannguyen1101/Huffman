#include"Openfolder.h"

void getfilepathinfolder(const char* folder, string filepath[], int& numoffile)
{
	DIR* d;
	struct dirent* dir;
	
	//Lay duong dan thu muc
	d = opendir(folder);
	
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			numoffile++;
			cout << dir->d_name << endl;

			if (numoffile >= 3)
			{
				filepath[numoffile - 3] = dir->d_name;//Gan vao filepath luu nhung file can thiet
			}

		}
		closedir(d);
	}
	
	numoffile -= 2;
	
	cout << endl;

}