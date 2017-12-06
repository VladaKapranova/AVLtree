#include <stdio.h>

class avl
{
public:
	int key;
	unsigned int height;
	avl *left;
	avl *right;

	unsigned int Height();//Возвращает высоту поддерева с вершиной в данном узле
	int balancefactor();
	void HeightP();//Восстанавливает правильную высоту после поворотов

	avl* rightRotate();//Правый поворот 
	avl* leftRotate();//Левый поворот 
	avl* balance();// Балансировка узла, если баланс-фактор 2 или -2 (большой левый и большой правый повороты в одной функции)

	avl* findmin();//Поиск узла с минимальным ключом в дереве р
	avl* removemin();//Удаление узла с мин ключом из дерева р


	avl()
	{
		key = 0;
		left = 0;
		right = 0;
		height = 0;
	}

	avl(int k)
	{
		key = k;
		left = 0;
		right = 0;
		height = 1;
	}

	void insert(int k); // Вставка элемента в дерево с вершиной р
	avl* search(int k);// Поиск элемента с ключом key в дереве с вершиной р
	avl* deleteroot(int k);// Удаление элемента с ключом р
	void printAVLTree(int level);

};

class AVLtree
{
	avl* root;

public:

	AVLtree(int k)
	{
		root = new avl(k);
	}

	~AVLtree()
	{
		delete root;
	}

	void Insert(int k)
	{
		root->insert(k);
	}

	avl* Search(int k)
	{
		return root->search(k);
	}

	void Delete(int k);

	void Print(int level)
	{
		root->printAVLTree(level);
	}

};

unsigned int avl::Height()
{
	if (this != 0)
		return height;
	else return 0;
}

int avl::balancefactor()
{
	if (this != 0)
	{
		return right->Height() - left->Height();
	}
}

void avl::HeightP()
{
	if (this != 0)
	{
		unsigned int hl, hr;
		if (left != 0)
			hl = left->height;
		else hl = 0;
		if (right != 0)
			hr = right->height;
		else hr = 0;
		height = (hl > hr ? hl : hr) + 1;
	}
}

avl* avl::rightRotate()
{
	avl * q = left;
	left = q->right;
	q->right = this;
	HeightP();
	q->HeightP();
	return q;
}

avl* avl::leftRotate()
{
	avl * p = right;
	right = p->left;
	p->left = this;
	HeightP();
	p->HeightP();
	return p;
}

avl* avl::balance()
{
	HeightP();
	if (balancefactor() == 2)
	{
		if (right->balancefactor() < 0)
			right = right->rightRotate();
		return leftRotate();
	}
	else if (balancefactor() == -2)
	{
		if (left->balancefactor() > 0)
			left = left->leftRotate();
		return rightRotate();
	}
	return this;
}

avl* avl::findmin()
{
	if (left != 0)
		return left->findmin();
	else return this;
}

avl* avl::removemin()
{
	if (left == 0)
		return right;
	left = left->removemin();
	return balance();
}

void avl::insert(int k)
{
	if (k < key)
	{
		if (left == 0)
		{
			left = new avl(k);
			left->balance();
		}
		else left->insert(k);
	}
	else if (k > key)
	{
		if (right == 0)
		{
			right = new avl(k);
			right->balance();
		}
		else right->insert(k);
	}
}

avl * avl::search(int k)
{
	if (this == 0)
		return 0;
	if (k < key)
		left = left->search(k);
	else if (k > key)
		right = right->search(k);
	else return this;
}

avl* avl::deleteroot(int k)
{
	if (this != 0)
	{
		if (k < key)
			left->deleteroot(k);
		else if (k > key)
			right->deleteroot(k); // Ищем ключ
		else //  key == p->key
		{
			if (left == 0 && right == 0)
			{
				delete this;
				return 0;
			}
		else if (left != 0 && right != 0)
		{
			avl* l = left;
			avl* r = right;
			delete this;

			avl* min = r->findmin();
			min->right = r->removemin();
			min->left = l;
			min->balance();
			balance();
		}
		else if (right == 0)
		{
			avl* l = left;
			delete this;
			avl* min = l;
			min->balance();
			balance();
		}
}
return balance();
}
}

void avl::printAVLTree(int level)
{
	if (this == 0)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("%i\n", key);

	left->printAVLTree(level + 1);
	right->printAVLTree(level + 1);
}

void AVLtree::Delete(int k)
{
	avl *el = root->search(k);
	if (el->left == 0 && el->right == 0)
	{
		delete el;
	}
	else
	{
		if (el->right == 0)
		{
			el = el->left;
			delete el->left;
		}
		else if (el->left == 0)
		{
			el = el->right;
			delete el->right;
		}
		else
		{
			avl* l = el->left;
			avl* r = el->right;
			avl* min = r->findmin();
			min->right = r->removemin();
			min->left = l;
			min->balance();
		}
	}

}

void main()
{
	AVLtree* tree = new AVLtree(5);

	tree->Insert(6);
	tree->Insert(4);
	tree->Insert(9);

	tree->Print(0);
	tree->Delete(4);
	tree->Print(0);

	delete tree;

}