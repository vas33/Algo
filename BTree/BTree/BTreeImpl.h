#pragma once
#include <vector>
#include <memory>
#include <iterator>
#include <iostream>
#include <queue>
#include <deque>


template <typename T>
class BTreeNode
{
	template <typename T, int>
	friend class BTree;

public:
	BTreeNode() :m_isLeafNode(false)
	{}

	void PrintNode()
	{
		std::cout << "|  ";

		typedef std::vector<T>::const_iterator Iter;
		for (Iter current = m_keys.begin(); current != m_keys.end();++current)
		{
			std::cout << *current;
		}

		std::cout << "  |";
	}

private:
	bool m_isLeafNode;
	std::vector<std::unique_ptr<BTreeNode<T>>> m_Child;
	std::vector<T> m_keys;
};

template <typename T,  const int BranchFactor = 5>
class BTree
{
public:
	typedef typename BTreeNode<T>* NodePtr;
	typedef typename std::unique_ptr<BTreeNode<T>> NodeLink;
	typedef typename std::shared_ptr<BTreeNode<T>> LeafNodeLink;
	typedef typename std::vector<NodeLink>::iterator IterChild;
	typedef typename std::vector<T>::iterator IterKeys;

protected:
	void SplitChild(NodeLink& node, unsigned int nodeIndex)
	{
		//create new node
		NodeLink newNode = allocateNode();

		//set lhs node to being node index
		NodeLink lhsNode = std::move(node->m_Child[nodeIndex]);
		
		//remove for sure 
		node->m_Child.erase(node->m_Child.begin() + nodeIndex);

		//set leaf node pointer
		newNode->m_isLeafNode = lhsNode->m_isLeafNode;

		//move rhs from node to new node
		{
			IterKeys begin = lhsNode->m_keys.begin() + BranchFactorByTwo;
			IterKeys end = lhsNode->m_keys.end();


			std::move(begin , end, std::back_inserter(newNode->m_keys));

			lhsNode->m_keys.erase(begin, end);
		}

		//move child values to new node
		if (!lhsNode->m_isLeafNode)
		{
			IterChild begin = lhsNode->m_Child.begin() + BranchFactorByTwo;
			IterChild end = lhsNode->m_Child.end();

			std::move(begin, end, std::back_inserter(newNode->m_Child));

			lhsNode->m_Child.erase(begin, end);
		}

		//take key from splited child and move it to root
		{
			IterKeys element = lhsNode->m_keys.begin() + BranchFactorByTwo -1;
			T key = *element;
			int insertIndex = node->m_keys.size();
			while (insertIndex >= 1 && key < node->m_keys[insertIndex- 1])
			{
				insertIndex--;
			}

			IterKeys insertLocation = node->m_keys.begin() + insertIndex;

			node->m_keys.insert(insertLocation, std::move(*element));

			lhsNode->m_keys.erase(element);		
		}

		//beceuse uniqie ptr rules we have to add child nodes at end
		node->m_Child.insert(node->m_Child.begin() + nodeIndex , std::move(lhsNode));
		node->m_Child.insert(node->m_Child.begin() + nodeIndex + 1, std::move(newNode));
	}

	void InsertNonFull(NodeLink& node, T key)
	{
		//get initial index
		unsigned int index = node->m_keys.size();

		if (node->m_isLeafNode)
		{
				while (index >= 1 && key < node->m_keys[index-1])
				{
					--index;
				}

			//add key at appropriate index and increment num items
			node->m_keys.insert(node->m_keys.begin() + index, key);
			//++node->m_numChild;
		}
		else
		{
			//find insert position
			if (index)
				while (index >= 1 && key < node->m_keys[index-1])
				{
					--index;
				}

			//index++;
			//check child count if bigger than alowwed split
			if (node->m_Child[index]->m_keys.size() > 2 * BranchFactorByTwo - 1)
			{
				SplitChild(node, index);
				if (key > node->m_keys[index])
				{
					index++;
				}
			}

			InsertNonFull(node->m_Child[index], key);
		}

	}
	
	int SearchNode(NodeLink& startNode, T key)
	{
		int index = 0;
		while (static_cast<unsigned int>(index) < startNode->m_keys.size() && key > startNode->m_keys[index])
		{
			++index;
		}

		if (static_cast<unsigned int>(index) < startNode->m_keys.size() && key == startNode->m_keys[index])
		{
			return index;
		}
		else if (startNode->m_isLeafNode)
		{
			return -1;
		}
		else
		{
			return SearchNode(startNode->m_Child[index], key);
		}
	}
public:
	BTree():m_root(allocateNode())
	{		
		m_root->m_isLeafNode = true;
	}

	NodeLink allocateNode()
	{
		return NodeLink(new BTreeNode<T>());
	}

	void Insert(T key)
	{
		if (m_root->m_keys.size() == 2 * BranchFactorByTwo - 1)
		{
			NodeLink newRootNode = allocateNode();
		
			//keep old root
			NodeLink oldRoot;
			std::swap(m_root ,oldRoot);
			
			//make new node the root
			std::swap(newRootNode, m_root);
			m_root->m_isLeafNode = false;

			//make old root child of new one
			m_root->m_Child.push_back(std::move(oldRoot));

			SplitChild(m_root, 0);
		}

		InsertNonFull(m_root, key);

	}

	void PrintClearTree()
	{
		std::deque<LeafNodeLink> printNodes;

		//BTreeNode<T>* nod = m_root.get();
		printNodes.push_back(LeafNodeLink(m_root.release()));
		//print node
		while (!printNodes.empty())
		{
			std::vector<LeafNodeLink> links;

			std::move(printNodes.begin(), printNodes.end(), std::back_inserter(links));
			printNodes.clear();

			for (std::vector<LeafNodeLink>::const_iterator current = links.begin(); current != links.end(); ++current)
			{
				LeafNodeLink node = *current;
				node->PrintNode();

				IterChild currentChild = node->m_Child.begin();
				IterChild endChild = node->m_Child.end();

				//add childs for fpinting on next level
				//add child for printing
				for (;currentChild != endChild; ++currentChild)
				{
					printNodes.push_back(LeafNodeLink((*currentChild).release()));
				}
			}
		
			//print new line
			cout << std::endl;
		}
		
	}


	int Search(T key)
	{
		return SearchNode(m_root, key);
	}
private:
	static const int BranchFactorByTwo = BranchFactor / 2;
	typename NodeLink m_root;
};