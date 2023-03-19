#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<conio.h>

// 定义双向链表节点数据类型,更换数据类型可以自行输入
typedef int Element;//当前为int
typedef struct node {
    struct node* front;
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
    node->front = NULL;
    node->next = NULL;//将新建指针域赋值NULL

    if (list->head == NULL) {   // 链表为空，新节点是头节点，则以此为新建节点
        list->head = node;
        node->front = NULL;
    }
    else {                    // 链表不为空，则将新节点添加到尾部
        node->front = list->tail;
        list->tail->next = node;
    }

    list->tail = node;//将新加数据链表指针赋值记录
    list->size++;//节点数加1
}

// 在链表中指定位置插入节点
void insert(LinkedList* list, int index, Element el) {
    if (index >= list->size) {  // index越界，直接添加到尾部
        add(list, el);
    }
    else {
        // 创建新节点
        Node* node = (Node*)malloc(sizeof(Node));
        node->el = el;
        node->front = NULL;
        node->next = NULL;

        Node* p = list->head;    // 指向头节点
        Node* q = NULL;         // 指向ptr前一个节点

        for (int i = 0; i < index-1; i++) {
            q = p;
            p = p->next;
        }

        if (q == NULL) {         // 插入位置为头节点
            node->next = p;
            list->head = node;
        }
        else {
            node->front = q;
            q->next = node;
            node->next = p;
        }

        list->size++;
    }
}

// 删除链表中指定位置节点并返回该节点数据
int removeNode(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {   // index越界
        printf("删除失败，节点数越界");//告知操作者删除情况
        return -1;  // 返回-1表示删除失败
    }
    else {
        
        Node* p = list->head;    // 指向头节点
        Node* q = NULL;         // 指向ptr前一个节点

        for (int i = 0; i < index-1; i++) {
            q = p;
            p = p->next;
        }

        if (q == NULL) {               // 删除头节点
            list->head = p->next;
            p->next->front = NULL;
        }
        else {
            q->next = p->next;
            p->next->front = q;
        }

        if (p == list->tail) {       // 删除尾节点
            list->tail = q;
        }

        int data = p->el;          // 获取待删除节点数据
        free(p);                  // 释放待删除节点
        list->size--;
        printf("\n%d\n",data);
        return data;    // 返回待删除节点数据
    }
}

// 获取链表指定位置节点数据
int get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {          // index越界，输出公告并返回-1
        printf("节点数越界，请输入正确的节点数");
        return -1;
    }
    else {
        Node* p = list->head;                       // 指向头节点

        for (int i = 0; i < index-1; i++) {
            p = p->next;
        }

        return p->el;                               // 返回指定位置节点数据
    }
}
//修改节点数据
void Modify(LinkedList* list, int index, Element el)
    {
    if (index < 0 || index >= list->size) {          // index越界，输出公告并返回-1
        printf("节点数越界，请输入正确的节点数");
        return;
    }
    else {
        Node* p = list->head;                       // 指向头节点
        for (int i = 0; i < index - 1; i++) {
            p = p->next;
        }
        p->el = el;
        printf("\n已修改完成\n");
        return;                               // 返回指定位置节点数据
    }
}
// 打印输出链表全部数据
void printList(LinkedList* list) {
    Node* p = list->head;

    printf("\nList: ");
    while (p != NULL) {
        printf("%d ", p->el);                    //输出类型自行修改，由自己定义，此处为int
        p = p->next;
    }
    printf("\n当前节点数为：\n%d\n", list->size);
}
//操作菜单
void Menu()
{
    printf("\n=========[单链表操作菜单]============\n");
    printf("[A/a]-打印链表\n");
    printf("[B/b]向尾部添加节点\n");
    printf("[C/c]在中间插入节点\n");
    printf("[D/d]删除节点\n");
    printf("[E/e]获取单个节点数据\n");
    printf("[F/f]修改节点数据\n");
    printf("[空格]-退出\n");
    printf("=================================\n");
}
// 主函数
int main() {
    LinkedList list;

    initList(&list);        // 初始化链表

    add(&list, 1);          // 添加节点
    add(&list, 2);
    add(&list, 3);
    add(&list, 4);
    add(&list, 5);

    printList(&list);       // 打印初始链表

    printf("\n链表本身已经存在数据，如上所示，请进行下一步操作\n");
    int i;
    Element el;            //存储输入节点数和数据，当链表数据
    char c = '0';
    do
    {
        printf("\n如果需要数据输入或查找,删除，请输入所需\n第几个节点数+空格+输入的数据+回车\n，不需使用的数据请请输入0\n");
        scanf_s("%d %d", &i, &el);                 //当链表数据类型发生变化时，此处需修改输入类型
        Menu();
        printf("\n请选择你需要的操作\n");
        switch (c = _getch())
        {
        case 'A':
        case 'a':printList(&list);            //输出链表
            break;
        case 'B':
        case 'b':add(&list, el);               //添加节点
            break;
        case 'C':
        case 'c':insert(&list, i, el);         //插入节点
            break;
        case 'D':
        case 'd':removeNode(&list, i);       // 删除节点
            break;
        case 'E':
        case 'e':printf("The %drd element is: %d\n\n", i, get(&list, 2));    // 获取节点数据
            break;
        case 'F':
        case 'f':Modify(&list, i, el);    // 获取节点数据
            break;
        }
    } while (c != ' ');

    return 0;
}