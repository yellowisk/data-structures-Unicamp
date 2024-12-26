#include <stdio.h>
#include <stdlib.h>
#include "expression.h"

void freeTree(p_node root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printTree(p_node root) {
    if (!root) return;
    if (root->left) {
        if (root->op == '|' || root->op == '&') {
            printf("(");
        }
        printTree(root->left);
    }
    printf("%c", root->op);
    if (root->right) {
        printTree(root->right);
        if (root->op == '|' || root->op == '&') {
            printf(")");
        }
    }
}

p_node createNode(p_node left, char op, p_node right) {
    p_node node = (p_node) malloc(sizeof(struct node));
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

char readChar(char **expression) {
    /* Basically, I get the char from the expression and 
    increment its pointer to the next char so that it's 
    skipped 'globally'. */
    char c = **expression;
    (*expression)++;
    return c;
}

p_node readTree(char **expression) {
    char c = readChar(expression);
    /* Using recurision, I create the whole tree based on the expression. */
    if (c == '(') {
        /* 
        If the function reads a '(' char, it calls itself and goes for identifying 
        what inside it. 
        */
        p_node left = readTree(expression);
        char op = readChar(expression);
        p_node right = readTree(expression);
        p_node node = createNode(left, op, right);
        readChar(expression);
        return node;
    } else if (c == '!' || c == '&' || c == '|') {
        /*
        If the function reads a char that is a '!', '&' or '|', it creates a new node.
        If the char is a '!' the left node is set to NULL so that it is guaranteed that
        the continuation of the tree at this point is to the right.
        Otherwise, the left node read normally.
        */
        p_node left = (c != '!') ? readTree(expression) : NULL;
        p_node right = readTree(expression);
        return createNode(left, c, right);
    } else {
        /*
        If the function reads a char that is not a '(', probably a random letter or 
        T or F, it creates a node with the char as the right node and returns it.
        */
        return createNode(NULL, c, NULL);
    }
    return NULL;
}

p_node removeDoubleExclamation(p_node root) {
    /* 
    Gets the first node after the double negation,
    destroys the double negation and returns the node
    that was gotten. Lesgooo!!!
    */
    if (!root) return NULL;

    p_node newRoot = root->right->right;
    free(root->right);
    free(root);
    return newRoot;
}

p_node moveNegationFromConstOrVars(p_node root) {
    /*
    First, this function gets the format of the option. Then, it negates the left and right
    by creating sorta intermeaditae nodes. These, negate the left and right nodes of the
    node that was formatted. Then, well, the former root node is destroyed and the new
    one with the negations moded is returned.
    */
    char newOption = (root->right->op == '|') ? '&' : '|';
    p_node leftNegation = createNode(NULL, '!', root->right->left);
    p_node rightNegation = createNode(NULL, '!', root->right->right);
    p_node newRoot = createNode(leftNegation, newOption, rightNegation);
    free(root->right);
    free(root);
    return newRoot;
}

p_node DeMorgan(p_node root) {
    if (!root) return NULL;

    root->left = DeMorgan(root->left);
    root->right = DeMorgan(root->right);

    if (root->op == '!' && root->right) {
        // !!exp -> exp
        if (root->right->op == '!') {
            /* After removing any possible double exclamation,
            DeMorgan is reapplied to ensure everything is fully correct!!!*/
            return DeMorgan(removeDoubleExclamation(root));
        }

        // !(exp1 | exp2) -> (!exp1 & !exp2)
        // !(exp1 & exp2) -> (!exp1 | !exp2)
        if (root->right->op == '|' || root->right->op == '&') {
            /* After moving 'em negations,
            DeMorgan is reapplied just like in the above if...
            */
            return DeMorgan(moveNegationFromConstOrVars(root));
        }
    }

    return root;
}

int isEqual(p_node subtree1, p_node subtree2) {
    if (!subtree1 && !subtree2) return 1;
    if (!subtree1 || !subtree2) return 0;
    if (subtree1->op != subtree2->op) return 0;

    if (isEqual(subtree1->left, subtree2->left) && isEqual(subtree1->right, subtree2->right)) {
        return 1;
    } else if (isEqual(subtree1->left, subtree2->right) && isEqual(subtree1->right, subtree2->left)) {
        return 1;
    }
    return 0;
}

p_node simplify(p_node root) {
    if (!root) return NULL;

    root->left = (root->left) ? simplify(root->left) : NULL;
    root->right = (root->right) ? simplify(root->right) : NULL;

    if (root->op == '&') {
        // handles the case: T & exp -> exp
        if ((root->left && root->left->op == 'T') || (root->right && root->right->op == 'T')) {
            p_node newRoot = ((root->left && root->left->op == 'T') ? root->right : root->left);
            freeTree((root->left && root->left->op == 'T') ? root->left : root->right);
            free(root);
            return simplify(newRoot);
        }

        // handles the case: F & exp -> F
        if ((root->right && root->right->op == 'F') || (root->left && root->left->op == 'F')) {
            freeTree(root);
            return createNode(NULL, 'F', NULL);
        }
    } else if (root->op == '|' && root->left && root->right) {
        // handles the case: T | exp -> T
        if (root->left->op == 'T' || root->right->op == 'T') {
            freeTree(root);
            return createNode(NULL, 'T', NULL);
        }

        // handels the case: F | exp -> exp
        if (root->left->op == 'F' || root->right->op == 'F') {
            p_node newRoot = (root->left->op == 'F') ? root->right : root->left;
            free((root->left->op == 'F') ? root->left : root->right);
            free(root);
            return simplify(newRoot);
        }
    } else if (root->op == '!') {
        //handles the case: !T -> F
        if (root->right) {
            if (root->right->op == 'T' || root->right->op == 'F') {
                p_node newNode = createNode(NULL, (root->right->op == 'T') ? 'F' : 'T', NULL);
                freeTree(root);
                return newNode;
            }
        }

        // handles the case: !F -> T
        if (root->left) {
            if (root->left->op == 'T' || root->left->op == 'F') {
                p_node newNode = createNode(NULL, (root->left->op == 'T') ? 'F' : 'T', NULL);
                freeTree(root);
                return newNode;
            }
        }
    }

    if (isEqual(root->left, root->right) && root->left && root->right) {
        /* 
        After all the simplification, I try to check if the two
        leaves of the tree are equal... If so, I return the 
        left leave to set it in the calling variable (either 
        root->left or root->right) at the start of the funtion...
        */
        freeTree(root->right);
        p_node rootLeft = root->left;
        free(root);
        return rootLeft;
    }

    return root;
}