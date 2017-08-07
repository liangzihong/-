#include<iostream>
#include<deque>
using namespace std;


//其实就是当需要得到地址时的操作。
/*	今天用了几个小时的时间找一个bug，就是在建立哈夫曼树的时候，建立了一个节点，然后再把节点放进去，然后又不断处理
涉及left和right指针的处理，一直在找，为什么当mindelete返回的是指针变量时可行，而如果返回的是节点的地址则不可以。
	然后终于找到了原因。罪魁祸首就是   返回的是局部变量的地址   这导致所有经过mindelete函数的指向都会随着每一次
mindelete的指向而不断变化，因为比如第一个出来的我把left指针设为&mindelete，而其实&mindelete每次都一样，随着每一次调用，
&mindelete指向的房间内容不断变化，如此一来，代码就完全错误了。


所以经验如下：
	如果要返回一个地址或一个变量的地址，只有两个方法
	一：返回类型就是指针变量，且返回的东西本身就是指针变量而不是&+局部变量。
	二：用temp=new struct; *temp=sth; 再返回temp即可，原理是避免用&mindelete这个出口的固定局部变量指针。
	三：尽量避免使用&function（）这种来获取你设想中出现的返回元素的地址，其实很大可能是局部变量的出口地址。
不是说不可以，但是你要做后续操作的时候就会出差错。
*/


struct treenode
{
	int value;
	treenode*left;
	treenode*right;
};

typedef treenode* huffmantree;
typedef deque<treenode> heap;

heap insert(heap H, treenode temp)
{
	H.push_back(temp);
	cout << (void*)&temp<<endl;
	return H;
}

treenode* mindelete(heap* H)
{
	huffmantree temp = new treenode;
	*temp = H->front();
	H->pop_front();
	return temp;
}


huffmantree build(huffmantree huff)
{
	heap arr;
	int ar[5] = { 1,2,3,4,5 };
	huffmantree a = new treenode[5];
	for (int i = 0; i < 5; i++)
	{
		a[i].value = ar[i];
		a[i].left = NULL;
		a[i].right = NULL;
		arr = insert(arr, a[i]);
	}



	while (arr.size() != 1)
	{
		huffmantree ans = new treenode;
		ans->left = mindelete(&arr);
		cout << "left" << (void*)ans->left << "------";
		ans->right=mindelete(&arr);
		cout << "right" << (void*)ans->right << "------";
		ans->value = ans->left->value + ans->right->value;
		cout << (void*)ans << "****";
		arr = insert(arr, *ans);
	}
	huff= mindelete(&arr);
	return huff;
}

int main()
{
	huffmantree huff = NULL;
	huff = build(huff);
	system("pause");
}

/*#include<iostream>
#include<deque>
using namespace std;

struct treenode
{
	int value;
	treenode*left;
	treenode*right;
};

typedef treenode* huffmantree;
typedef deque<treenode*> heap;

heap insert(heap H, treenode* temp)
{
	H.push_back(temp);
	cout << (void*)temp << endl;
	return H;
}

treenode* mindelete(heap* H)
{
	treenode* temp =H->front();
	H->pop_front();
	return temp;
}


huffmantree build(huffmantree huff)
{
	heap arr;
	int ar[5] = { 1,2,3,4,5 };
	huffmantree* a = new huffmantree[5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = new treenode;
		a[i]->value = ar[i];
		a[i]->left = NULL;
		a[i]->right = NULL;
		arr = insert(arr, a[i]);
	}


	while (arr.size() != 0)
	{
		cout << (void*)arr.front() << "*********";
		cout << (void*)mindelete(&arr) <<endl;
	}

	/*huffmantree *ans = new huffmantree[10];
	int cnt = 0;
	while (arr.size() != 1)
	{
		ans[cnt] = new treenode;
		ans[cnt]->left = mindelete(&arr);
		//cout << "left" << (void*)ans[cnt]->left << "------";
		ans[cnt]->right = mindelete(&arr);
		//cout << "right" << (void*)ans[cnt]->right << "------";
		ans[cnt]->value = ans[cnt]->left->value + ans[cnt]->right->value;
		//cout << (void*)ans[cnt] << "****";
		arr = insert(arr, *ans[cnt]);
		cnt++;
	}
	huff = mindelete(&arr);*/
	/*return huff;
}

int main()
{
	huffmantree huff = NULL;
	huff = build(huff);
	system("pause");
}*/