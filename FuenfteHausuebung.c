#include <stdio.h>
#include <stdlib.h>

/*══════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║   Author: Nazar Burdeinyi, ITS-b2 a                                                                       ║
║   Name: FuenfteHausuebung.c                                                                               ║
║   Description: Binary Search Tree. Werte hinzufügen, Traversieren und Werte löschen                       ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════*/

struct node
{
    int value;
    struct node *left;
    struct node *right;
};

struct node *createNode(int v)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode != NULL)
    {
        newNode->value = v;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

struct node *insertIntoTree(int v, struct node *root)
{
    if (root == NULL)
    {
        struct node *newNode = createNode(v);
        return newNode;
    }
    else
    {
        if (root->value > v)
        {
            if (root->left == NULL)
            {
                root->left = createNode(v);
            }
            else
            {
                insertIntoTree(v, root->left);
            }
        }
        else if (root->value < v)
        {
            if (root->right == NULL)
            {
                root->right = createNode(v);
            }
            else
            {
                insertIntoTree(v, root->right);
            }
        }
    }
    return root;
}

void InOrder(struct node *root)
{
    if (root->left != NULL)
    {
        InOrder(root->left);
    }
    printf("%d ", root->value);
    if (root->right != NULL)
    {
        InOrder(root->right);
    }
}

void PreOrder(struct node *root)
{
    printf("%d ", root->value);
    if (root->left != NULL)
    {
        PreOrder(root->left);
    }
    if (root->right != NULL)
    {
        PreOrder(root->right);
    }
}

void PostOrder(struct node *root)
{
    if (root->left != NULL)
    {
        PostOrder(root->left);
    }
    if (root->right != NULL)
    {
        PostOrder(root->right);
    }
    printf("%d ", root->value);
}

struct node *DeleteNode(int v, struct node *root)
{
    struct node *temp; // = root

    if (root->value > v) // Schritt nach links
    {
        root->left = DeleteNode(v, root->left);
    }
    else if (root->value < v) // Schritt nach rechts
    {
        root->right = DeleteNode(v, root->right);
    }
    else // Node ist gefunden
    {
        if (root->left == NULL && root->right == NULL) // Keine Kinder
        {
            free(root);
            root = NULL;
        }
        else if (root->left != NULL && root->right == NULL) // Ein Kind Links
        {
            temp = root;
            root = root->left;
            free(temp);
        }
        else if (root->left == NULL && root->right != NULL) // Ein Kind Rechts
        {
            temp = root;
            root = root->right;
            free(temp);
        }
        else // Zwei Kinder
        {
            temp = root->right;

            while (temp->left != NULL)
            {
                temp = temp->left;
            }

            root->value = temp->value;
            root->right = DeleteNode(temp->value, root->right);
        }
    }
    return root;
}

void End_of_Programm(struct node *root) // Post-Order, aber mit free() anstatt printf()
{
    if (root->left != NULL)
    {
        End_of_Programm(root->left);
    }
    if (root->right != NULL)
    {
        End_of_Programm(root->right);
    }
    free(root);
}

int main()
{
    char ch[5] = "";
    int n = 0, i, w, sw, l;
    struct node *Root = NULL;

    while (n <= 0)
    {
        printf("Bitte Anzahl der Elemente im Baum eingeben: ");
        scanf("%d", &n);
    }

    for (i = 0; i < n; i++)
    {
        printf("Bitte den Wert eingeben: ");
        scanf("%d", &w);
        Root = insertIntoTree(w, Root);
    }

    while (1)
    {
        system("cls");
        printf("__BINARY_TREE_MENUE__\n1. In-Order\n2. Pre-Order\n3. Post-Order\n4. Delete node\n0. Beenden\nIhr Wahl - ");
        scanf("%d", &sw);

        switch (sw)
        {
        case 1:
            printf("\nIn-Order:\n");
            InOrder(Root);
            printf("\n");
            system("pause");
            break;
        case 2:
            printf("\nPre-Order:\n");
            PreOrder(Root);
            printf("\n");
            system("pause");
            break;
        case 3:
            printf("\nPost-Order:\n");
            PostOrder(Root);
            printf("\n");
            system("pause");
            break;
        case 4:
            if (Root != NULL)
            {
                printf("\n");
                PostOrder(Root);
                printf("\n");
                getchar();
                printf("\nDen Wert zum Loeschen eingeben (\"-\" beendet die Eingabe): ");
                scanf("%s", ch);

                if (ch[0] == '-')
                {
                    break;
                }
                l = atoi(ch);

                Root = DeleteNode(l, Root);
            }
            else
            {
                printf("Der Baum ist leer. Nichts zum Entfernen\n");
            }
            break;
        case 0:
            if (Root)
            {
                End_of_Programm(Root);
            }
            system("cls");
            return 0;
        default:
            printf("\nFalsche Eingabe\n");
            system("pause");
            break;
        }
    }
}