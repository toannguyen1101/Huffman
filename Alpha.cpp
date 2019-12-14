#include"Alpha.h"

node** tachchuts(string filepath, int& size)
{
	node** tmp = new node * [256];
	
	int* freq = new int[256];//Mang tan so
	
	for (int i = 0; i < 256; i++)
	{
		freq[i] = 0;
	}

	ifstream fileinput(filepath, ios::binary);
	
	while (!fileinput.eof())
	{
		char* data = new char[1024 * 1024 * 8];
		fileinput.read(data, 1024 * 1024 * 8);
		
		for (int i = 0; i < fileinput.gcount(); i++)
		{
			if (int(data[i] < 0))
				freq[int(data[i]) + 256]++;				//Tinh tan so cai gia tri
			else
				freq[int(data[i])]++;
		}
	}

	fileinput.close();
	
	//Gan tan so vao node tmp
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] > 0)
		{
			tmp[size] = createnode(i, freq[i]);
			size++;
		}
	}

	return tmp;
}