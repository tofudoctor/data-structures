#include <iostream>
using namespace std;
class node
{
private:
    int data;
    node *l;
    node *r;

public:
    friend class bst;
};
class bst
{
private:
    node *root;
    node *cur;
    node *ptr;
    node *tmp;
    node *free_in(node *x, int d);
    void pre(node *x);
    void in(node *x);
    void post(node *x);
    void print_2d(node *x, int space);
    int hight(node *x);

public:
    bst();
    void add(int d);
    void free(int d);
    void show(string s);
    node *min_node(node *x);
};
bst::bst()
{
    root = NULL;
}
node *bst::min_node(node *x)
{
    while (x->l != NULL)
    {
        x = x->l;
    }
    return x;
}
void bst::add(int d)
{
    ptr = new node;
    cur = new node;
    cur = root;
    ptr->data = d;
    ptr->l = NULL;
    ptr->r = NULL;
    if (root == NULL)
    {
        root = ptr;
    }
    else
    {
        while (cur != NULL)
        {
            if (d > cur->data && cur->r == NULL)
            {
                cur->r = ptr;
                break;
            }
            else if (d > cur->data)
            {
                cur = cur->r;
            }
            else if (d < cur->data && cur->l == NULL)
            {
                cur->l = ptr;
                break;
            }
            else
            {
                cur = cur->l;
            }
        }
    }
}
void bst::free(int d)
{
    free_in(root, d);
}
node *bst::free_in(node *x, int d)
{
    if (x == NULL)
    {
        return x;
    }
    else if (d > x->data)
    {
        x->r = free_in(x->r, d);
    }
    else if (d < x->data)
    {
        x->l = free_in(x->l, d);
    }
    else
    {
        if (x->r == NULL)
        {
            tmp = x->r;
            delete x;
            return tmp;
        }
        else if (x->l == NULL)
        {
            tmp = x->l;
            delete x;
            return tmp;
        }
        else
        {
            tmp = min_node(x->r);
            x->data = tmp->data;
            x->r = free_in(x->r, tmp->data);
        }
    }
    return x;
}
void bst::print_2d(node *x, int space)
{
    if (x == NULL)
    {
        return;
    }
    space += 10;
    print_2d(x->r, space);
    cout << "\n";
    for (int i = 10; i < space; i++)
    {
        cout << ' ';
    }
    cout << x->data << "\n";
    print_2d(x->l, space);
}
void bst::pre(node *x)
{
    if (x != NULL)
    {
        cout << x->data << " ";
        pre(x->l);
        pre(x->r);
    }
}
void bst::in(node *x)
{
    if (x != NULL)
    {
        in(x->l);
        cout << x->data << " ";
        in(x->r);
    }
}
void bst::post(node *x)
{
    if (x != NULL)
    {
        post(x->l);
        post(x->r);
        cout << x->data << " ";
    }
}
int bst::hight(node *x)
{
    if (x == NULL)
    {
        return -1;
    }
    else
    {
        int rhight = hight(x->r);
        int lhight = hight(x->l);
        return max(lhight, rhight) + 1;
    }
}
void bst::show(string s)
{
    if (s == "in")
    {
        in(root);
    }
    else if (s == "pre")
    {
        pre(root);
    }
    else if (s == "post")
    {
        post(root);
    }
    else if (s == "high")
    {
        cout << hight(root);
    }
    else
    {
        print_2d(root, 0);
    }
    cout << "\n";
}
int main()
{
    bst tree;
    tree.add(35);
    tree.add(18);
    tree.add(23);
    tree.add(1);
    tree.add(12);
    tree.add(43);
    tree.add(31);
    tree.add(52);
    tree.add(20);
    tree.add(3);
    tree.show("high");
    tree.free(52);
    tree.show("high");
    tree.free(35);
    tree.show("high");
    tree.free(3);
    tree.show("high");
    //tree.show("in");
    //tree.show("pre");
    //tree.show("post");
    return 0;
}