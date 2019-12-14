#include"Huffman.h"


board* createboard(char data)
{
	board* tmp = new board;
	tmp->data = data;
	return tmp;
}

node* createnode(char data, long int  freq)
{
	node* tmp = new node;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->data = data;
	tmp->freq = freq;
	return tmp;
}
void swap(node& a, node& b) {
	node tmp = a;
	a = b;
	b = tmp;
}
//Min heap node
void heapify(node** data, int size, int idx)
{
	int min = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < size && data[left]->freq < data[min]->freq)
		min = left;
	if (right < size && data[right]->freq < data[min]->freq)
		min = right;

	if (min != idx)
	{
		swap(data[idx], data[min]);
		heapify(data, size, min);
	}
}

void minheap(node** alp, int size)
{
	for (int i = (size - 1) / 2; i >= 0; i--)
		heapify(alp, size, i);
}

//Them 1 node vao node
void insertnode(node** alp, int& size, node* top)
{
	++size;
	int i = size - 1;

	while (i && top->freq < alp[(i - 1) / 2]->freq) {

		alp[i] = alp[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	alp[i] = top;
}

//Lay node root cua min heap
node* extracminnode(node** alp, int& size)
{
	node* tmp = alp[0];

	alp[0] = alp[size - 1];
	size--;
	minheap(alp, size);
	return tmp;
}

//In tan so va ky tu
void printfreq(node* tree) {
	if (tree != NULL)
	{
		cout << tree->data << ": " << tree->freq << endl;
		printfreq(tree->left);
		printfreq(tree->right);
	}
}

//Xay dung cay huffman
node* buildhuffmantree(node** alp, int size)
{
	node* left, * right, * top;
	int count = size;
	while (count > 1)
	{
		//Lay 2 phan tu nho nhat trong mang xong gan vao node top de tao cay
		left = extracminnode(alp, count);
		right = extracminnode(alp, count);

		top = createnode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertnode(alp, count, top);

	}

	return alp[0];

}

void ticknumber(node* alp, board** res, int size, int arr[], int top) {
	
	//Danh so 0 1 cho tung node trong cay 
	if (alp->left)
	{
		arr[top] = 0;
		ticknumber(alp->left, res, size, arr, top + 1);
	}

	if (alp->right) 
	{
		arr[top] = 1;
		ticknumber(alp->right, res, size, arr, top + 1);
	}

	//Tien hanh gan ma nhi phan cho ky tu
	if (alp->right == NULL && alp->left == NULL)
	{
		for (int i = 0; i < size; i++)
		{
			if (res[i]->data == alp->data)
			{
				for (int j = 0; j < top; j++)
				{
					if (arr[j] == 1)
						res[i]->bin.append("1");
					else
						res[i]->bin.append("0");
				}
				break;
			}
		}


	}
}

//Doi ky tu kieu node sang board
board** changenodetoboard(node** alp, int size)
{
	board** tmp = new board * [size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = createboard(alp[i]->data);
	}
	return tmp;
}

board** huffmantree(node** alp, int size)
{
	minheap(alp, size);
	board** result = changenodetoboard(alp, size);
	node* tree = buildhuffmantree(alp, size);
	int arr[256];
	int top = 0;
	ticknumber(tree, result, size, arr, top);
	return result;
}