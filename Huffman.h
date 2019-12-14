#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

struct node
{
	char data;
	long int freq;
	node* left,* right;
};
struct board 
{
	char data;
	string bin;
};

//Tao board
board* createboard(char data);
//Tao node
node* createnode(char data, long int  freq);
// Swap 2 ky tu
void swap(node& a, node& b);
//Min heap cay
void heapify(node** data, int size, int idx);
void minheap(node** alp, int size);
//Them 1 node moi
void insertnode(node** alp, int& size, node* top);
//Lay min node trong node
node* extracminnode(node** alp, int& size);
//In tan so , ky tu
void printfreq(node* tree);
//Xay cay huffman
node* buildhuffmantree(node** alp, int size);
//Danh so ky tu
void ticknumber(node* alp, board** res, int size, int arr[], int top);
//Doi node sang board
board** changenodetoboard(node** alp, int size);
//Tao ra mang ky tu ,a nhi phan tu huffman
board** huffmantree(node** alp, int size);


