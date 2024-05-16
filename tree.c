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

void input(Equip *e) {
    printf("Enter number: ");
    scanf("%d", &e->num);
    printf("Enter type: ");
    scanf("%s", e->type);
    printf("Enter brand: ");
    scanf("%s", e->brand);
    printf("Enter color: ");
    scanf("%s", e->color);
    printf("Enter last inspection date (day month year): ");
    scanf("%d %d %d", &e->insp_date.day, &e->insp_date.month, &e->insp_date.year);
    printf("Enter owner type (1 for company, 2 for individual): ");
    int owner_type;
    scanf("%d", &owner_type);
    if (owner_type == 1) {
        printf("Enter company ID: ");
        scanf("%s", e->owner.company_id);
    } else {
        printf("Enter owner's first name: ");
        scanf("%s", e->owner.owner_name.first_name);
        printf("Enter owner's last name: ");
        scanf("%s", e->owner.owner_name.last_name);
    }
}

void display(const Equip *e) {
    printf("Number: %d\n", e->num);
    printf("Type: %s\n", e->type);
    printf("Brand: %s\n", e->brand);
    printf("Color: %s\n", e->color);
    printf("Last inspection date: %d-%d-%d\n", e->insp_date.day, e->insp_date.month, e->insp_date.year);
    printf("Owner: ");
    if (isdigit(e->owner.company_id[0])) {
        printf("Company ID: %s\n", e->owner.company_id);
    } else {
        printf("Individual: %s %s\n", e->owner.owner_name.first_name, e->owner.owner_name.last_name);
    }
}

void displayMenu() {
    printf("Choose an option:\n");
    printf("1. AVL TREE operations\n");
    printf("2. B TREE operations\n");
    printf("3. B+ TREE operations\n");
    printf("4. Exit\n");
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Структура узла АВЛ-дерева
typedef struct AVLNode {
    Equip data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// Создание пустого АВЛ-дерева
AVLNode* createAVLTree() {
    return NULL;
}

// Получение высоты узла
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Балансировка АВЛ-дерева
AVLNode* rotateRight(AVLNode* node) {
    AVLNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(node));
    return leftChild;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    rightChild->height = 1 + max(getHeight(rightChild->right), getHeight(node));
    return rightChild;
}

// Вставка узла в АВЛ-дерево
AVLNode* insertAVLNode(AVLNode* node, Equip data) {
    if (node == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->data = data;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (data.num < node->data.num) {
        node->left = insertAVLNode(node->left, data);
    } else if (data.num > node->data.num) {
        node->right = insertAVLNode(node->right, data);
    } else {
        return node; // Дублирующий элемент, не вставляем
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getHeight(node->left) - getHeight(node->right);

    if (balanceFactor > 1 && data.num < node->left->data.num) {
        return rotateRight(node);
    }

    if (balanceFactor < -1 && data.num > node->right->data.num) {
        return rotateLeft(node);
    }

    if (balanceFactor > 1 && data.num > node->left->data.num) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1 && data.num < node->right->data.num) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Вывод АВЛ-дерева
void displayAVLTree(AVLNode* root) {
    if (root == NULL) {
        return;
    }
    displayAVLTree(root->left);
    display(&root->data);
    displayAVLTree(root->right);
}

// Поиск узла по значению
AVLNode* searchAVLTree(AVLNode* root, int value) {
    if (root == NULL || root->data.num == value) {
        return root;
    }
    if (value < root->data.num) {
        return searchAVLTree(root->left, value);
    } else {
        return searchAVLTree(root->right, value);
    }
}

// Удаление узла из АВЛ-дерева
AVLNode* deleteAVLNode(AVLNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data.num) {
        root->left = deleteAVLNode(root->left, value);
    } else if (value > root->data.num) {
        root->right = deleteAVLNode(root->right, value);
    } else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteAVLNode(root->right, temp->data.num);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getHeight(root->left) - getHeight(root->right);

    if (balanceFactor > 1 && getHeight(root->left) >= getHeight(root->right)) {
        return rotateRight(root);
    }

    if (balanceFactor > 1 && getHeight(root->left) < getHeight(root->right)) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balanceFactor < -1 && getHeight(root->right) >= getHeight(root->left)) {
        return rotateLeft(root);
    }

    if (balanceFactor < -1 && getHeight(root->right) < getHeight(root->left)) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Структура узла B-дерева
typedef struct BNode {
    int count; // Количество элементов в узле
    Equip data[MAX_DEGREE]; // Данные узла
    struct BNode* children[MAX_DEGREE + 1]; // Массив указателей на дочерние узлы
} BNode;

// Создание пустого B-дерева
BNode* createBTree() {
    BNode* root = (BNode*)malloc(sizeof(BNode));
    root->count = 0;
    for (int i = 0; i < MAX_DEGREE; i++) {
        root->children[i] = NULL;
    }
    return root;
}

// Разделение дочернего узла
void splitChild(BNode* parent, int childIndex, BNode* child) {
    BNode* newChild = (BNode*)malloc(sizeof(BNode));
    newChild->count = MAX_DEGREE / 2;
    parent->count++;

    for (int i = 0; i < MAX_DEGREE / 2; i++) {
        newChild->data[i] = child->data[i + MAX_DEGREE / 2];
    }

    if (child->count > MAX_DEGREE / 2) {
        for (int i = 0; i <= MAX_DEGREE / 2; i++) {
            newChild->children[i] = child->children[i + MAX_DEGREE / 2];
            child->children[i + MAX_DEGREE / 2] = NULL;
        }
    }

    for (int i = parent->count; i >= childIndex + 2; i--) {
        parent->children[i] = parent->children[i - 1];
    }

parent->children[childIndex + 1] = newChild;

for (int i = parent->count - 1; i >= childIndex; i--) {
parent->data[i + 1] = parent->data[i];
}

parent->data[childIndex] = child->data[MAX_DEGREE / 2];

child->count = MAX_DEGREE / 2;
}

// Вставка узла в B-дерево
BNode* insertBNode(BNode* root, Equip data) {
    if (root == NULL) {
        // Создание нового дерева
        root = (BNode*)malloc(sizeof(BNode));
        root->count = 1;
        root->data[0] = data;
        for (int i = 0; i <= MAX_DEGREE; i++) {
            root->children[i] = NULL;
        }
        return root;
    }

    // Если корень полон, разделяем его
    if (root->count == MAX_DEGREE) {
        BNode* newRoot = (BNode*)malloc(sizeof(BNode));
        newRoot->count = 0;
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        int i = 0;
        if (newRoot->data[0].num < data.num) {
            i++;
        }
        newRoot->children[i] = insertBNode(newRoot->children[i], data);
        return newRoot;
    }

    // Вставка в соответствующее дочернее дерево
    int i = 0;
    while (i < root->count && data.num > root->data[i].num) {
        i++;
    }
    root->children[i] = insertBNode(root->children[i], data);
    return root;
}

// Удаление узла из B-дерева
BNode* deleteBNode(BNode* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    // Поиск узла для удаления
    int i = 0;
    while (i < root->count && value > root->data[i].num) {
        i++;
    }

    // Если узел найден в текущем узле, удаляем его
    if (i < root->count && value == root->data[i].num) {
        if (root->children[i] == NULL) { // Это лист
            for (int j = i; j < root->count - 1; j++) {
                root->data[j] = root->data[j + 1];
            }
            root->count--;
            return root;
        }

        // Находим следующий по порядку узел в дочернем поддереве
        BNode* child = root->children[i];
        while (child->children[child->count] != NULL) {
            child = child->children[child->count];
        }
        Equip temp = child->data[child->count - 1];
        child->data[child->count - 1] = root->data[i];
        root->data[i] = temp;
        root->children[i] = deleteBNode(root->children[i], temp.num);
        return root;
    }

    // Узел находится в дочернем поддереве
    root->children[i] = deleteBNode(root->children[i], value);
    return root;
}



// Вывод B-дерева
void displayBTree(BNode* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->count; i++) {
        display(&root->data[i]);
        if (root->children[i] != NULL) {
            displayBTree(root->children[i]);
        }
    }

    if (root->children[root->count] != NULL) {
        displayBTree(root->children[root->count]);
    }
}

// Поиск узла по значению в B-дереве
BNode* searchBTree(BNode* root, int value) {
    int i = 0;
    while (i < root->count && value > root->data[i].num) {
        i++;
    }

    if (i < root->count && value == root->data[i].num) {
        return root;
    } else if (root->children[i] != NULL) {
        return searchBTree(root->children[i], value);
    } else {
        return NULL;
    }
}

// Структура узла B+-дерева
typedef struct BPlusNode {
    int count; // Количество элементов в узле
    Equip data[MAX_DEGREE]; // Данные узла
    struct BPlusNode* children[MAX_DEGREE + 1]; // Массив указателей на дочерние узлы
    bool isLeaf; // Флаг, указывающий, является ли узел листом
} BPlusNode;

// Создание пустого B+-дерева
BPlusNode* createBPlusTree() {
    BPlusNode* root = (BPlusNode*)malloc(sizeof(BPlusNode));
    root->count = 0;
    root->isLeaf = true;
    for (int i = 0; i < MAX_DEGREE; i++) {
        root->children[i] = NULL;
    }
    return root;
}

// Разделение дочернего узла
void splitChildBPlus(BPlusNode* parent, int childIndex, BPlusNode* child) {
    BPlusNode* newChild = (BPlusNode*)malloc(sizeof(BPlusNode));
    newChild->isLeaf = child->isLeaf;
    newChild->count = MAX_DEGREE / 2;
    parent->count++;

    for (int i = 0; i < MAX_DEGREE / 2; i++) {
        newChild->data[i] = child->data[i + MAX_DEGREE / 2];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= MAX_DEGREE / 2; i++) {
            newChild->children[i] = child->children[i + MAX_DEGREE / 2];
        }
    }

    for (int i = parent->count; i >= childIndex + 2; i--) {
        parent->children[i] = parent->children[i - 1];
    }

    parent->children[childIndex + 1] = newChild;

    for (int i = parent->count - 1; i >= childIndex; i--) {
        parent->data[i + 1] = parent->data[i];
    }

    parent->data[childIndex] = child->data[MAX_DEGREE / 2];

    child->count = MAX_DEGREE / 2;
}

// Вставка узла в B+-дерево
BPlusNode* insertBPlusNode(BPlusNode* root, Equip data) {
    if (root == NULL) {
        // Создание нового дерева
        root = (BPlusNode*)malloc(sizeof(BPlusNode));
        root->isLeaf = true;
        root->count = 1;
        root->data[0] = data;
        for (int i = 0; i <= MAX_DEGREE; i++) {
            root->children[i] = NULL;
        }
        return root;
    }

    if (root->isLeaf) {
        // Вставка в лист
        int i = 0;
        while (i < root->count && data.num > root->data[i].num) {
            i++;
        }
        for (int j = root->count; j > i; j--) {
            root->data[j] = root->data[j - 1];
        }
        root->data[i] = data;
        root->count++;

        // Если лист переполнен, разделяем его
        if (root->count == MAX_DEGREE + 1) {
            BPlusNode* newRoot = (BPlusNode*)malloc(sizeof(BPlusNode));
            newRoot->isLeaf = false;
            newRoot->count = 0;
            splitChildBPlus(newRoot, 0, root);
            return newRoot;
        }
        return root;
    }

    // Вставка в нелист
    int i = 0;
    while (i < root->count && data.num > root->data[i].num) {
        i++;
    }
    root->children[i] = insertBPlusNode(root->children[i], data);

    // Если дочерний узел переполнен, разделяем его
    if (root->children[i]->count == MAX_DEGREE + 1) {
        splitChildBPlus(root, i, root->children[i]);
    }
    return root;
}

// Удаление узла из B+-дерева
BPlusNode* deleteBPlusNode(BPlusNode* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    // Поиск узла для удаления
    int i = 0;
    while (i < root->count && value > root->data[i].num) {
        i++;
    }

    // Если узел найден в текущем узле, удаляем его
    if (i < root->count && value == root->data[i].num) {
        if (root->isLeaf) {
            for (int j = i; j < root->count - 1; j++) {
                root->data[j] = root->data[j + 1];
            }
            root->count--;
            return root;
        }

        // Находим следующий по порядку узел в дочернем поддереве
        BPlusNode* child = root->children[i + 1];
        while (!child->isLeaf) {
            child = child->children[0];
        }
        Equip temp = child->data[0];
        child->data[0] = root->data[i];
        root->data[i] = temp;
        root->children[i + 1] = deleteBPlusNode(root->children[i + 1], temp.num);
        return root;
    }

    // Узел находится в дочернем поддереве
    root->children[i] = deleteBPlusNode(root->children[i], value);
    return root;
}

// Вывод B+-дерева
void displayBPlusTree(BPlusNode* root) {
    if (root == NULL) {
        return;
    }

    if (root->isLeaf) {
        for (int i = 0; i < root->count; i++) {
            display(&root->data[i]);
        }
    } else {
        for (int i = 0; i < root->count; i++) {
            displayBPlusTree(root->children[i]);
            display(&root->data[i]);
        }
        displayBPlusTree(root->children[root->count]);
    }
}

// Поиск узла по значению в B+-дереве
BPlusNode* searchBPlusTree(BPlusNode* root, int value) {
    int i = 0;
    while (i < root->count && value > root->data[i].num) {
        i++;
    }

    if (i < root->count && value == root->data[i].num) {
        return root;
    } else if (root->isLeaf) {
        return NULL;
    } else {
        return searchBPlusTree(root->children[i], value);
    }
}