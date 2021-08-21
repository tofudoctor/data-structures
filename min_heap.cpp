#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class min_heap
{
private:
    vector<int> node;

public:
    min_heap();
    int search(int d);
    void adjust_to_top(int current_index);
    void adjust_to_botton(int current_index, int last_index);
    void add(int d);
    void free(int d);
    void show();
};
min_heap::min_heap()
{
    node.push_back(NULL);
}
int min_heap::search(int d)
{
    for (int i = 1; i < node.size(); i++)
    {
        if (node[i] == d)
        {
            return i;
        }
    }
}
void min_heap::adjust_to_top(int current_index)
{
    while (current_index > 1)
    {
        if (node[current_index] > node[current_index / 2])
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
void min_heap::adjust_to_botton(int current_index, int last_index)
{
    int child_index = current_index * 2;
    int tmp = node[child_index];
    while (child_index <= last_index)
    {
        if (node[child_index] > node[child_index + 1] && child_index < node.size() - 1)
        {
            child_index++;
        }
        if (node[current_index] > node[child_index])
        {
            node[child_index] = node[current_index];
            child_index *= 2;
        }
        else
        {
            break;
        }
        node[child_index / 2] = tmp;
    }
}
void min_heap::add(int d)
{
    node.push_back(d);
    adjust_to_top(node.size() - 1);
}
void min_heap::free(int d)
{
    int target = min_heap::search(d);
    swap(node[node.size() - 1], node[target]);
    node.pop_back();
    if (node.size() - 1 > 2)
    {
        if (target > 2 && node[target] <= node[target / 2])
        {
            adjust_to_top(target);
        }
        else
        {
            adjust_to_botton(target, node.size() - 1);
        }
    }
}
void min_heap::show()
{
    for (int i = 1; i <= node.size() - 1; i++)
    {
        cout << node[i] << "\n";
    }
    cout << "\n";
}
int main()
{
    min_heap heap_tree;
    heap_tree.add(15);
    heap_tree.add(23);
    heap_tree.add(10);
    heap_tree.add(40);
    heap_tree.add(8);
    heap_tree.show();
    heap_tree.free(15);
    heap_tree.show();
    heap_tree.free(10);
    heap_tree.show();
    return 0;
}