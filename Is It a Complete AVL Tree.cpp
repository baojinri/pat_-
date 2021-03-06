#include <algorithm>
#include <iostream>
struct node
{
    int date;
    int height;
    node *lchild;
    node *rchild;
};

int getheight(node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int getbalancefactor(node *root)
{
    return getheight(root->lchild) - getheight(root->rchild);
}

int updateheught(node *root)
{
    root->height = std::max(getheight(root->lchild), getheight(root->rchild)) + 1;
    return 0;
}

int L(node *&root)
{
    node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    updateheught(root);
    updateheught(temp);
    root = temp;
    return 0;
}

int R(node *&root)
{
    node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updateheught(root);
    updateheught(temp);
    root = temp;
    return 0;
}

int build(node *&root, int v)
{
    if (root == NULL)
    {
        root = new node;
        root->date = v;
        root->lchild = NULL;
        root->rchild = NULL;
        root->height = 1;
        return 0;
    }
    if(v<root->date)
    {
        build(root->lchild,v);
        updateheught(root);
        if(getbalancefactor(root)==2)
        {
            if(getbalancefactor(root->lchild)==1)
            {
                R(root);
            }
            else if(getbalancefactor(root->lchild)==-1)
            {
                L(root->lchild);
                R(root);
            }
        }
    }
    else
    {
        build(root->rchild,v);
        updateheught(root);
        if(getbalancefactor(root)==-2)
        {
            if(getbalancefactor(root->rchild)==-1)
            {
                L(root);
            }
            else if(getbalancefactor(root->rchild)==1)
            {
                R(root->rchild);
                L(root);
            }
        }
    }
    return 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        int temp;
        std::cin >> temp;
        build(root, temp);
    }
    node *quene[30];
    int f = 0, r = 0;
    quene[r++] = root;
    int flag = 0;
    while (r!=f)
    {
        node *temp = quene[f++];
        std::cout << temp->date;
        if(f!=n)
            std::cout << " ";
        else
            std::cout << std::endl;
        if(temp->lchild!=NULL)
        {
            quene[r++] = temp->lchild;
            if(f*2!=r)
                flag = 1;
        }
        if(temp->rchild!=NULL)
        {
            quene[r++] = temp->rchild;
            if(f*2+1!=r)
                flag = 1;
        }
    }
    if(flag==1)
        std::cout << "NO";
    else
        std::cout << "YES";

    return 0;
}