#include "linked.h"
#include <stdlib.h>
#include <stdio.h>

p_node searchByIndex(p_node head, int index) {
    if (head == NULL || head->index == index) {
        return head;
    }
    return searchByIndex(head->next, index);
};

void printList(p_node head) {
    p_node current = head;
    for (current = head; current != NULL; current = current->next) {
        if (current->next != NULL) {
            printf("%c ", current->value);
            continue;
        }
        printf("%c\n", current->value);
    }
}

int get_len(p_node head) {
    int length = 0;
    p_node temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

void updateIndexes(p_node head) {
    p_node current = head;
    int index = 0;
    while (current != NULL) {
        current->index = index++;
        current = current->next;
    }
}

char removeNodeByIndex(p_node *head, int index) {
    char value;
    p_node toRemove = searchByIndex(*head, index);

    if (toRemove == *head) {
        value = (*head)->value;
        *head = (*head)->next;
        free(toRemove);
        updateIndexes(*head);
        return value;
    }

    p_node beforeToRemove = searchByIndex(*head, index - 1);
    value = toRemove->value;
    beforeToRemove->next = toRemove->next;
    free(toRemove);
    updateIndexes(*head);

    return value;
}

p_node createNode(char value, int index) {
    p_node newNode = (p_node) malloc(sizeof(struct node));
    newNode->index = index;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
};

void insertNodeAt(p_node *head, char value, int index) {
    /*
        NodeAt represents the Node in the position we want to insert a new node.
        NodeAt  will ultimately come after the newNode after we do all the process
        of insertion.
    */ 
    p_node newNode = createNode(value, index);
    p_node nodeAt = searchByIndex(*head, index);

    /* Inserts at the beginning and starts a Linked List if the head is null. */
    if (*head == NULL || index == 0) {
        newNode->next = nodeAt;
        *head = newNode;
        updateIndexes(*head);
        return;
    }

    /*
    Here, I have to make sure the node before the nodeAt points to the newNode,
    so that the linked list is correctly set.
    If nodeAt is NULL, it means I'm inseting at the end, otherwise I'm inserting 
    in the middle. :)
    */
    newNode->next = nodeAt;
    searchByIndex(*head, index - 1)->next = newNode;
    updateIndexes(*head);
    
    return;
}

void invertPrefix(p_node *head, int prefixLength) {
    p_node current = *head;
    p_node previous = NULL;
    p_node next = NULL;
    
    /* 
    Here I start printing the prefix while reversing it.
    To reverse it, I make the current node point to the previous node.
    Then, I make the previous node be the current node and the current node
    be the next node. In the first iteration, the first node of the prefix
    will point to a NULL macro, but later we'll connect it to the first
    node of the suffix.
    */
    printf("prefixo ");
    while (current != NULL && prefixLength > 0) {
        printf("%c ", current->value);
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
        prefixLength--;
    }

    /* printing only the prefix, after reversing */
    printf("-> ");
    printList(previous);

    // "head", now the end of the prefix, points to the first node of the suffix (current).
    if (*head != NULL) {
        (*head)->next = current;
    }
    *head = previous; // set head as the node at start of the reversed list

    updateIndexes(*head);
}

void invertSuffix(p_node *head, int suffixLength) {
    if (suffixLength <= 0) return; // This never happens, but it's a good practice to check, lol

    // Here I get the lenght of the prefix.
    int length = get_len(*head);
    int prefixLength = length - suffixLength;
    if (prefixLength < 0) {
        prefixLength = 0;
    }

    // Here I find the tail of the prefix so that I can connect the reversed suffix to it.
    p_node current = *head;
    p_node prefixTail = NULL;
    if (prefixLength > 0) {
        prefixTail = searchByIndex(*head, prefixLength - 1);
        current = prefixTail->next;
    }

    /* 
    Here I start printing the suffix while reversing it.
    To reverse it, I make the current node point to the previous node.
    Then, I make the previous node be the current node and the current node
    be the next node. In the first itration, the first node of the suffix
    will point to a NULL macro, so that the suffix ends there. :)
    */
    printf("sufixo ");
    p_node previous = NULL;
    p_node next = NULL;
    while (current != NULL) {
        printf("%c ", current->value);
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    /* \
    Printing only the suffix, after reversing.
    Here, wee start looping from "previous" because it's now the
    starting node of the suffix.
     */
    printf("-> ");
    printList(previous);

    /* Reconnects the reversed suffix with the prefix */
    if (prefixTail != NULL) {
        /* 
        The tail of the prefix now points to the head of the reversed suffix,
        which, again, is stored in the "previous" variable.
        */
        prefixTail->next = previous;
    } else {
        *head = previous;  // If there is no prefix, the reversed suffix becomes the head
    }

    /* Updating indexes again... */
    updateIndexes(*head);
}

void print_transpose(p_node head, int p, int q, int r) {
    printf("subsequencia ");
    p_node current = head;

    for (int i = 0; i < get_len(head); i++) {
        if (i >= p && i <= q) {
            printf("%c ",current->value);
            if (i > q) break;
        }
        current = current->next;
    }

    (r > 0) ? printf(">> %d\n", r) : printf("<< %d\n", -r);
}

void transpose(p_node *head, int p, int q, int r) {
    print_transpose(*head, p, q, r);
    p_node pNode = searchByIndex(*head, p);
    p_node qNode = searchByIndex(*head, q);
    p_node beforeP = searchByIndex(*head, p - 1);
    p_node afterQ = qNode->next;

    if (r > 0) {
    /*
    In this approach, I find the node that'll actually come
    before the pNode. Then, I make the qNode point to this 
    node's next node, so that the linked list continues.
    After that, if the pNode is the head, I make the head point
    to the afterQ node. Otherwise, I make the beforeP node point
    to the afterQ node.
    And that's it, with this approach all transpotions to the right
    end up working with this manipulation of where the pointers are
    poiting to.
    */
        int beforePos = q + r;
        p_node realBeforeP = searchByIndex(*head, beforePos); // if new_position <= last_position index
        
        qNode->next = realBeforeP->next;
        realBeforeP->next = pNode;
        if (p == 0) {
            *head = afterQ;
        } else {
            beforeP->next = afterQ;
        }
    } else {
    /*
    Here I do a similar process when it comes to changing where the
    nodes are pointing to. But, here, I find the node that'll come
    after the qNode (realAfterQ). If this node is the head, I know that the head
    will have to be the pNode and so I make it come true and,
    subsequentently, make the beforeP node point to the node after qNode
    and make qNode point to another node: the realAfterQ node.
    If the realAfterQ node is not the head, I make the node before pNode point
    to qNode's next node, so that the linked list continues. Then, I make
    qNode point to the realAfterQ node and make the node before realAfterQ
    point to pNode.
    */
        int afterPos = p + r;
        p_node realAfterQ = searchByIndex(*head, afterPos);
        if (realAfterQ->index == 0) {
            *head = pNode;
            beforeP->next = qNode->next;
            qNode->next = realAfterQ;
        } else {
            searchByIndex(*head, p - 1)->next = qNode->next;
            qNode->next = realAfterQ;
            beforeP = searchByIndex(*head, realAfterQ->index - 1);
            beforeP->next = pNode;
        }
    }

    updateIndexes(*head);
}

void destroyList(p_node head) {
    if (head != NULL) {
        destroyList(head->next);
        free(head);
    }
}