#include"Decompression.h"

string dectobin(int data)
{
	//Do mac dinh la su dung 8 bit nen su dung mang 8 ky tu
	int a[8], n = 0;
	
	string bin;
	
	//Tinh mang nhi phan
	for (int i = 0; data > 0; i++)
	{
		a[i] = data % 2;
		data = data / 2;
		n++;
	}
	//Gan cac so nhi phan vao string bin
	for (int i = n - 1; i >= 0; i--)
		bin += char(a[i] + 48);
	//Neu mang nhi phan co do dai nho hon 8 thi them vao dau cac phan tu 0 cho du 8
	if (n < 8)
		bin.insert(0, 8 - n, '0');
	return bin;
}

void decompression(string filepath, string outfile, string filename)
{

	int size = 0;

	node** temp = new node * [256];
	//Tao duong dan va file xuat ra sau khi giai nen
	outfile += '/';
	outfile += filename;

	ifstream fileinput(filepath, ios::binary);
	ofstream fileoutput(outfile, ios::binary);

	//Doc so ky tu 
	int num;
	fileinput >> num;

	int count = 0;
	
	//Doc cac ky tu va tan so
	for (int i = 0; i < num; i++)
	{
		int data;
		int freq;
		fileinput >> data;
		fileinput >> freq;
		if (data < 0)
			data += 256;
		temp[size] = createnode(char(data), freq);
		size++;
	}

	//Tim xem trong mang co ky tu $ hay khong
	int freq$ = 0;
	for (int i = 0; i < size; i++)
		if (temp[i]->data == '$')
			freq$ = temp[i]->freq;

	//Xay dung cay huffman
	board** tree = huffmantree(temp, size);
	


	string bin;
	string out;
	int du;

	while (!fileinput.eof())
	{

		char* data = new char[1024 * 1024 * 32];
		fileinput.read(data, 1024 * 1024 * 32);
	
		if (fileinput.gcount() < 1024 * 1024 * 32)
		{
			du = data[fileinput.gcount() - 1] - 48;  //Do phan tu cuoi la so luong phan tui con du trong qua trinh nen lay vao de xoa bot cac bit 0
		}
		//Doc tu phan tu 1 vi luc ghi ra co phan tu xuong dong
		for (int i = 1; i < fileinput.gcount(); i++)
		{
			if (fileinput.gcount() < 1024 * 1024 * 32)//Neu so phan tu lon hon so phan tu doc vao thi phan tu tien hanh xoa cac bit 0 du o ky tu cuoi
			{
				//Tien hanh gan cai ky tu doc tu file xong chuyen ve nhi phan
				if (i < fileinput.gcount() - 1)
				{
					if (int(data[i]) < 0)
						bin += dectobin(int(data[i]) + 256);
					else
						bin += dectobin(int(data[i]));
					if (i == fileinput.gcount() - 2)
					{
						bin.erase(bin.length() - du, du); //Xoa cac bit 0 du
					}

				}
			}
			else
			{
				if (int(data[i]) < 0)
					bin += dectobin(int(data[i]) + 256);
				else
					bin += dectobin(int(data[i]));
			}
			if (bin.length() > 5000)
			{
				int check = 0;
				int count = 0;
				node* p = temp[0];
				for (int i = 0; i < 5000; i++)
				{
					//Duyet cay de doc ky tu
					if (bin[i] == '0' && p->left != NULL)
						p = p->left;
					else if (bin[i] == '1' && p->right != NULL)
						p = p->right;
					else
						p = temp[0];

					//In ra ky tu, neu co ky tu $ thi xet xem ky tu do co bang tan so da luu luc dau khong
					if (p != NULL)
					{
						if (p->data != '$')
						{
							out += p->data;
							check = count;
							p = temp[0];
						}
						else if (p->freq == freq$)
						{
							out += p->data;
							check = count;
							p = temp[0];
						}
					}
					count++;
				}
				bin.erase(0, check);

			}

			if (out.length() > 100)
			{
				fileoutput << out;
				out.erase();

			}
		}
	}

	//In ra chuoi ky tu
	if (out.length() > 0)
	{
		fileoutput << out;
		out.erase();
	}

	//Tuong tu nhu tren, nhung de xu li nhung phan tu trong bin con du
	if (bin.length() > 0)
	{
		int check = 0;
		int count = 0;
		node* p = temp[0];
		for (int i = 0; i < bin.length(); i++)
		{
			if (bin[i] == '0' && p->left != NULL)
				p = p->left;
			else if (bin[i] == '1' && p->right != NULL)
				p = p->right;
			else
				p = temp[0];

			if (p != NULL)
			{
				if (p->data != '$')
				{
					out += p->data;
					check = count;
					p = temp[0];
				}
				else if (p->freq == freq$)
				{
					out += p->data;
					check = count;
					p = temp[0];
				}
			}


			count++;
		}
		bin.erase(0, bin.length());
		fileoutput << out;
	}

	//Dong file
	fileinput.close();
	fileoutput.close();

}