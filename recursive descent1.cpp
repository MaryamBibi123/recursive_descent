#include<iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>

typedef struct treenode *tree;
struct treenode
{
    char info;
    tree left;
    tree right;
};

static int i = 0;
char nextsym(char input[]), nextChar; // Renamed next to nextChar
char input[10];

tree proc_e();
tree proc_t();
tree proc_v();
void inorder(tree root);

int main()
{
    tree root;
    int len;

    std::cout << "Enter an expression :\n";
    std::cin >> input;

    len = strlen(input);
    nextChar = nextsym(input);
    root = proc_e();

    if (len != i - 1)
    {
        std::cout << "error! Length error" << std::endl;
    // Remove getch();
        std::cin.get(); // Waits for a key press
        exit(0);
    }
    else
    {
        std::cout << "It's a valid expression\n";
        inorder(root);
    }

    return 0;
}

tree treebuild(char x, tree a, tree b)
{
    tree t;
    t = new treenode;
    t->info = x;
    t->left = a;
    t->right = b;

    return t;
}

tree proc_e()
{
    tree a, b;
    a = proc_t();

    while (nextChar == '+' || nextChar == '-')
    {
        if (nextChar == '+')
        {
            nextChar = nextsym(input);
            b = proc_t();
            a = treebuild('+', a, b);
        }
        else
        {
            nextChar = nextsym(input);
            b = proc_t();
            a = treebuild('-', a, b);
        }
    }
    return a;
}

tree proc_t()
{
    tree a, b;
    a = proc_v();

    while (nextChar == '*' || nextChar == '/')
    {
        if (nextChar == '*')
        {
            nextChar = nextsym(input);
            b = proc_v();
            a = treebuild('*', a, b);
        }
        else
        {
            nextChar = nextsym(input);
            b = proc_v();
            a = treebuild('/', a, b);  // Fixed backslash issue ('\\' to '/')
        }
    }
    return a;
}

tree proc_v()
{
    tree a;

    if (isalpha(nextChar))
        a = treebuild(nextChar, NULL, NULL);
    else
    {
        std::cout << "error! Invalid exp";
            // Remove getch();
        std::cin.get(); // Waits for a key press

        exit(0);
    }

    nextChar = nextsym(input);
    return a;
}

char nextsym(char input[])
{
    i++;
    return input[i - 1];
}

void inorder(tree t)
{
    if (t != NULL)
    {
        inorder(t->left);
        std::cout << t->info << " ";
        inorder(t->right);
    }
}
