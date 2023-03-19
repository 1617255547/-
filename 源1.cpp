#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<conio.h>

// 定义单链表节点数据类型,更换数据类型可以自行输入
typedef int Element;//当前为int
typedef struct node {
    Element el;          // 存储节点可改数据
    struct node* next;  // 存储下一节点地址
}Node;

// 定义单链表类型
typedef struct LinkedList {
    Node* head;      // 存储链表头节点
    Node* tail;      // 存储链表尾节点
    int size;        // 存储链表节点数
}LinkedList;

// 初始化链表
void initList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
// 在链表尾部添加节点和数据
void add(LinkedList* list, Element el) {//输入头指针和需要添加的数据
    // 创建新节点
    Node* node = (Node*)malloc(sizeof(Node));
    node->el = el;
    node->next = NULL;//将新建指针域赋值NULL

    if (list->head == NULL) {   // 链表为空，新节点是头节点，则以此为新建节点
        list->head = node;
    }
    else {                    // 链表不为空，则将新节点添加到尾部
        list->tail->next = node;
    }

    list->tail = node;//将新加数据链表指针赋值记录
    list->size++;//节点数加1
}
//操作菜单
void Menu()
{
    printf("\n=========[链表操作菜单]============\n");
    printf("[A/a]奇偶节点替换\n");
    printf("[B/b]寻找中间节点\n");
    printf("[C/c]判断链表是否成环\n");
    printf("[D/d]翻转链表\n");
    printf("[空格]-退出\n");
    printf("=================================\n");
}
//输出链表函数，方便观看操作是否正确
void printList(LinkedList* list) {
    Node* p = list->head;

    printf("\nList: ");
    while (p != NULL) {
        printf("%d ", p->el);//输出类型自行修改，由自己定义，此处为int
        p = p->next;
    }
    printf("\n当前节点数为：\n%d\n", list->size);
}
//判别链表是否成环函数，利用快慢指针法实现
int Ring(LinkedList* list) {
    Node*q,* p = list->head;
    q = p;
    if (p == NULL) {
        printf("\n链表为空，无法操作\n");
        return 0;
    }
    while(1) {
        for (int i=0;i<2;i++) {         //设置p移动速度是q的两倍
            p = p->next;
            if (p == NULL) {            //如果p是null，则说明链表存在尾部，不成环
                printf("\n该链表不成环\n");
                return 0;
            }
            if (p == q) {               //如果q==p，则说明链表成环
                printf("\n该链表成环\n");
                return 1;
            }
        }
        q = q->next;
    }
}
//查找链表中间节点，并返回输出中间节点数据
void Middle(LinkedList* list) {
    int i;
    Node* q, * p = list->head;
    q = p; 
    if (p == NULL) {
        printf("\n链表为空，无法操作\n");
        return;
    }
    if (Ring(list)) {
        printf("\n该链表成环，所以不存在中间节点\n");              //判断链表是否成环
        return;
    }
    if (list->size % 2 == 0) {
        printf("\n该节点数为双数n，所以返回节点数据为第n/2位\n");  //告知特殊情况时的输出
    }
    while (p!=NULL) {
        for (i = 0; i < 2; i++) {            //设置p移动速度是q的两倍
            p = p->next;
            if (p == NULL)break;             //当p到低端就停止循环
        }
        if (i != 1)q = q->next;              //选择性进行q的最后一步是否前进
    }
    printf("%d", q->el);                     //输出中点数据
}
//翻转链表
void Turn (LinkedList* list) {
    Node*o=NULL,* q=NULL, * p=NULL;         //因为要利用三个指针，所以加了一个指针变量  o

    p = list->head;                        //转换储存头末节点的数据
    list->head = list->tail;
    list->tail = p;

    if (p == NULL) {
        printf("\n链表为空，无法操作\n");            //正常检索
        return;
    }

    while (p!=NULL) {
        o = p->next;
        p->next = q;
        q = p;
        p = o;
    }
    printf("\n已经成功翻转链表\n");
    printList(list);
}
//奇偶替换
void Parity (LinkedList* list) {
    Node* o = NULL, * q = NULL, * p = list->head;                   //因为要利用三个指针，所以加了一个指针变量  o

    if (p == NULL||p->next==NULL) {
        printf("\n链表为空或只有一个节点，无法操作\n");            //正常检索
        return;
    }
    list->head = p->next;                                         //先把头结点存储的地址更换
    o = p->next->next;                                           //每个指针都站一个位置，一共可以影响四个位置
    p->next->next = p;
    p->next = o;
    q = o->next;
    while (1) {
        p->next = q;
        o->next = q->next;
        q->next = o;
        if (o->next == NULL||o->next->next==NULL)break;//当遇到最后一个元素时，立刻跳出循环，也是换位完成
        p = o;                                         //集体向后移动一个元素
        o = o->next;                                  //因为前面已经换位的原因，只是移动一位便可
        q = o->next;
    }

    printf("\n已经成功实现数据节点奇偶互换\n");
    printList(list);                                //输出一次确认数据是否正确
}
// 主函数
int main() {
    LinkedList list;

    initList(&list);        // 初始化链表

    for (int i = 1; i < 8; i++) {
        add(&list, i);
    }                        // 添加初始节点

    printList(&list);       // 打印初始链表

    printf("\n链表本身已经存在数据，如上所示，请进行下一步操作\n");
    char c = '0';
    do
    {
        Menu();
        printf("\n请选择你需要的操作\n");
        switch (c = _getch())
        {
        case 'A':
        case 'a':Parity(&list);         //奇偶替换
            break;
        case 'B':
        case 'b':Middle(&list);        //查找中间节点
            break;
        case 'C':
        case 'c':Ring(&list);         //判断是否成环
            break;
        case 'D':
        case 'd':Turn(&list);        //翻转链表
            break;
        }
    } while (c != ' ');

    return 0;
}