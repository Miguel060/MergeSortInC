#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void split(Node* head, Node** front, Node** back) {
    Node* fast;
    Node* slow;
    slow = head;
    fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

Node* merge(Node* front, Node* back) {
    Node* result = NULL;

    if (front == NULL) return back;
    if (back == NULL) return front;

    if (front->data <= back->data) {
        result = front;
        result->next = merge(front->next, back);
    } else {
        result = back;
        result->next = merge(front, back->next);
    }

    return result;
}

void mergeSort(Node** head) {
    Node* front;
    Node* back;

    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    split(*head, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *head = merge(front, back);
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = newNode(38);
    head->next = newNode(27);
    head->next->next = newNode(43);
    head->next->next->next = newNode(3);
    head->next->next->next->next = newNode(9);
    head->next->next->next->next->next = newNode(82);
    head->next->next->next->next->next->next = newNode(10);

    printf("Lista original: ");
    printList(head);

    mergeSort(&head);

    printf("Lista ordenada: ");
    printList(head);

    return 0;
}
