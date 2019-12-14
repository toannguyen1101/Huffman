#pragma once
#include<fstream>
#include<string.h>
#include<math.h>
#include"Huffman.h"

//Nen file
void compression(string outfolder, string filecompress, string filepath, string* tmp, int size, node* n);
