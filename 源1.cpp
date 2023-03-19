#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<conio.h>

// ���嵥����ڵ���������,�����������Ϳ�����������
typedef int Element;//��ǰΪint
typedef struct node {
    Element el;          // �洢�ڵ�ɸ�����
    struct node* next;  // �洢��һ�ڵ��ַ
}Node;

// ���嵥��������
typedef struct LinkedList {
    Node* head;      // �洢����ͷ�ڵ�
    Node* tail;      // �洢����β�ڵ�
    int size;        // �洢����ڵ���
}LinkedList;

// ��ʼ������
void initList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
// ������β����ӽڵ������
void add(LinkedList* list, Element el) {//����ͷָ�����Ҫ��ӵ�����
    // �����½ڵ�
    Node* node = (Node*)malloc(sizeof(Node));
    node->el = el;
    node->next = NULL;//���½�ָ����ֵNULL

    if (list->head == NULL) {   // ����Ϊ�գ��½ڵ���ͷ�ڵ㣬���Դ�Ϊ�½��ڵ�
        list->head = node;
    }
    else {                    // ����Ϊ�գ����½ڵ���ӵ�β��
        list->tail->next = node;
    }

    list->tail = node;//���¼���������ָ�븳ֵ��¼
    list->size++;//�ڵ�����1
}
//�����˵�
void Menu()
{
    printf("\n=========[��������˵�]============\n");
    printf("[A/a]��ż�ڵ��滻\n");
    printf("[B/b]Ѱ���м�ڵ�\n");
    printf("[C/c]�ж������Ƿ�ɻ�\n");
    printf("[D/d]��ת����\n");
    printf("[�ո�]-�˳�\n");
    printf("=================================\n");
}
//���������������ۿ������Ƿ���ȷ
void printList(LinkedList* list) {
    Node* p = list->head;

    printf("\nList: ");
    while (p != NULL) {
        printf("%d ", p->el);//������������޸ģ����Լ����壬�˴�Ϊint
        p = p->next;
    }
    printf("\n��ǰ�ڵ���Ϊ��\n%d\n", list->size);
}
//�б������Ƿ�ɻ����������ÿ���ָ�뷨ʵ��
int Ring(LinkedList* list) {
    Node*q,* p = list->head;
    q = p;
    if (p == NULL) {
        printf("\n����Ϊ�գ��޷�����\n");
        return 0;
    }
    while(1) {
        for (int i=0;i<2;i++) {         //����p�ƶ��ٶ���q������
            p = p->next;
            if (p == NULL) {            //���p��null����˵���������β�������ɻ�
                printf("\n�������ɻ�\n");
                return 0;
            }
            if (p == q) {               //���q==p����˵������ɻ�
                printf("\n������ɻ�\n");
                return 1;
            }
        }
        q = q->next;
    }
}
//���������м�ڵ㣬����������м�ڵ�����
void Middle(LinkedList* list) {
    int i;
    Node* q, * p = list->head;
    q = p; 
    if (p == NULL) {
        printf("\n����Ϊ�գ��޷�����\n");
        return;
    }
    if (Ring(list)) {
        printf("\n������ɻ������Բ������м�ڵ�\n");              //�ж������Ƿ�ɻ�
        return;
    }
    if (list->size % 2 == 0) {
        printf("\n�ýڵ���Ϊ˫��n�����Է��ؽڵ�����Ϊ��n/2λ\n");  //��֪�������ʱ�����
    }
    while (p!=NULL) {
        for (i = 0; i < 2; i++) {            //����p�ƶ��ٶ���q������
            p = p->next;
            if (p == NULL)break;             //��p���Ͷ˾�ֹͣѭ��
        }
        if (i != 1)q = q->next;              //ѡ���Խ���q�����һ���Ƿ�ǰ��
    }
    printf("%d", q->el);                     //����е�����
}
//��ת����
void Turn (LinkedList* list) {
    Node*o=NULL,* q=NULL, * p=NULL;         //��ΪҪ��������ָ�룬���Լ���һ��ָ�����  o

    p = list->head;                        //ת������ͷĩ�ڵ������
    list->head = list->tail;
    list->tail = p;

    if (p == NULL) {
        printf("\n����Ϊ�գ��޷�����\n");            //��������
        return;
    }

    while (p!=NULL) {
        o = p->next;
        p->next = q;
        q = p;
        p = o;
    }
    printf("\n�Ѿ��ɹ���ת����\n");
    printList(list);
}
//��ż�滻
void Parity (LinkedList* list) {
    Node* o = NULL, * q = NULL, * p = list->head;                   //��ΪҪ��������ָ�룬���Լ���һ��ָ�����  o

    if (p == NULL||p->next==NULL) {
        printf("\n����Ϊ�ջ�ֻ��һ���ڵ㣬�޷�����\n");            //��������
        return;
    }
    list->head = p->next;                                         //�Ȱ�ͷ���洢�ĵ�ַ����
    o = p->next->next;                                           //ÿ��ָ�붼վһ��λ�ã�һ������Ӱ���ĸ�λ��
    p->next->next = p;
    p->next = o;
    q = o->next;
    while (1) {
        p->next = q;
        o->next = q->next;
        q->next = o;
        if (o->next == NULL||o->next->next==NULL)break;//���������һ��Ԫ��ʱ����������ѭ����Ҳ�ǻ�λ���
        p = o;                                         //��������ƶ�һ��Ԫ��
        o = o->next;                                  //��Ϊǰ���Ѿ���λ��ԭ��ֻ���ƶ�һλ���
        q = o->next;
    }

    printf("\n�Ѿ��ɹ�ʵ�����ݽڵ���ż����\n");
    printList(list);                                //���һ��ȷ�������Ƿ���ȷ
}
// ������
int main() {
    LinkedList list;

    initList(&list);        // ��ʼ������

    for (int i = 1; i < 8; i++) {
        add(&list, i);
    }                        // ��ӳ�ʼ�ڵ�

    printList(&list);       // ��ӡ��ʼ����

    printf("\n�������Ѿ��������ݣ�������ʾ���������һ������\n");
    char c = '0';
    do
    {
        Menu();
        printf("\n��ѡ������Ҫ�Ĳ���\n");
        switch (c = _getch())
        {
        case 'A':
        case 'a':Parity(&list);         //��ż�滻
            break;
        case 'B':
        case 'b':Middle(&list);        //�����м�ڵ�
            break;
        case 'C':
        case 'c':Ring(&list);         //�ж��Ƿ�ɻ�
            break;
        case 'D':
        case 'd':Turn(&list);        //��ת����
            break;
        }
    } while (c != ' ');

    return 0;
}