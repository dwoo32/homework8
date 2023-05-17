#include<stdio.h>
#include<stdlib.h>


typedef struct Node {//Node 구조체 선언
	int key;//int형 변수 key 선언
	struct Node* llink;//Node 포인터 llink 선언
	struct Node* rlink;//Node 포인터 rlink 선언
} listNode;//구조체 listNode로 명칭 정함

/* 함수 리스트 */
int initialize(listNode** h);//listNode형 이중포인터 h를 매개변수로 하는 int형 intitialize 함수, headNode에 메모리를 할당하여 초기화함
                             //이중포인터로 받아 포인터 h의 값을 변경 가능
int freeList(listNode* h); //listNode형 포인터 h를 매개변수로 하는 int형 freeList함수, 할당된 메모리 해제
int insertLast(listNode* h, int key);//listNode형 포인터 h와 int형 변수 key를 매개변수로 하는 int형 함수insertLast
									 //list의 끝 부분에 key에 대한 노드를 추가
int deleteLast(listNode* h);//listNode형 포인터 h 매개변수로 하는 int형 deleteLast 함수, list의 마지막 노드 삭제
int insertFirst(listNode* h, int key);//listNode의 포인터 h, int형 변수 key를 매개변수로 하는 int형 insertFirst함수, 
									  //list의 첫 부분에 key에 대한 노드를 추가
int deleteFirst(listNode* h);//listNode의 포인터h를 매개변수로 하는 int형 deleteFirst함수, list의 첫 노드를 삭제
int invertList(listNode* h);//listNode의 포인터 h를 매개변수로 하는 int형 invertList함수, list의 link를 역순으로 재배치

int insertNode(listNode* h, int key);//listNode의 포인터 h, int형 변수 key를 매개변수로 하는 int형 insertNode함수, list에 key에 대한 노드를 추가
int deleteNode(listNode* h, int key);//listNode의 포인터 h, int형 변수 key를 매개변수로 하는 int형 deleteNode함수, list의 노드 하나 삭제

void printList(listNode* h);//listNode의 포인터 h를 매개변수로 하는 void형 함수 printList 함수, list 출력



int main()
{
	char command;//문자형 변수 command 선언
	int key;//int형 변수 key 선언
	listNode* headnode=NULL;//listNode의 포인터 headnode를 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf("------------------ [Kimdongwoo] [2020039058] -------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {//command 값에 따른 switch 조건문
		case 'z': case 'Z'://z 대소문자 입력 받았을 때
			initialize(&headnode);//headnode의 주소를 매개변수로 하는 intitialize 함수 실행
			break;
		case 'p': case 'P':// p 대소문자 입력 받았을 때
			printList(headnode);//headnode를 매개변수로 printlist 호출하여 list 출력
			break;
		case 'i': case 'I'://i 대소문자 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력 받은 값 key에 할당
			insertNode(headnode, key);//insertNode 함수 호출로 key에 대한 노드 추가
			break;
		case 'd': case 'D'://d 대소문자 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력 받은 값 key에 할당
			deleteNode(headnode, key);//deleteNode 함수 호출로 key에 대한 노드 하나 삭제
			break;
		case 'n': case 'N'://n 대소문자 입력받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력 받은 값 key에 할당
			insertLast(headnode, key);//insertLast함수 호출로 list의 마지막 부분에 노드 하나 추가
			break;
		case 'e': case 'E'://e 대소문자 입력 받았을 때
			deleteLast(headnode);//headnode를 매개변수로 deleteLast함수 호출로 list의 마지막 노드 삭제
			break;
		case 'f': case 'F'://f 대소문자 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력 받은 값 key에 할당
			insertFirst(headnode, key);//headnode와 key를 매개변수로 insertFirst함수 호출하여 list의 첫부분에 노드 하나 추가
			break;
		case 't': case 'T'://t 대소문자 입력 받았을 때
			deleteFirst(headnode);//headnode를 매개변수로 deleteFirst함수 호출하여 list의 첫번째 노드 삭제
			break;
		case 'r': case 'R'://r 대소문자 입력 받았을 때
			invertList(headnode);//headnode를 매개변수로 invertList 함수 호출하여 list 역순으로 재배열
			break;
		case 'q': case 'Q'://q 대소문자 입력 받았을 때
			freeList(headnode);//headnode 매개변수로 freeList 함수 호출하여 할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q 대소문자 입력 받기 전까지 반복

	return 1;
}


int initialize(listNode** h) 
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)//포인터 h가 NULL이 아니라면
		freeList(*h);//할당된 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));//포인터 h listNode의 크기만큼 메모리 할당
	(*h)->rlink = *h;//포인터 h의 rlink에 포인터h 할당
	(*h)->llink = *h;//포인터 h의 llink에 포인터 h 할당
	(*h)->key = -9999;//포인터 h의 key에 -9999로 초기화
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h)
{
	if(h->rlink==h)//h의 rlink가 h일 때
	{
		free(h);//h에 할당된 메모리 해제
		return 0;
	}
	listNode*p =h->rlink;//listNode형 포인터 p에 h의 rlink 할당
	listNode*prev=NULL; //listNode형 포인터 prev NULL로 초기화
	while(p!=NULL && p!=h)//p가 NULL and p가 h가 아닐 동안 반복
	{
		prev=p;//prev에 p 할당
		p=p->rlink;//p에 p의 rlink 할당
		free(prev);//prev에 할당된 메모리 해제
	}
	free(h);//h에 할당된 메모리 해제
	
	return 0;
}



void printList(listNode* h) 
{
	int i = 0;//int형 변수 i 0으로 초기화
	listNode* p;//listNode포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//h가 NULL이라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//p에 h의 rlink 할당

	while(p != NULL && p != h) {//p가 NULL이 아니고 and p가 h가 아닐 동안 반복
		printf("[ [%d]=%d ] ", i, p->key);//p의 key를 통해 저장된 값들 출력
		p = p->rlink;//p에 p의 rlink 할당
		i++;//i 값 1 증가
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;//i에 0값 할당
	p = h->rlink;//p에 h의 rlink값 할당
	while(p != NULL && p != h){//p가 NULL아 아니고 and p가 h가 아닐동안 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);////p의 key , p의 llink, p의 rlink 출력
		p = p->rlink;//p에 p의 rlink 값 할당
		i++;//i 값 1 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) 
{
	if(h==NULL)//h가 NULL이라면
	return -1;

	listNode*node=(listNode*)malloc(sizeof(listNode));//listNode형 포인터 node에 listNode의 크기만큼 메모리 할당
	node->key=key;//node의 key에 key 값 할당
	node->rlink=NULL;//node의 rlink NULL로 초기화
	node->llink=NULL;//node의 llink NULL로 초기화

	if(h->rlink=h)//h의 rlink가 h 이라면
	{
		h->rlink=node;//h의 rlink에 node 저장
		h->llink=node;//h의 llink에 node 저장
		node->rlink=h;//node의 rlink에 h 저장
		node->llink=h;//node의 llink에 h 저장

	}
	else
	{
		h->llink->rlink=node;//h의 llink의 rlink에 node 저장
		node->llink=h->llink;//node의 llink에 h의 llink 저장
		h->llink=node;//h의 llink에 node 저장
		node->rlink=h;//node의 rlink에 h 저장
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) 
{
	if(h->llink==h||h==NULL)//h의 llink가 h or h가 NULL이라면
	{
		printf("nothing to delete\n");//삭제할 것이 없다고 출력
		return 1;
	}

	listNode*noderemove=h->llink;//listNode의 포인터 noderomve에 h의 llink 할당
	noderemove->llink->rlink=h;//noderemove의 llink의 rlink에 h 저장
	h->llink=noderemove->llink;//h의 llink에 noderemove의 llink 저장
	free(noderemove);//noderemove에 할당된 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) 
{
	listNode*node=(listNode*)malloc(sizeof(listNode));//listNode의 포인터 node에 listNode의 크기만큼 메모리 할당
	node->key=key;//node의 key에 key 값 할당
	node->rlink=NULL;//node의 rlink NULL로 초기화
	node->llink=NULL;//node의 llink NULL로 초기화

	node->rlink=h->rlink;//node의 rlink에 h의 rlink 값 할당
	h->rlink->llink=node;//h의 rlink의 llink에 node저장
	node->llink=h;//node의 llink 에 h 저장
	h->rlink=node;	//h의 rlink에 node 저장

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) 
{
	if(h == NULL || h->rlink == h)//h가 NULL or h의 rlink가 h 이라면 
	{
		printf("nothing to delete\n");//삭제할 것이 없다고 출력
		return 0;
	}
	
	listNode*nodereomve=h->rlink;//listNode의 포인터  noderemove에 h의 rlink 값 할당
	nodereomve->rlink->llink=h;//noderemove의 rlink의 llink에 h 저장
	h->rlink=nodereomve->rlink;//h의 rlink에 noderemove의 rlink 값 할당

	free(nodereomve);//noderemove에 할당된 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) 
{
	if(h->rlink==h || h==NULL)//h의 rlink가 h or h가 NULL이라면
	{
		printf("nothing to invert\n");//재배치할 것이 없다고 출력
		return 0;
	}

	listNode*n=h->rlink;//listNode형 포인터 n에 h의 rlink 값 할당
	listNode*trail=h;//listNode형 포인터 trail에 h값 할당
	listNode*middle=h;//listNode형 포인터 middle에 h값 할당 

	h->llink=h->rlink;//h의 llink에 h의 rlink 값 할당
	
	while(n!=NULL && n!=h)//n이 NULL이 아니고 and n이 h가 아닐동안 반복
	{
		trail=middle;//trail에 middle 값 할당
		middle=n;//middle에 n값 할당
		n=n->rlink;//n에 n의 rlink값 할당
		middle->rlink=trail; //middle의 rlink에 trail 값 할당
		middle->llink=n;//middle의 llink에 n값 할당
	}

	h->rlink=middle;//h의 rlink에 middle값 할당

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) 
{
	if(h==NULL)//h가 NULL이라면
	return -1;

	listNode*node=(listNode*)malloc(sizeof(listNode));//listNode형 포인터 node에 listNode의 크기만큼 메모리 할당
	node->key=key;//node의 key에 key 값 할당
	node->llink=node->rlink=NULL;//node의 llink, node의 rlink를 NULL로 초기화

	if(h->rlink!=NULL)//h의 rlink가 NULL이 아니라면
	{
		insertFirst(h,key);//h와 key를 매개변수로 insertNode 함수 호출하여 첫번째 노드에 key값 삽입
		return 1;
	}

	listNode*n=h->rlink;//listNode형 포인터 n에 h의 rlink값 할당
	while(n!=NULL && n!=h)//n이 NULL이 아니다 and n이 h가 아닐동안 반복
	{
		if(n->key >=key)//n의 key가 key값 보다 크거나 같을 동안
		{
			if(n==h->rlink)//n이 h의 rlink가 같다면
			{
				insertFirst(h,key);//h,key를 매개변수로 insertFirst함수 호출하여 첫번째 노드에 key값 삽입
			}
			else
			{
				node->rlink=n;//node의 rlink에 n값 할당
				node->llink=n->llink;//node의 llink에 n의 llink값 할당
				n->llink->rlink=node;//n의 llink의 rlink에 node값 할당
				n->llink=node;//n의 llink에 node 저장

			}
		}
	}
	// 마지막 노드까지 찾지 못했을 때 마지막에 삽입
	insertLast(h,key);//h와 key를 매개변수로 insertLast함수 호출하여 list의 마지막에 key값 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) 
{
	if(h->rlink==h || h ==NULL)//h의 rlink가 h or h가 NULL 이라면
	{
		printf("nothing to delete\n");//삭제할 것이 없다고 출력
		return 0;
	}

	listNode*n=h->rlink;//listNode형 포인터 n에 h의 rlink 값 할당

	while(n!=NULL && n!=h)//n이 NULL이 아니다 and n이 h가 아닐 동안 반복
	{
		if(n->key == key)//n의 key가 key와 같다면
		{
			if(n == h->rlink)//n이 h의 rlink와 같다면
			{
				deleteFirst(h);//h를 매개변수로 deleteFirst함수 호출하여 첫번째 노드 삭제
			}
			else if(n->rlink == h)//n의 rlink와 h가 같다면
			{	
				deleteLast(h);//h를 매개변수로 deleteLast함수 호출하여 마지막 노드 삭제
			}
			else
			{
				n->llink->rlink=n->rlink;//n의 llink의 rlink에 n의 rlink 값 할당
				n->rlink->llink=n->llink;//n의 rlink의 llink에 n의 llink 값 할당
				free(n);//n에 할당된 메모리 해제
			}
			return 0;
		}
		n=n->rlink;//n에 n의 rlink 값 할당
	}

	printf("can't find the node for key = %d\n",key);//찾지 못했다면, key값에 해당하는 node를 찾지못했다고 출력
	return 0;
}


