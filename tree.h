#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_DEGREE 3

typedef struct {
    int num;
    char type[50];
    char brand[50];
    char color[20];
    struct {
        int day;
        int month;
        int year;
    } insp_date;
    union {
        char company_id[20];
        struct {
            char first_name[30];
            char last_name[30];
        } owner_name;
    } owner;
} Equip;

void input(Equip *e);
void display(const Equip *e);
void displayMenu();
int max(int a, int b);

// Структура узла АВЛ-дерева
typedef struct AVLNode {
    Equip data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

AVLNode* createAVLTree();
int getHeight(AVLNode* node);
AVLNode* rotateRight(AVLNode* node);
AVLNode* rotateLeft(AVLNode* node);
AVLNode* insertAVLNode(AVLNode* node, Equip data);
void displayAVLTree(AVLNode* root);
AVLNode* searchAVLTree(AVLNode* root, int value);
AVLNode* deleteAVLNode(AVLNode* root, int value);

// Структура узла B-дерева
typedef struct BNode {
    int count;
    Equip data[MAX_DEGREE];
    struct BNode* children[MAX_DEGREE + 1];
} BNode;

BNode* createBTree();
void splitChild(BNode* parent, int childIndex, BNode* child);
BNode* insertBNode(BNode* root, Equip data);
BNode* deleteBNode(BNode* root, int value);
void displayBTree(BNode* root);
BNode* searchBTree(BNode* root, int value);


// Структура узла B+-дерева
typedef struct BPlusNode {
    int count;
    Equip data[MAX_DEGREE];
    struct BPlusNode* children[MAX_DEGREE + 1];
    bool isLeaf;
} BPlusNode;

BPlusNode* createBPlusTree();
void splitChildBPlus(BPlusNode* parent, int childIndex, BPlusNode* child);
BPlusNode* insertBPlusNode(BPlusNode* root, Equip data);
BPlusNode* deleteBPlusNode(BPlusNode* root, int value);
void displayBPlusTree(BPlusNode* root);
BPlusNode* searchBPlusTree(BPlusNode* root, int value);


#endif