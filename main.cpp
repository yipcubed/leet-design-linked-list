#include <algorithm>
#include <cstring>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <sstream>


// https://leetcode.com/problems/design-linked-list/


// #include "../utils/VectorUtils.hpp"
// #include "../utils/TreeUtils.hpp"
// #include "../utils/PrintUtils.hpp"

using namespace std;

#pragma GCC diagnostic ignored "-Wunknown-pragmas"

// Live coding problems, watch at
// https://www.twitch.tv/yipcubed
// https://www.youtube.com/channel/UCTV_UOPu7EWXvYWsBFxMsSA/videos
//

// makes code faster, but larger. Just for LeetCode fun!
#pragma GCC optimise ("Ofast")

// makes stdin not synced so it is faster. Just for LeetCode fun!
static auto _no_sync_ __attribute__((unused)) = []() {              // NOLINT
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class MyLinkedList {
    friend ostream &operator<<(ostream &os, const MyLinkedList &ml);

private:
    struct ListNode {
        int val;
        ListNode *next{nullptr};
        ListNode *prev{nullptr};

        explicit ListNode(int val, ListNode *nextNode = nullptr)
                : val{val} {
            connect(this, nextNode);
        }
    };

    static void connect(ListNode *from, ListNode *to) {
        if (from) from->next = to;
        if (to) to->prev = from;
    }

    ListNode *head{nullptr};
    ListNode *tail{nullptr};
public:
    /** Initialize your data structure here. */
    MyLinkedList() {}

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0) return -1;
        int count = 0;
        ListNode *curr = head;
        while (curr) {
            if (count++ == index)
                return curr->val;
            curr = curr->next;
        }
        return -1;
    }

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        auto nh = new ListNode(val, head);
        if (head == nullptr) {
            head = tail = nh;
        } else {
            head = nh;
        }
    }

/** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        auto nt = new ListNode(val);
        if (head == nullptr) {
            head = tail = nt;
        } else {
            connect(tail, nt);
            tail = nt;
        }
    }

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index == -1) {
            addAtHead(val);
            return;
        }
        if (index < -1) return;
        int count = 0;
        ListNode *curr = head;
        while (curr) {
            if (count == index) {
                // insert before this one
                auto n = new ListNode(val);
                if (!curr->prev)
                    head = n;
                connect(curr->prev, n);
                connect(n, curr);
                return;
            }
            ++count;
            curr = curr->next;
        }
        // bad index, add to end
        if (count == index)
            addAtTail(val);
    }

/** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < 0) return;
        int count = 0;
        ListNode *curr = head;
        while (curr) {
            if (count == index) {
                if (!curr->next)
                    tail = curr->prev;
                if (!curr->prev)
                    head = head->next;
                connect(curr->prev, curr->next);
                return;
            }
            ++count;
            curr = curr->next;
        }
        // bad index
        return;
    }

};

ostream &operator<<(ostream &os, const MyLinkedList &ml) {
    os << "[";
    auto tr = ml.head;
    if (tr) {
        os << tr->val;
        tr = tr->next;
    }

    while (tr) {
        os << "->" << tr->val;
        tr = tr->next;
    }
    return os << "]";;
}

void test1() {
    MyLinkedList linkedList;
    cout << linkedList << endl;
    linkedList.addAtHead(1);
    cout << linkedList << endl;
    linkedList.addAtTail(3);
    cout << linkedList << endl;
    linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
    cout << linkedList << endl;
    cout << linkedList.get(1) << endl;           // returns 2
    linkedList.deleteAtIndex(1);  // now the linked list is 1->3
    cout << linkedList << endl;
    cout << linkedList.get(1) << endl;        // returns 3
    cout << linkedList << endl;

    // ["MyLinkedList",
    // "addAtHead","addAtHead",
    // "deleteAtIndex",
    // "addAtIndex",
    // "addAtHead","addAtHead","addAtHead",
    // "get",
    // "addAtTail",
    // "addAtIndex","addAtHead"]
    //[[],[5],[2],[1],[1,9],[4],[9],[8],[3],[1],[3,6],[3]]
    MyLinkedList m;
    cout << "[] ? " << m << endl;
    m.addAtHead(5);
    m.addAtHead(2);
    cout << "2->5 ? " << m << endl;
    m.deleteAtIndex(1);
    cout << "2 ? " << m << endl;
    m.addAtIndex(1, 9);
    cout << "2->9 ? " << m << endl;
    m.addAtHead(4);
    m.addAtHead(9);
    m.addAtHead(8);
    cout << "8->9->4->2->9 ? " << m << endl;
    cout << "2 ? " << m.get(3) << endl;
    m.addAtTail(1);
    cout << "8->9->4->2->9->1? " << m << endl;
    m.addAtIndex(3, 6);
    m.addAtHead(3);

//    ["MyLinkedList","addAtHead","addAtTail",
//     "addAtIndex","get","deleteAtIndex","get"]
//    [[],[1],[3],[1,2],[1],[1],[1]]
    MyLinkedList m2;
    cout << "[] ? " << m2 << endl;
    m2.addAtHead(1);
    m2.addAtTail(3);
    cout << "1->3 ? " << m2 << endl;
    m2.addAtIndex(1, 2);
    cout << "1->2->3 ? " << m2 << endl;
    cout << "2 ? " << m2.get(1) << endl;
    m2.deleteAtIndex(1);
    cout << "1->3 ? " << m2 << endl;
    cout << "3 ? " << m2.get(1) << endl;

    // ["MyLinkedList","get","addAtIndex","get","get","addAtIndex","get","get"]
    //[[],[0],[1,2],[0],[1],[0,1],[0],[1]]
    MyLinkedList m3;
    cout << "-1 ? " << m3.get(0) << endl;
    m3.addAtIndex(1, 2);
    cout << "[] ? " << m3 << endl;

}


void test2() {

}

void test3() {

}