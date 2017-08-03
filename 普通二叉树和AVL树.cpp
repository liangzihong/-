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


//�������
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

//ǰ�����
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

//�������
void aftout(bintree T)
{
	if (T == NULL)
		return;
	aftout(T->left);
	aftout(T->right);
	cout << T->data;
}

//�ǵݹ����
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

//�������
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

//�������ĸ߶�
int getheight(bintree T)
{
	if (T == NULL) return 0;
	int left = getheight(T->left);
	int right = getheight(T->right);
	int height = left > right ? left : right;
	height++;
	return height;
}


//�������ɶ�����
//�������ɶ������鱾��ʵ�����Ϊ���ݴ�һ��ʼֻ��һ�����ڵ㣬���Խ���������������һ�������ĺ���
//�������һ����ÿ������һ���ڵ㣬��������ڵ�data���⣬��ֱ�Ӱ����������������ݶ�����
//������û����Ϊ��һ��ʼ��ע�����Աߵ��ֵܽڵ㶼�Ѿ������ˣ�������һ�����ݾ����Լ��������ݡ�
//���Կ�������  ���г�����Ѻ��Ӹ㶨���ٰѲ�ΪNULL��������У�����������ָ���ָ�봦��

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


//�����������Ĳ����뽨��
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

//�����������ĵݹ����
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

//�����������ķǵݹ����
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

//����������������Сֵ
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

//�����������������ֵ
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

//������������ɾ��  
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
		else if (T->left == NULL&&T->right != NULL)              //���ҽ��û��ڵ㣬����
			T = T->right;
		else if (T->right == NULL&&T->left != NULL)
			T = T->left;
		else    //�������ڵ�
		{
			/*bintree temp;     
			temp = Findemin(T->right);
			temp->left = T->left;           ������ʵҲ���ԣ���Ч����̫�ã�*/
			
			bintree temp;
			temp = Findmin(T->right);
			T->data = temp->data;
			T->right = BSTdelete(T->right, temp->data);
			//���������������С�ڵ����ǰ�ڵ㻻����ɾ����С�ڵ㣬�������Ĳ��������̫��
		}


	}
	return T;
}


//AVL������
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

//AVL���ҵ���
bintree AVLrightrotation(bintree T)
{
	if (!T) return NULL;
	bintree temp = T->right;
	T->right = T->right->left;
	temp->left = T;
	T = temp;
	return T;
}

//AVL���Һ���˫��
bintree AVLrightleftrotation(bintree T)
{
	T->right = AVLleftrotation(T->right);
	T = AVLrightrotation(T);
	return T;
}

//AVL�������˫��
bintree AVLleftrightrotation(bintree T)
{
	T->left = AVLrightrotation(T->left);
	T = AVLleftrotation(T);
	return T;
}



//AVL���Ĳ������
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
	//���������ǲ���������ɣ����濪ʼ���ݸ߶������е�����

	if (getheight(T->left) - getheight(T->right) == 2)     
	{
		if (target < T->left->data)    //����
		{
			T = AVLleftrotation(T);
		}
		else if (target > T->left->data)   //����˫��
		{
			T = AVLleftrightrotation(T);
		}
	}

	else if (getheight(T->left) - getheight(T->right) == -2)
	{
		if (target > T->right->data)   //�ҵ���
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

//AVL����ɾ������
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
		else if (T->left == NULL&&T->right != NULL)              //���ҽ��û��ڵ㣬����
			T = T->right;
		else if (T->right == NULL&&T->left != NULL)
			T = T->left;
		else    //�������ڵ�
		{
			/*bintree temp;
			temp = Findemin(T->right);
			temp->left = T->left;           ������ʵҲ���ԣ���Ч����̫�ã�*/

			bintree temp;
			temp = Findmin(T->right);
			T->data = temp->data;
			T->right = AVLdelete(T->right, temp->data);
			//���������������С�ڵ����ǰ�ڵ㻻����ɾ����С�ڵ㣬�������Ĳ��������̫��
		}
	}
	if (getheight(T->left) - getheight(T->right) == 2)
	{
		if (target < T->left->data)    //����
		{
			T = AVLleftrotation(T);
		}
		else if (target > T->left->data)   //����˫��
		{
			T = AVLleftrightrotation(T);
		}
	}
	else if (getheight(T->left) - getheight(T->right) == -2)
	{
		if (target > T->right->data)   //�ҵ���
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






