#include"compress.h"

void compression(string outfolder, string filecompress, string filepath, string* tmp, int size, node* n)
{
	//Tao ten file va duong dan de xuat ra sau khi nen
	string outfile = outfolder;
	outfile += "/compress_";
	outfile += filepath;
	
	ifstream fileinput(filecompress, ios::binary);
	ofstream fileoutput(outfile, ios::binary);
	
	//In so luong ky tu ra file
	fileoutput << size << endl;
	
	//In bang tan so va ky tu
	for (int i = 0; i < size - 1; i++)
		fileoutput << int(n[i].data) << " " << n[i].freq << " ";
	fileoutput << int(n[size - 1].data) << " " << n[size - 1].freq << endl;
	
	string bin;//Mang luu ma nhi phan
	string out;//Mang luu ky tu sau khi chuyen ve nhi phan

	while (!fileinput.eof())
	{

		char* data = new char[1024 * 1024 * 32];
		fileinput.read(data, 1024 * 1024 * 32);
		
		for (int i = 0; i < fileinput.gcount(); i++)
		{

			if (int(data[i]) < 0)
				bin += tmp[int(data[i]) + 256];				//Gan cai ma nhi phan cac ky tu vao bin
			else
				bin += tmp[int(data[i])];

			if (bin.length() >= 40000)
			{
				for (int i = 0; i < 40000; i += 8)
				{
					//Chuyen 8 bit ve 1 ky tu
					char c = char((bin[i] - 48) * 128 + (bin[i + 1] - 48) * 64 + (bin[i + 2] - 48) * 32 + (bin[i + 3] - 48) * 16 + (bin[i + 4] - 48) * 8 + (bin[i + 5] - 48) * 4 + (bin[i + 6] - 48) * 2 + (bin[i + 7] - 48));
					out += c; //Gan ky tu sau khi cat 8bit ve 1 ky tu gan vao out
				}
				bin.erase(0, 40000);
			}
		}

		if (out.length() > 1000)
		{
			fileoutput << out;
			out.erase();//Xoa chuoi sau khi in ra
		}
	}


	if (bin.length() > 0)
	{

		for (int i = 0; i < bin.length(); i += 8)
		{

			char c = char((bin[i] - 48) * 128 + (bin[i + 1] - 48) * 64 + (bin[i + 2] - 48) * 32 + (bin[i + 3] - 48) * 16 + (bin[i + 4] - 48) * 8 + (bin[i + 5] - 48) * 4 + (bin[i + 6] - 48) * 2 + (bin[i + 7] - 48));
			out += c;
			if (i + 16 >= bin.length())
				bin.erase(0, i + 8);
		}

		fileoutput << out;

		//Do su dung 8 bit nen se co nhung bit bi du
		int du = 8 - bin.length();

		if (bin.length() < 8)
		{
			//Gan nhung bit con thieu bang bit 0 de du 8 bit
			for (int i = bin.length(); i < 8; i++)
				bin += "0";
			char dec = char((bin[0] - 48) * 128 + (bin[1] - 48) * 64 + (bin[2] - 48) * 32 + (bin[3] - 48) * 16 + (bin[4] - 48) * 8 + (bin[5] - 48) * 4 + (bin[6] - 48) * 2 + (bin[7] - 48));
		}
		fileoutput << dec << du;//In phan du ra file
	}

	fileinput.close();
	fileoutput.close();

}

