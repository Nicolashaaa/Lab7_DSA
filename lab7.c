#include "tree.h"



int main() {
    int choice, treeType;
    AVLNode* avlTree = NULL;
    BNode* bTree = NULL;
    BPlusNode* bPlusTree = NULL;
    Equip equipment;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("AVL TREE operations:\n");
                printf("1. Create tree\n");
                printf("2. Display tree\n");
                printf("3. Insert node\n");
                printf("4. Search by position/value\n");
                printf("5. Delete node\n");
                scanf("%d", &treeType);

                switch (treeType) {
                    case 1:
                        // Создание и отображение АВЛ-дерева
                        avlTree = createAVLTree();

                    case 2:
                        displayAVLTree(avlTree);
                        break;
                    case 3:
                        // Вставка узла в АВЛ-дерево
                        input(&equipment);
                        avlTree = insertAVLNode(avlTree, equipment);
                        break;
                    case 4:
                        // Поиск элемента в АВЛ-дереве
                        printf("Enter value to search: ");
                        int value;
                        scanf("%d", &value);
                        AVLNode* found = searchAVLTree(avlTree, value);
                        if (found != NULL) {
                            display(&found->data);
                        } else {
                            printf("Value not found in AVL tree.\n");
                        }
                        break;
                    case 5:
                        // Удаление узла из АВЛ-дерева
                        printf("Enter value to delete: ");
                        scanf("%d", &value);
                        avlTree = deleteAVLNode(avlTree, value);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 2:
                printf("B TREE operations:\n");
                printf("1. Create tree\n");
                printf("2. Display tree\n");
                printf("3. Insert node\n");
                printf("4. Search by position/value\n");
                printf("5. Delete node\n");
                scanf("%d", &treeType);

                switch (treeType) {
                    case 1:
                        // Создание и отображение B-дерева
                        bTree = createBTree();
                        break;
                    case 2:
                        displayBTree(bTree);
                        break;
                    case 3:
                        // Вставка узла в B-дерево
                        input(&equipment);
                        bTree = insertBNode(bTree, equipment);
                        break;
                    case 4:
                        // Поиск элемента в B-дереве
                        printf("Enter value to search: ");
                        int value;
                        scanf("%d", &value);
                        BNode* found = searchBTree(bTree, value);
                        if (found != NULL) {
                            // Вывод найденного узла
                        } else {
                            printf("Value not found in B tree.\n");
                        }
                        break;
                    case 5:
                        // Удаление узла из B-дерева
                        printf("Enter value to delete: ");
                        scanf("%d", &value);
                        bTree = deleteBNode(bTree, value);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 3:
                printf("B+ TREE operations:\n");
                printf("1. Create tree\n");
                printf("2. Display tree\n");
                printf("3. Insert node\n");
                printf("4. Search by position/value\n");
                printf("5. Delete node\n");
                scanf("%d", &treeType);

                switch (treeType) {
                    case 1:
                        // Создание и отображение B+-дерева
                        bPlusTree = createBPlusTree();
                        break;
                    case 2:
                        displayBPlusTree(bPlusTree);
                        break;
                    case 3:
                        // Вставка узла в B+-дерево
                        input(&equipment);
                        bPlusTree = insertBPlusNode(bPlusTree, equipment);
                        break;
                    case 4:
                        // Поиск элемента в B+-дереве
                        printf("Enter value to search: ");
                        int value;
                        scanf("%d", &value);
                        BPlusNode* found = searchBPlusTree(bPlusTree, value);
                        if (found != NULL) {
                            // Вывод найденного узла
                        } else {
                            printf("Value not found in B+ tree.\n");
                        }
                        break;
                    case 5:
                        // Удаление узла из B+-дерева
                        printf("Enter value to delete: ");
                        scanf("%d", &value);
                        bPlusTree = deleteBPlusNode(bPlusTree, value);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}