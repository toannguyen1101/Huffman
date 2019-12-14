#pragma once
#include<iostream>
#include<math.h>
#include"Huffman.h"
#include<fstream>
using namespace std;

//Chuyen thap phan ve nhi phan
string dectobin(int data);
//Giai nen
void decompression(string filepath, string outfile, string filename);
