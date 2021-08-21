#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class max_heap
{
private:
    vector<int> node;

public:
    max_heap();
    void adjust_to_botton(int current_index, int last_index);
    void adjust_to_top(int current_index);
    void add(int d);
    void free(int d);
    int search(int d);
    void show();
};
max_heap::max_heap()
{
    node.push_back(NULL);
}
int max_heap::search(int d)
{
    for (int i = 1; i < node.size() - 1; i++)
    {
        if (d == node[i])
        {
            return i;
        }
    }
}
void max_heap::adjust_to_top(int current_index)
{
    while (current_index > 1)
    {
        if (node[current_index] <= node[current_index / 2])
        {
            break;
        }
        else
        {
            swap(node[current_index], node[current_index / 2]);
        }
        current_index /= 2;
    }
}
void max_heap::adjust_to_botton(int current_index, int last_index)
{
    int child_index = current_index * 2;
    int tmp = node[current_index];
    while (child_index <= last_index)
    {
        if ((node[child_index + 1] > node[child_index]) && (child_index + 1 <= node.size() - 1))
        {
            child_index++;
        }
        if (node[current_index] > node[child_index])
        {
            break;
        }
        else
        {
            node[current_index] = node[child_index];
            child_index *= 2;
        }
        node[child_index / 2] = tmp;
    }
}
void max_heap::add(int d)
{
    node.push_back(d);
    adjust_to_top(node.size() - 1);
}
void max_heap::free(int d)
{
    int target = search(d);
    swap(node[node.size() - 1], node[target]);
    node.pop_back();
    if (node.size() - 1 > 2)
    {
        if (node[target] > node[target / 2] && target > 2)
        {
            max_heap::adjust_to_top(target);
        }
        else
        {
            max_heap::adjust_to_botton(target, node.size() - 1);
        }
    }
}
void max_heap::show()
{
    for (int i = 1; i <= node.size() - 1; i++)
    {
        cout << node[i] << "\n";
    }
    cout << "\n";
}
int main()
{
    max_heap heap_tree;
    heap_tree.add(15);
    heap_tree.add(23);
    heap_tree.add(10);
    heap_tree.add(40);
    heap_tree.add(8);
    heap_tree.show();
    heap_tree.free(23);
    heap_tree.show();
    heap_tree.free(40);
    heap_tree.show();
    return 0;
}