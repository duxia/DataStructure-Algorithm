/*
 ============================================================================
 Name        : LinkedList.c
 Author      : coffee
 Version     :
 Copyright   : Copyright ©2015 sweet coffee.All right reserved.
 Description : 单链表整理
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//定义数据结构
typedef int elemType;
typedef struct _node
{
	elemType data;
	struct _node *next;
} Node,*pNode;

//创建链表
void CreateList(pNode *List, elemType array[],int n)
{
	*List = (pNode)malloc(sizeof(Node));//分配链表头结点空间(不放数据)
	pNode p,tail=*List;//定义临时指针和尾指针

	int i;
	for(i=0;i<n;i++) {
		p = (pNode)malloc(sizeof(Node));//分配数据节点空间
		p->data = array[i];//数据赋值
		tail->next = p;//和原链表链接
		tail = p;//尾指针刷新位置
	}
	tail->next = NULL;//尾指针置空
}
//删除链表
void DeleteList(pNode List)
{
	pNode tail,p = List->next;//定义临时指针和尾指针
	while(p) {
		tail = p->next;//先指向下一个数据节点
		free(p);//释放p指向当前节点
		p = tail; //刷新p
	}
	List->next = NULL;//清空头结点
}
//获取第i个位置上的元素(i从1开始计数)
elemType GetElemFromIndex(pNode List,int i)
{
	if(i <= 0)
		return 0;

	pNode p = List->next;
	int index = 1;
	while(p) {
		if(i==index){
			return p->data;
		}
		p = p->next;
		index++;
	}
	return 0;//未找到
}
//找到第一个匹配元素的下标
int GetIndexFromElem(pNode List,elemType data)
{
	pNode p = List->next;
	int index = 1;
	while(p) {
		if(data == p->data)
			return index;
		p = p->next;
		index++;
	}
	return 0;//未找到
}
//给出节点的位置，返回节点指针
pNode GetPointerFromIndex(pNode List, int i)
{
	if(List==NULL || List->next==NULL || i<1)
		return List;

	int index = 1;
	pNode p = List->next;
	while(p) {
		if(index == i)
			return p;
		p = p->next;
		index++;
	}
	return NULL;
}
//元素插入,将元素插入第i个元素之后(i从1开始)
int InsertElem(pNode List,elemType data,int i)
{
	if(i<=0)
		return 0;
	pNode p = List->next;
	int index = 1;
	while(p) {
		if(index == i) {
			pNode tmp = (pNode)malloc(sizeof(Node));
			tmp->data = data;
			tmp->next = p->next;
			p->next = tmp;
			return 1;//插入成功
		}
		p = p->next;
		index++;
	}
	return 0;//插入失败
}
//元素删除,删除第一个满足条件的元素并返回该元素位置
int RemoveElemFromData(pNode List,elemType data)
{
	pNode p = List->next;
	pNode tail = List;//记录p的上一位置
	int index = 1;
	while(p) {
		if(p->data == data) {
			tail->next = p->next;//修改上一位置指针
			free(p);//删除节点
			return index;
		}
		tail = p;
		p = p->next;
		index++;
	}
	return 0;//未找到
}
//元素删除,删除第i个位置上的元素,并返回该元素值
elemType RemoveElemFromIndex(pNode List,int i)
{
	if(i<=0)
		return NULL;
	pNode p = List->next;
	pNode tail = List;//记录p的上一位置
	int index = 1;
	while(p) {
		if(index == i) {
			tail->next = p->next;
			elemType data = p->data;
			free(p);
			return data;
		}
		tail = p;
		p = p->next;
		index++;
	}
	return NULL;
}
//链表逆序
void ReverseList(pNode List)
{
	if(List==NULL || List->next==NULL || List->next->next==NULL)
		return;//无头结点,无数据节点,只有1个数据节点
	pNode prev = List;
	pNode p = prev->next;
	pNode next = p->next;
	p->next = NULL;//第一个数据节点next指针置空
	while(next) {
		prev = p;
		p = next;
		next = next->next;
		p->next = prev;
	}
	List->next = p;//修改头结点
}
//节点交换,交换i,j位置上的节点
int ExchangeNode(pNode List,int i,int j)
{
	pNode p = List->next;
	if(!p || i<1 || j<1)
		return 0;//无数据节点

	pNode prev_i = GetPointerFromIndex(List,i-1);
	pNode prev_j = GetPointerFromIndex(List,j-1);
	pNode pi = prev_i->next;
	pNode pj = prev_j->next;
	prev_i->next = pj;
	prev_j->next = pi;
	//经典三步交换
	pNode tmp = pi->next;
	pi->next = pj->next;
	pj->next = tmp;
	return 1;//交换成功
}
//单链表实现冒泡排序(交互元素,不修改节点指针)
void BubbleSortList(pNode List)
{
	pNode p = List->next;
	if(!p->next || !p)
		return;//没有数据节点或只有一个数据节点
	pNode q = p->next;//q记录当前节点的后继
	pNode end = NULL;//end记录最后一个排好序的节点位置
	while(List->next != end) {//当第一个数据节点还未排好序,则继续排序
	    p = List->next;//每趟排序结束后,p回到第一个数据节点
	    q = p->next;
	    while(p->next != end) {//当p->next == end时,表示已经到达排序好的位置
	        if(p->data > q->data) {
	            elemType tmp = p->data;
	            p->data = q->data;
	            q->data = tmp;
	        }
	        p = q;
	        q = q->next;
	    }
	    end = p;//里层循环退出时p指向本轮排序好的最后一个元素
	}
}
//链表快排_v1(修改指针)
pNode ListPartition(pNode pHead,pNode pEnd)
{
	pNode privoteNode = pHead->next;
	elemType privoteKey = privoteNode->data;
	//将链表划分为2个子链表,p,q分别为子链表的末尾指针
	pNode p = pHead; //p的左侧全部<=privoteKey
	pNode q = pHead->next; //q的左侧全部>privoteKey
	pNode cursor = q->next;//游标初始化,用于遍历该趟链表
	while(cursor != pEnd) {
		if(cursor->data <= privoteKey)//当前游标对应值小于等于pK
			p = p->next = cursor;//将当前节点放在p后,并更新p
		else //当前游标对应值大于pK
			q = q->next = cursor;//将当前节点放在q后,并更新q
		cursor = cursor->next;//游标后移一位
	}
	//链接2个子链表
	q->next = pEnd;
	p->next = privoteNode;
	return privoteNode;
}
void QuickSortList1(pNode pHead,pNode pEnd)
{
	if(pHead->next != pEnd) {
		pNode privote = ListPartition(pHead,pEnd);
		QuickSortList1(pHead,privote);
		QuickSortList1(privote,pEnd);
	}
}
//链表快排_v2(修改指针)
void QuickSortList2(pNode pHead, pNode pEnd)
{
	if ( pHead->next == pEnd)
		return;

	pNode privoteNode = pHead->next;
	elemType pivot = privoteNode->data;

	pNode p = pHead;
	pNode q = privoteNode;
	pNode cursor = privoteNode->next;

	while (cursor != pEnd) {
		if (cursor->data <= pivot)
			p = p->next = cursor;
		else
			q = q->next = cursor;
		cursor = cursor->next;
	}
	p->next = privoteNode;
	q->next = pEnd;

	QuickSortList2(pHead, privoteNode );
	QuickSortList2(privoteNode, pEnd );
}
//打印链表
void PrintList(pNode List)
{
	pNode p = List->next;//指向第一个数据节点
	while(p) {//不为空时循环
		printf("%d->",p->data);
		p=p->next;
	}
	printf("NULL\n");
}
int main(void) {
	int array[] = {1,2,1,2,4,5};
	pNode List;

	//由于List的初始化在函数内部,因此需要将地址传入,若在main中初始化,可以直接传入
	CreateList(&List,array,6);
	printf("初始化后当前链表为:\n");
	PrintList(List);

	QuickSortList1(List,NULL);
	printf("第一次排序后为:\n");
	PrintList(List);

	printf("第3个元素为:\n");
	elemType data = GetElemFromIndex(List,3);
	printf("%d\n",data);

	printf("5在第几位:\n");
	int index = GetIndexFromElem(List,5);
	printf("%d\n",index);

	InsertElem(List,8,3);
	printf("将8插入第3位后,链表为:\n");
	PrintList(List);

	RemoveElemFromData(List,1);
	printf("删除1后,链表为:\n");
	PrintList(List);

	RemoveElemFromIndex(List,3);
	printf("删除第3位置上的元素后,链表为:\n");
	PrintList(List);

	ReverseList(List);
	printf("逆序后链表为:\n");
	PrintList(List);

	QuickSortList2(List,NULL);
	printf("链表快排v2后为:\n");
	PrintList(List);

	pNode p = GetPointerFromIndex(List,3);
	printf("3号节点的指针为:%p,对应数据为:%d\n",p,p->data);

	ExchangeNode(List,1,3);
	printf("交换1,3节点后,链表为:\n");
	PrintList(List);

	BubbleSortList(List);
	printf("排序后的链表为:\n");
	PrintList(List);

	DeleteList(List);
	printf("清空链表后为:\n");
	PrintList(List);

	return EXIT_SUCCESS;
}
