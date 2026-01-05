#include <stdio.h>
#include <stdlib.h>

/*======================
  Cau truc NODE
======================*/
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/*======================
  KHAI BÁO HÀM
======================*/
Node* createNode(int x);
void pushFront(Node **head, int x);
void printList(Node *head);
void freeList(Node **head);

/* Các thuat toan sap xep */
void bubbleSort(Node *head);
void insertionSort(Node **head);
void selectionSort(Node *head);
void mergeSort(Node **head);
void quickSort(Node **head);
/* Hàm ho tro */
void sortedInsert(Node **sorted, Node *newNode);
void frontBackSplit(Node *source, Node **front, Node **back);
Node* sortedMerge(Node *a, Node *b);
Node* getTail(Node *cur);
Node* partition(Node *head, Node *end, Node **newHead, Node **newEnd);
Node* quickSortRecur(Node *head, Node *end);

/*======================
  ÐiNH NGHiA HÀM
======================*/
Node* createNode(int x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

void pushFront(Node **head, int x) {
    Node* p = createNode(x);
    p->next = *head;
    *head = p;
}

void printList(Node *head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node **head) {
    Node *tmp;
    while (*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

/*======================
  BUBBLE SORT
======================*/
void bubbleSort(Node *head) {
    if (!head)
	 return;
    int swapped;
    Node *p, *lptr = NULL;

    do {
        swapped = 0;
        p = head;
        while (p->next != lptr) {
            if (p->data > p->next->data) {
                int t = p->data;
                p->data = p->next->data;
                p->next->data = t;
                swapped = 1;
            }
            p = p->next;
        }
        lptr = p;
    } while (swapped);
}

/*======================
  INSERTION SORT
======================*/
void sortedInsert(Node **sorted, Node *newNode) {
    if (*sorted == NULL || (*sorted)->data >= newNode->data) {
        newNode->next = *sorted;
        *sorted = newNode;
    } else {
        Node *cur = *sorted;
        while (cur->next && cur->next->data < newNode->data)
            cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

void insertionSort(Node **head) {
    Node *sorted = NULL;
    Node *cur = *head;

    while (cur) {
        Node *next = cur->next;
        sortedInsert(&sorted, cur);
        cur = next;
    }
    *head = sorted;
}
/*======================
  SELECTION SORT
======================*/
void selectionSort(Node *head) {
    Node *i, *j, *min;
    for (i = head; i != NULL; i = i->next) {
        min = i;

        for (j = i->next; j != NULL; j = j->next) {
            if (j->data < min->data) {
                min = j;
            }
        }
        if (min != i) {
            int temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
    }
}

/*======================
  MERGE SORT
======================*/
void frontBackSplit(Node *source, Node **front, Node **back) {
    Node *slow = source, *fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Node* sortedMerge(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}

void mergeSort(Node **head) {
    if (!*head || !(*head)->next) 
	return;
    Node *a, *b;
    frontBackSplit(*head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *head = sortedMerge(a, b);
}

/*======================
  QUICK SORT
======================*/
Node* getTail(Node *cur) {
    while (cur && cur->next)
        cur = cur->next;
    return cur;
}

Node* partition(Node *head, Node *end, Node **newHead, Node **newEnd) {
    Node *pivot = end;
    Node *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if (*newHead == NULL)
                *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if (*newHead == NULL)
        *newHead = pivot;

    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node *head, Node *end) {
    if (!head || head == end)
        return head;

    Node *newHead = NULL, *newEnd = NULL;
    Node *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);
        getTail(newHead)->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSort(Node **head) {
    *head = quickSortRecur(*head, getTail(*head));
}
/*======================
  MENU
======================*/
void menu() {
    printf("\n===== MENU SAP XEP =====\n");
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Quick Sort\n");
    printf("0. Thoat\n");
    printf("========================\n");
    printf("Chon thuat toan: ");
}

/*======================
  MAIN
======================*/
int main() {
    int choice, n, x;
    Node *head = NULL;
int i;              // them  

    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    for ( i = 0; i < n; i++) {
        printf("Nhap phan tu %d: ", i + 1);
        scanf("%d", &x);
        pushFront(&head, x);
    }

    printf("\nDanh sach ban dau:\n");
    printList(head);

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bubbleSort(head);
                break;
            case 2:
                insertionSort(&head);
                break;
             case 3:
  			    selectionSort(head);
  			    break;
            case 4:
                mergeSort(&head);
                break;
            case 5:
                quickSort(&head);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }

        if (choice >= 1 && choice <= 5) {
            printf("Danh sach sau sap xep:\n");
            printList(head);	
        }

    } while (choice != 0);

    freeList(&head);
    return 0;
}

