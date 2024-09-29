#include <bits/stdc++.h>
using namespace std;
template <typename datatype>
struct node{
    datatype data;
    node* next;
};
node<int>*front = nullptr, *rear=nullptr;
void init() {
    node<int> s;
    front=rear=&s;
}
int main() {
    init();
    node<int> t;
    t.data=1;
    front->next=&t;
    rear=&t;
    cout<<front->next->data;
    return 0;
}