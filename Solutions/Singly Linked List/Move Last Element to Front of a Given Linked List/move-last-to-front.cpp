/*
    GEEKSFORGEEKS
        DATA STRUCTURES
            SINGLY LINKED LIST EXERCISE
    
    MOVE LAST ELEMENT TO FRONT OF A GIVEN LINKED LIST

    coded by Fatih Cinar
    on March 10th, 2020
*/

#include <iostream>
using namespace std;

class Node
{
    public:
        int Value;
        Node* Next;
    public:
        Node(); // guarantess the Next pointer is NULL
        Node(int mValue); // guarantees the Next pointer is NULL
};

class LinkedList
{
    public:
        Node* Head;
    public:
        LinkedList(); // guarantess Head Pointer is NULL initially
        void insertEnd(int mValue); 
        void print();
        void moveLastNodeToFront(); // Moves the last node to front
        ~LinkedList(); // Releases memory 

        static LinkedList* getArbitraryLinkedList(); 
        // returns a new arbitrary-length and arbitrary-valued linked list
};


int main(){

    LinkedList* ll1 = LinkedList::getArbitraryLinkedList();
    // a reference to a linked list object
    // But the linked list object only has one address (pointer) inside

    /* TEST CASE 1 */
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    ll1->moveLastNodeToFront();
    ll1->print();

    

    /* TEST CASE 2 */

    LinkedList* ll2 = LinkedList::getArbitraryLinkedList();

    ll2->print();

    ll2->moveLastNodeToFront();
    ll2->print();

    ll2->moveLastNodeToFront();
    ll2->print();

    ll2->moveLastNodeToFront();
    ll2->print();

    ll2->moveLastNodeToFront();
    ll2->print();

    ll2->moveLastNodeToFront();
    ll2->print();

    return 0;

}

LinkedList::~LinkedList(){
    /*
        Destructor Function
        Memory Release
    */

    Node* iterator = this->Head; 
    // will be iterating on the linked list
    
    if(iterator == nullptr){
        // Noting to release
        return;
    }
    else{
        // at least one element to release memory

        Node* nextOne = nullptr; 
        // remember the address of the next node during relase

        // VISIT EACH NODE ONCE
        while(iterator != nullptr){
            
            nextOne = iterator->Next; // remember next node first

            delete iterator; // release this node
            
            iterator = nextOne; // keep iterating with the next one
        }

        return;
    }

}

LinkedList* LinkedList::getArbitraryLinkedList(){
    /*
        This static class method returns an arbitrary-length
        linked list with random values in it
        Like FACTORY DESIGN PATTERN 
    */

    // First DECIDE the LENGTH of the linked list

    const int maximumLength = 10;
    const int lengthList = rand() % maximumLength;

    int length = lengthList;

    LinkedList* newLinkedList = new LinkedList();
    // Create the lnked list object
    // Head pointer is null initially

    if(length == 0){
        // if the length is chosen to be ZERO
        // return the linked list 

    }
    else{
        int random; // randomNumber to add to the nodes

        // add nodes as much as length-chosen
        while(length >= 0){

            random = rand() % 100; // get random value to add

            newLinkedList->insertEnd(random);

            length--; // have added one
        }
    }

    return newLinkedList;
}


LinkedList::LinkedList(){

    this->Head = nullptr;
}

void LinkedList::insertEnd(int mValue){
    /*
        This method inserts a new node to the linked list
        at the end
    */

    // ALLOCATE MEMORY for new node first for sure
    Node* newNode = new Node(mValue);

    if(this->Head == nullptr){
        // CASE: LINKED LIST EMPTY
        this->Head = newNode;

        return;
    }
    else{
        // CASE: NOT-EMPTY LINKED LIST

        // go to the last element in the linked list
        Node* iterator = this->Head;

        while(iterator->Next != nullptr){

            iterator = iterator->Next;
        }

        // we're at the last element
        iterator->Next = newNode;

        return;
    }

}

void LinkedList::print(){

    if(this->Head == nullptr){
        // CASE: LINKED LIST EMPTY
        cout << "Empty List!" << endl;
    }
    else{

        // Iterate on the linked list and print everything

        Node* iterator = this->Head;

        // Iterate till the last node
        while(iterator != nullptr){

            cout << iterator->Value << " ";

            iterator = iterator->Next;
        }

        cout << endl;
    }
}

void LinkedList::moveLastNodeToFront(){
    /*
        This method moves the last element
        to the front of the linked list
    */

    /*
        ALGORITHM
        # Use two pointers
            One pointer is iterator
            Second pointer is previous pointer 
            Iterate on the linked list and each time
            Do not forget previous
            When you are at the last node
            # make previous node's next NULL
                because it is the last node now
            # and take the last node
                make it head node
            # and make the old-last-now-head node's next old-head node
                ## also keep old head node
    */


    if(this->Head == nullptr){
        // CASE: LINKED LIST EMPTY
        return;
    }

    if(this->Head->Next == nullptr){
        // CASE: LINKED LIST ONLY HAS ONE VALUE
        return;
    }

    Node *iterator = this->Head;
    // Iterator starts from the first node
    Node *previous = nullptr;
    // Initially previous pointer is NULL

  
    // GET TO THE LAST NODE  
    while(iterator->Next != nullptr){
        
        previous = iterator; 
        
        iterator = iterator->Next;
    }

    // NOW
    //  iterator = last node
    //  previous = second last node

    // Break the link at the node before the last node
    previous->Next = nullptr;

    // Remember the old head node
    Node* oldHead = this->Head;

    // Make the last node , new head node
    this->Head = iterator;
    
    // and link the new head node to the old head node
    iterator->Next = oldHead;

    return;

}

Node::Node()
{
    this->Value = 0;
    this->Next = nullptr;
}
Node::Node(int mValue)
{
    this->Next = nullptr;
    this->Value = mValue;
}
