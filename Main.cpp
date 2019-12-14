#include"Alpha.h"
#include"Decompression.h"
#include"Openfolder.h"
#include"Compress.h"
#include<windows.h>
#include<fstream>
#include <chrono> 
using namespace std::chrono;

void main()
{
	int choose;
	do
	{
		cout << "---o0o---DO AN CTDL---o0o---" << endl;
		cout << "1. Compress file txt." << endl;
		cout << "2. Compress folder txt." << endl;
		cout << "3. Decompress file." << endl;
		cout << "4. Decompress folder." << endl;
		cout << "0. Exit." << endl;
		cout << "Choose: ";
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			cout << "--o0o--Compress file--o0o--" << endl;
			
			string infolder;
			string filepath;
			string outfolder;
			
			cin.ignore(37655, '\n');
			cout << "Nhap duong dan (ex:D/folder): ";
			getline(cin, infolder);
			cout << "Nhap ten file(ex:name.txt): ";
			getline(cin, filepath);
			cout << "Nhap duong dan luu file sau khi nen (ex:D/folder): ";
			getline(cin, outfolder);

			infolder += '/';
			infolder += filepath;
			int size = 0;
			
			cout << "Compressing....." << endl;
			
			auto start1 = high_resolution_clock::now();
			
			//Tao mang tan so va ky tu
			node** n = tachchuts(infolder, size);
			
			//Tao mang tan so rieng de in ra file
			node* tempn = new node[size];
			
			for (int i = 0; i < size; i++)
			{
				tempn[i].data = n[i]->data;
				tempn[i].freq = n[i]->freq;
			}

			//Xay cay huffman
			board** tree = huffmantree(n, size);


			//Tao mang ky tu xong gan tu mang cay vao ky tu
			string* tmp = new string[256];

			for (int i = 0; i < size; i++)
			{
				if (int(tree[i]->data) < 0)
				{
					tmp[int(tree[i]->data) + 256] = (tree[i]->bin);

				}
				else
					tmp[int(tree[i]->data)] = (tree[i]->bin);
			}
			//Nen
			compression(outfolder, infolder, filepath, tmp, size, tempn);

			auto stop1 = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop1 - start1);
		
			system("cls");
			
			cout << "Compresstion time: " << duration.count() << endl;
			cout << "DONE!!!" << endl<<endl;
			
			break;
		}
		case 2:
		{
			cout << "--o0o--Compress folder--o0o--" << endl;
			
			string filepath[200];

			string infolderstr;
			
			string outfolder;

			int numoffile = 0;
			
			cin.ignore(37655, '\n');
			
			cout << "Nhap duong dan (ex:D/folder): ";
			
			getline(cin, infolderstr);
			
			cout << "Nhap duong dan luu file sau khi nen(ex:D/folder): ";
			
			getline(cin, outfolder);

			const char* infolder = infolderstr.c_str();
			
			//Lay file tu thu muc
			getfilepathinfolder(infolder, filepath, numoffile);
			
			cout << "Compressing....." << endl;
			
			auto start = high_resolution_clock::now();
			
			//Tuong tu nhu case 1
			for (int j = 0; j < numoffile; j++)
			{

				string filecompress = infolder;
				filecompress += '/';
				filecompress += filepath[j];

				int size = 0;

				node** n = tachchuts(filecompress, size);
				node* tempn = new node[size];
				for (int i = 0; i < size; i++)
				{
					tempn[i].data = n[i]->data;
					tempn[i].freq = n[i]->freq;
				}

				board** tree = huffmantree(n, size);

				string* tmp = new string[256];

				for (int i = 0; i < size; i++)
				{
					if (int(tree[i]->data) < 0)
					{
						tmp[int(tree[i]->data) + 256] = (tree[i]->bin);

					}
					else
						tmp[int(tree[i]->data)] = (tree[i]->bin);
				}

				compression(outfolder, filecompress, filepath[j], tmp, size, tempn);
			}
			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			
			system("cls");
			
			cout << "Compresstion time: " << duration.count() << endl;
			cout << "DONE!!!" << endl<<endl;
			
			break;
		}
		case 3:
		{
			cout << "---o0o---Decompress file---o0o---" << endl;
			
			string filepath ;
			string filename;
			string outfile;
			
			cin.ignore(37655, '\n');
			cout << "Nhap duong dan file nen (D:/folder): ";
			getline(cin, filepath);
			cout << "Nhap ten file nen (ex: compress_name.txt): ";
			getline(cin, filename);
			cout << "Nhap duong dan xuat file sau giai nen: ";
			getline(cin, outfile);

			//Tao thu muc va dau ra file
			filepath += '/';
			filepath += filename;
			filename = "De" + filename;
			
			auto start = high_resolution_clock::now();
			
			cout <<"Decomressing......" << endl;
			
			//Giai nen
			decompression(filepath, outfile,filename);
			
			cout << "DONE!!!" << endl << endl;
			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			cout << "Decompresstion time: " << duration.count() << endl;
			
			break;
		}

		case 4:
		{
			cout << "--o0o--Decompress folder--o0o--" << endl;

			string filename[200];

			string infolderstr;
			string outfolder;

			int numoffile = 0;
			cin.ignore(37655, '\n');
			cout << "Nhap duong dan(ex:D/folder): ";
			getline(cin, infolderstr);
			cout << "Nhap duong dan luu file da nen(ex:D/folder): ";
			getline(cin, outfolder);

			const char* infolder = infolderstr.c_str();
			
			//Lay file tu thu muc
			getfilepathinfolder(infolder, filename, numoffile);
			
			auto start = high_resolution_clock::now();

			for (int i = 0; i < numoffile; i++) 
			{
				string filepath = infolderstr;
				filepath+= '/';
				filepath += filename[i];
				filename[i] = "De" + filename[i];
				cout <<i+1<< ".Decomressing......" << endl;
				decompression(filepath, outfolder, filename[i]);
				cout << "DONE!!!" << endl << endl;
			}

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			
			cout << "Decompresstion time: " << duration.count() << endl;
			
			break;
		}
		case 0:
			break;
		default:
		{
			system("cls");
			cout << "Gia tri ban nhap khong hop le, vui long nhap lai: ";
			cin >> choose;
			break;
		}
		}
		if (choose != 0)
		{
			int choose2;
			cout << "Ban co muon tiep tuc: \n1. Co.\n2.Khong.\nNhap: ";
			cin >> choose2;
			if (choose2 == 2)
			{
				system("cls");
				break;
			}
			else
				system("cls");
		}
	}while (choose != 0);
	cout << "Cam on vi da su dung!!!";
}