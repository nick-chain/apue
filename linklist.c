#include"linklist.h"
#include<stdlib.h>
#include<stdio.h>

List CreateList(){
    List H;
    H = (List)malloc(sizeof(LinkList));

    if(!H){
        printf("no enough memory\n");
        exit(-1);
    }
    
    H->Data = -1;
    H->Next = NULL;//具有头节点的链表

    return H;
}

void HeadInsertNode(List H,int Element){
    List ptr;

    ptr = (List)malloc(sizeof(LinkList));
    if(!ptr){
        printf("no enough memory\n");
        exit(-1);
    }
    ptr->Data = Element;

    ptr->Next = H->Next;
    H->Next = ptr;

}

List TailInsertNode(List H, int Element){
    List ptr,q;
    q = H;

    while(q->Next){
        q = q->Next;
    }
    ptr = (List)malloc(sizeof(LinkList));
    ptr ->Data = Element;
    
    ptr->Next = q->Next;
    q ->Next  = ptr;
    q = ptr;

    return H;
}

void PrintList(List H){
    List ptr=H->Next;

    while(ptr){
        printf("%d ",ptr->Data);
        ptr = ptr->Next;
    }
    printf("\n");
}

List FindKey(List H,int Key){
    int i=1;
    List p=H->Next;
    while(p!= NULL&&i<Key){
        p = p->Next;
        i++;
    }
    if(i == Key){
        return p;
    }
    else{
        return NULL;
    }
}

List FindElement(List H, int Element){
    List ptr=H->Next;
    
    while(ptr&&ptr->Data!=Element){
        ptr = ptr->Next;
    }

    return ptr;
}

List Insert(List H,int postion,int Element){
    List ptr,s;
    if(postion == 1){//在头节点出插入
        ptr = (List)malloc(sizeof(LinkList));
        ptr->Data = Element;
        ptr->Next = H->Next;
        H->Next = ptr;

        return H;
    }
    ptr = FindKey(H,postion-1);
    if(ptr == NULL){
        printf("postion illegal\n");
        return NULL;
    }
    else{
        s = (List)malloc(sizeof(LinkList));
        s->Data = Element;
        
        s->Next = ptr->Next;
        ptr->Next = s;
        ptr = s;
        return H;
    }       
}

int Delete(List H, int postion){
    List ptr = H->Next,s;

    if(postion == 1){//删除头节点
        H->Next = H->Next->Next;
        free(ptr);
        
        return 1;
    }

    ptr = FindKey(H,postion-1);
    if(ptr == NULL){
        return -1;
    }
    else if(ptr->Next == NULL){
        printf("postion is no xeasit");
        return -1;
    }
    else{
        s = ptr->Next;
        ptr->Next = s->Next;
        free(s);

        return 1;
    }
}

List ReverseList(List H){
    List p,q,t;

    p = H;
    q = NULL;
    while(p){
        t = p->Next;
        p->Next = q;
        q = p;
        p = t;
    }

    return q;
}

void Print(List H){
    List ptr=H;

    while(ptr->Next){
        printf("%d ",ptr->Data);
        ptr = ptr->Next;
    }
    printf("\n");
}
