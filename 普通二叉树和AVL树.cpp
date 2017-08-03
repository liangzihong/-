#include<iostream>
#include<deque>
#include<stack>
#include<cmath>
#include<string>
using namespace std;

typedef int elementtype;

struct treenode
{
	elementtype data;
	treenode* left;
	treenode* right;
};

typedef treenode* bintree;


//中序遍历
void midout(bintree T)
{
	if (T == NULL)
		return;
	else
	{
		midout(T->left);
		cout << T->data;
		midout(T->right);
	}
}

//前序遍历
void befout(bintree T)
{
	if (T == NULL)
	{
		return;
	}
	else
	{
		cout << T->data;
		befout(T -> left);
		befout(T->right);
	}
}

//后序遍历
void aftout(bintree T)
{
	if (T == NULL)
		return;
	aftout(T->left);
	aftout(T->right);
	cout << T->data;
}

//非递归遍历
void output(bintree T)
{
	stack<bintree> staarr3;
	if (T == NULL) return;
	while (T != NULL||staarr3.size()!=0)
	{
		if (T != NULL) 
		{
			staarr3.push(T);
			T = T->left;
		}
		
		if (T==NULL&&staarr3.size() != 0)
		{
			T = staarr3.top();
			cout << T->data;
			staarr3.pop();
			T = T->right;
		}
	}
	
}

//层序遍历
void leveloutput(bintree T)
{
	deque<bintree> arr;
	if (T == NULL) return;

	arr.push_back(T);
	while (arr.size()!=0)
	{
		T = arr.front();
		arr.pop_front();
		if (T != NULL) {
			arr.push_back(T->left);
			arr.push_back(T->right);
			cout << T->data<<" ";
		}
	}
}

//二叉树的高度
int getheight(bintree T)
{
	if (T == NULL) return 0;
	int left = getheight(T->left);
	int right = getheight(T->right);
	int height = left > right ? left : right;
	height++;
	return height;
}


//层序生成二叉树
//层序生成二叉树书本其实更妙，因为数据从一开始只有一个根节点，所以接下来的两个数据一定是它的孩子
//所以如此一来，每次生成一个节点，输入这个节点data以外，还直接把它的两个孩子数据都输入
//这样做没错，因为从一开始就注定你旁边的兄弟节点都已经填满了，所以下一个数据就是自己孩子数据。
//所以可以连续  队列出来后把孩子搞定，再把不为NULL的输入队列，这样不必用指针的指针处理

bintree build(bintree root)
{
	elementtype data;
	deque<bintree*> arr;
	arr.push_back(&root);
	int state = 1;
	while (cin >> data)
	{
		if (data == -1) {
			arr.pop_front();
		}
		else {
			bintree T = *arr.front();
			if (T == NULL) {
				*arr.front() = new treenode; T = *arr.front();
			}
			if (state == 1) {
				root = T, state = 0;
			}
			arr.pop_front();
			T->data = data, T->left = NULL, T->right = NULL;
			arr.push_back(&(T->left));
			arr.push_back(&(T->right));
		}
	}
	return root;

}


//二分搜索树的插入与建立
bintree BSTinsert(bintree T, elementtype target)
{
	if(T==NULL)
	{
		T = new treenode;
		T->data = target, T->left = NULL, T->right = NULL;
	}
	else if (target < T->data) T->left = BSTinsert(T->left, target);
	else T->right = BSTinsert(T->right, target);
	return T;
}

//二分搜索树的递归查找
bintree BSTsearch1(bintree T, elementtype target)
{
	if (T == NULL)
		return NULL;
	else if (T->data == target)
		return T;
	else
	{
		bintree ans = NULL;
		if (target < T->data)
			ans = BSTsearch1(T->left, target);
		else if (target > T->data)
			ans = BSTsearch1(T->right, target);
		return ans;
	}
}

//二分搜索树的非递归查找
bintree BSTsearch2(bintree T, elementtype target)
{
	bintree ans = NULL;
	while (T != NULL)
	{
		if (T->data == target)
		{
			ans = T; break;
		}
		else if (T->data > target)
			T = T->left;
		else T = T->right;
	}
	return ans;
}

//二分搜索树的找最小值
bintree Findmin(bintree T)
{
	if (T == NULL) return T;
	else
	{
		while (T->left != NULL)
		{
			T = T->left;
		}
		return T;
	}
}

//二分搜索树的找最大值
bintree Findmax(bintree T)
{
	if (T == NULL) return T;
	else
	{
		while (T->right != NULL)
		{
			T = T->right;
		}
		return T;
	}

}

//二分搜索树的删除  
bintree BSTdelete(bintree T,elementtype target)
{
	if (T == NULL) return NULL;
	else if (target < T->data)
		T->left = BSTdelete(T->left, target);
	else if (target > T->data)
		T->right = BSTdelete(T->right, target);
	else
	{
		if (T->left == NULL&&T->right == NULL) return NULL;
		else if (T->left == NULL&&T->right != NULL)              //有右结点没左节点，所以
			T = T->right;
		else if (T->right == NULL&&T->left != NULL)
			T = T->left;
		else    //有两个节点
		{
			/*bintree temp;     
			temp = Findemin(T->right);
			temp->left = T->left;           这种其实也可以，但效果不太好，*/
			
			bintree temp;
			temp = Findmin(T->right);
			T->data = temp->data;
			T->right = BSTdelete(T->right, temp->data);
			//这个拿右子树的最小节点跟当前节点换，再删除最小节点，这样树的层数不会差太多
		}


	}
	return T;
}


//AVL树左单旋
bintree AVLleftrotation(bintree T)
{
	if (!T) return NULL;
	/*bintree temp = T->left;
	T->left = temp->right;
	temp->left = T;
	T = temp;
	return T;*/

	bintree temp = T->left;
	T->left = T->left->right;
	temp->right = T;
	T = temp;
	return T;
}

//AVL树右单旋
bintree AVLrightrotation(bintree T)
{
	if (!T) return NULL;
	bintree temp = T->right;
	T->right = T->right->left;
	temp->left = T;
	T = temp;
	return T;
}

//AVL先右后左双旋
bintree AVLrightleftrotation(bintree T)
{
	T->right = AVLleftrotation(T->right);
	T = AVLrightrotation(T);
	return T;
}

//AVL先左后右双旋
bintree AVLleftrightrotation(bintree T)
{
	T->left = AVLrightrotation(T->left);
	T = AVLleftrotation(T);
	return T;
}



//AVL树的插入调整
bintree AVLinsert(bintree T, elementtype target)
{
	if (T == NULL) {
		T = new treenode;
		T->data = target, T->left = NULL, T->right = NULL;
		return T;
	}
	else if (T->data > target) {
		T->left = AVLinsert(T->left, target);
	}
	else if (T->data < target) {
		T->right = AVLinsert(T->right, target);
	}
	//以上三步是插入数据完成，下面开始根据高度来进行调整。

	if (getheight(T->left) - getheight(T->right) == 2)     
	{
		if (target < T->left->data)    //左单旋
		{
			T = AVLleftrotation(T);
		}
		else if (target > T->left->data)   //左右双旋
		{
			T = AVLleftrightrotation(T);
		}
	}

	else if (getheight(T->left) - getheight(T->right) == -2)
	{
		if (target > T->right->data)   //右单旋
		{
			T = AVLrightrotation(T);
		}
		else if (target < T->right->data)
		{
			T = AVLrightleftrotation(T);
		}
	}
	return T;
}

//AVL树的删除调整
bintree AVLdelete(bintree T, elementtype target)
{
	if (T == NULL) return NULL;
	else if (target < T->data)
		T->left = AVLdelete(T->left, target);
	else if (target > T->data)
		T->right = AVLdelete(T->right, target);
	else
	{
		if (T->left == NULL&&T->right == NULL) return NULL;
		else if (T->left == NULL&&T->right != NULL)              //有右结点没左节点，所以
			T = T->right;
		else if (T->right == NULL&&T->left != NULL)
			T = T->left;
		else    //有两个节点
		{
			/*bintree temp;
			temp = Findemin(T->right);
			temp->left = T->left;           这种其实也可以，但效果不太好，*/

			bintree temp;
			temp = Findmin(T->right);
			T->data = temp->data;
			T->right = AVLdelete(T->right, temp->data);
			//这个拿右子树的最小节点跟当前节点换，再删除最小节点，这样树的层数不会差太多
		}
	}
	if (getheight(T->left) - getheight(T->right) == 2)
	{
		if (target < T->left->data)    //左单旋
		{
			T = AVLleftrotation(T);
		}
		else if (target > T->left->data)   //左右双旋
		{
			T = AVLleftrightrotation(T);
		}
	}
	else if (getheight(T->left) - getheight(T->right) == -2)
	{
		if (target > T->right->data)   //右单旋
		{
			T = AVLrightrotation(T);
		}
		else if (target < T->right->data)
		{
			T = AVLrightleftrotation(T);
		}
	}
	return T;
}

int main() 
{
	bintree head;
	bintree target=NULL;
	head = NULL;
	elementtype ch;
	
	while (cin >> ch)
	{
		head=AVLinsert(head, ch);
		leveloutput(head); cout << endl;
	}
	head = AVLdelete(head,11);
	leveloutput(head); cout << endl;

	/*bintree min = NULL;
	bintree max = NULL;
	min = Findmin(head);
	max = Findmax(head);
	cout << "min is " << min->data << endl;
	cout << "max is " << max->data << endl;

	head = BSTdelete(head,min->data);
	head = BSTdelete(head, max->data);
	
	min = Findmin(head);
	max = Findmax(head);
	cout << "min is " << min->data << endl;
	cout << "max is " << max->data << endl;
	
	head = BSTdelete(head, 'j');*/
	//leveloutput(head); cout << endl;
	
	
	//if (target != NULL) cout << target->data;
	//else cout << "zhaobudao";
	
	
	
	//leveloutput(head);
	//befout(head);
	//midout(head);
	//output(head);


	system("pause");
}






