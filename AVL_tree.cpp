#include <iostream>
using namespace std;
class node
{
private:
    int data;
    node *l;
    node *r;
    friend class avl_tree;
};
class avl_tree
{
private:
    node *root;
    node *b;
    int balancefactor(node *x);
    int height(node *x);
    node *r_rotation(node *a);
    node *l_rotation(node *a);
    node *add_recursive(node *x, node *new_node);
    node *free_recursive(node *x, int d);
    node *min_node(node *x);
    void pre(node *x);
    void in(node *x);
    void post(node *x);

public:
    avl_tree();
    void add(int d);
    void free(int d);
    void show(string s);
};
avl_tree::avl_tree()
{
    root = NULL;
}
int avl_tree::height(node *x)
{
    if (x == NULL)
    {
        return -1;
    }
    else
    {
        int rheight = height(x->r);
        int lheight = height(x->l);
        return max(rheight, lheight) + 1;
    }
}
int avl_tree::balancefactor(node *x)
{
    if (x == NULL)
    {
        return -1;
    }
    else
    {
        return height(x->l) - height(x->r);
    }
}
node *avl_tree::r_rotation(node *a)
{
    node *b = a->l;
    node *br = b->r;
    b->r = a;
    a->l = br;
    return b;
}
node *avl_tree::l_rotation(node *a)
{
    node *b = a->r;
    node *bl = b->l;
    b->l = a;
    a->r = bl;
    return b;
}
void avl_tree::add(int d)
{
    node *new_node = new node;
    new_node->data = d;
    new_node->l = NULL;
    new_node->r = NULL;
    root = add_recursive(root, new_node);
}
node *avl_tree::add_recursive(node *x, node *new_node)
{
    if (x == NULL)
    {
        x = new_node;
        return x;
    }
    if (new_node->data > x->data)
    {
        x->r = add_recursive(x->r, new_node);
    }
    else if (new_node->data < x->data)
    {
        x->l = add_recursive(x->l, new_node);
    }
    else
    {
        cout << "conflicted!!!\n";
        return x;
    }
    int bf = balancefactor(x);
    if (bf > 1 && new_node->data < x->l->data)
    {
        return r_rotation(x);
    }
    else if (bf < -1 && new_node->data > x->r->data)
    {
        return l_rotation(x);
    }
    else if (bf > 1 && new_node->data > x->l->data)
    {
        x->l = l_rotation(x->l);
        return r_rotation(x);
    }
    else if (bf < -1 && new_node->data < x->r->data)
    {
        x->r = r_rotation(x->r);
        return l_rotation(x);
    }
    return x;
}
void avl_tree::free(int d)
{
    root = free_recursive(root, d);
}
node *avl_tree::free_recursive(node *x, int d)
{
    if (x == NULL)
    {
        return x;
    }
    else if (d > x->data)
    {
        x->r = free_recursive(x->r, d);
    }
    else if (d < x->data)
    {
        x->l = free_recursive(x->l, d);
    }
    else
    {
        if (x->r == NULL)
        {
            node* tmp = x->l;
            delete x;
            return tmp;
        }
        else if (x->l == NULL)
        {
            node* tmp = x->r;
            delete x;
            return tmp;
        }
        else{
            node* tmp = min_node(x->r);
            x->data = tmp->data;
            x->r = free_recursive(x->r, tmp->data);
        }
    }
    int bf = balancefactor(x);
    if(bf == 2 && balancefactor(x->l)>=0){
        x = r_rotation(x);
    }
    else if(bf == -2 && balancefactor(x->r)<=0){
        x = l_rotation(x);
    }
    else if(bf == 2 && balancefactor(x->l)==-1){
        x->l = l_rotation(x->l);
        x = r_rotation(x);
    }
    else if( bf == -2 && balancefactor(x->r) == 1){
        x->r = r_rotation(x->r);
        x = l_rotation(x);
    }
    return x;
}
node *avl_tree::min_node(node *x)
{
    while (x->l == NULL)
    {
        x = x->l;
    }
    return x;
}
void avl_tree::pre(node *x)
{
    if (x != NULL)
    {
        cout << x->data << ' ';
        pre(x->l);
        pre(x->r);
    }
}
void avl_tree::in(node *x)
{
    if (x != NULL)
    {
        in(x->l);
        cout << x->data << ' ';
        in(x->r);
    }
}
void avl_tree::post(node *x)
{
    if (x != NULL)
    {
        post(x->l);
        post(x->r);
        cout << x->data << ' ';
    }
}
void avl_tree::show(string s)
{
    if (s == "pre")
    {
        pre(root);
    }
    else if (s == "in")
    {
        in(root);
    }
    else if (s == "post")
    {
        post(root);
    }
    cout << '\n';
}
int main()
{
    avl_tree tree;
    tree.add(30);
    tree.add(25);
    tree.add(15);
    tree.add(22);
    tree.add(23);
    tree.add(13);
    tree.add(26);
    tree.add(36);
    tree.show("pre");
    tree.free(23);
    tree.show("pre");
    return 0;
}