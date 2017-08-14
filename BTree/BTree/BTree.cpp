// BTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BTreeImpl.h"
#include <string>
#include <assert.h>

using namespace std;
int main()
{

	BTree<string,5> tree;

	//tree.Insert("A");
	//tree.Insert("B");
	//tree.Insert("C");
	//tree.Insert("D");
	//tree.Insert("E");
	//tree.Insert("F");
	//tree.Insert("G");
	//tree.Insert("H");
	//tree.Insert("I");
	//tree.Insert("J");
	//tree.Insert("K");
	//tree.Insert("L");
	//tree.Insert("M");
	//tree.Insert("N");
	//tree.Insert("O");
	//tree.Insert("P");
	//tree.Insert("Q");
	//tree.Insert("R");
	//tree.Insert("S");
	//tree.Insert("T");
	//tree.Insert("U");

	tree.Insert("F");
	tree.Insert("S");
	tree.Insert("Q");
	tree.Insert("K");
	tree.Insert("C");
	tree.Insert("L");

	tree.Insert("H");

	
	tree.Insert("T");
	tree.Insert("V");
	tree.Insert("W");
	tree.Insert("M");
	tree.Insert("R");
	tree.Insert("N");
	tree.Insert("P");
	tree.Insert("A");
	tree.Insert("B");
	tree.Insert("X");
	tree.Insert("Y");
	tree.Insert("D");
	tree.Insert("Z");
	tree.Insert("E");

	int index = tree.Search("C");
	assert(tree.Search("C") >= 0);

	index = tree.Search("A");
	assert(tree.Search("A") >= 0);

	index = tree.Search("V");
	assert(tree.Search("V") >= 0);

	index = tree.Search("W");
	assert(tree.Search("W") >= 0);

	tree.PrintClearTree();

	char exit;
	cin >> exit;
    return 0;

}

