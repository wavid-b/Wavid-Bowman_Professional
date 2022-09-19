/*
    Wavid Bowman
    Interquartile Range

    Given a sorted singly linked list without a tail (e.g, head -> 1 -> 2 -> 3 -> 4), 
    return the interquartile range of the data set using the slow and fast pointer 
    approach OR using a methodology that does not iterate over the linked list 
    twice. You must not iterate over the entire linked list more than once and you 
    cannot use arrays, vectors, lists or an STL implementation of List ADT in this problem.

    Sample Input:
        2 4 4 5 6 7 8
    
    Sample Output:
        3.00 
*/

#include <iostream>
#include <iomanip>

class Node {
    public:
        int value;
        Node* next = nullptr;
};

Node* insertEnd(Node* head, int key)
{
    Node* temp = new Node();
    temp->value = key;
    if(head == nullptr)
        head = temp;
    else
    {
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    return head;
}
float findMedian(Node* head, Node*& middleNode, Node*& rec1, Node* &rec2, bool firstPass) {
    float output = 0.0;
    Node* fastptr = head;
    Node* lastSlowPtr = head;
    Node* slowptr = head;
    Node* twoForward = head;
	while (twoForward != nullptr) {
		twoForward = fastptr->next;
		if (twoForward != nullptr) {
			twoForward = twoForward->next;
		}
		if (twoForward != nullptr)
		{
            lastSlowPtr = slowptr;
            slowptr = slowptr->next;
			fastptr = twoForward;
		}
		else {
			//case for if there are an odd number in the list 
			if (fastptr->next == nullptr) {
				output = float(slowptr->value);
                middleNode = slowptr->next;
                //so that I can reconnect the linked list later
                if (firstPass) {
                    rec1 = lastSlowPtr;
                    rec2 = lastSlowPtr->next;
                    //so that the q1 loop knows to stop
                    lastSlowPtr->next = nullptr;
                }
			}
			//case for even number in list
			else {
				output = (float)(slowptr->value);
				output = (output + slowptr->next->value) / 2;
				middleNode = slowptr->next;
                if (firstPass) {
                    rec1 = slowptr;
                    rec2 = slowptr->next;
                    //for q1 to stop when it should
                    slowptr->next = nullptr;
                }
			}
		}
	}
    return output;
}
float interQuartile(Node* head)
{
    Node* reconnector2 = nullptr;
    Node* reconnector1 = nullptr;
    Node* trash = nullptr;
    Node* midNode = nullptr;
    float median = 0.0;
    float q1 = 0.0;
    float q3 = 0.0;
    //first pass has a different call just so I can reconnect the broken linked list 
    median = findMedian(head, midNode, reconnector1, reconnector2, true);
    q1 = findMedian(head, trash, reconnector1, reconnector2, false);
    q3 = findMedian(midNode, trash, reconnector1, reconnector2, false);

    //now reconnect the broken linked list for no memory leakage
    reconnector1->next = reconnector2;
    return q3-q1;   
}
