/*
    GEEKSFORGEEKS
        DATA STRUCTURES
            SINGLY LINKED LIST EXERCISE
    IDENTICAL LINKED LISTS

    coded by Fatih Cinar
    on March 26th, 2020
*/

#include <iostream>
#include <vector>
using namespace std;

class Node
{
    public:
        int Value;
        Node* Next;
    public:
        Node(); // default constructor for node class
        Node(int value); // custom constructor for node class
};

class LinkedList
{
    private:
        Node* head; // head pointer of the linked list
    
    /* FUNCTIONALITIES */
    private:
        void releaseMemoryAllocated(); // releases all the memory allocated
    public:
        LinkedList(); // default constructor for the linked list class
        void insertEnd(int value); // insert the given value at the end of the linked list
        void insertMultipleValues(vector<int>& values); // insert multiple valuest at one
        void printList(); // prints the whole linked list
        ~LinkedList(); // default destructor for LL, releases memory
        bool isEmpty(); // figures out whether the LL is empty or not
        Node* getHeadNode(); // gives the head node of the LL
        
        static bool areIdentical(LinkedList* list1, LinkedList* list2); 
        // figures out whether two linked lists are identical or not

        static void testFunctionality();
        // tests functionality of areIdentical() function

};

enum Configurations
{
    DEFAULT_VALUE_NODE = 0,
    EMPTY = true,
    NOT_EMPTY = false,
};

Node::Node(){
    /*
        default constructor for the node class
    */

    this->Value = DEFAULT_VALUE_NODE;
    // make next pointer null, guarantee it
    this->Next = nullptr;
    
}

Node::Node(int value){
    /*
        custom constructor for the node class
        creates a node with a given value
    */

    this->Value = value; 
    this->Next = nullptr; // guarantee that it points to null initially 
}

LinkedList::LinkedList(){
    /*  
        default constructor for the linked list class
    */

    this->head = nullptr; // guarantee this
}

bool LinkedList::isEmpty(){
    /*
        figures out whether the linked list is empty or not
    */

    if(this->head == nullptr){
        return EMPTY;
    }
    else{
        return NOT_EMPTY;
    }
}

void LinkedList::printList(){
    /*
        prints the whole linked list to the console
    */

    if(this->isEmpty()){
        // CASE: LINKED LIST IS EMPTY
        cout << "Empty List!" << endl;
    }
    else{
        // print all elements using an iterator

        Node* iterator = this->head;

        while(iterator != nullptr){
        
            cout << iterator->Value << " ";
        
            iterator = iterator->Next; // keep going
        }

        cout << endl;
        return;
    }
    
}

void LinkedList::releaseMemoryAllocated(){
    /*
        this method releases all the memory allocated 
        privately
        use this in a destructor
    */

    if(!this->isEmpty()){
        // if this linked list IS NOT EMPTY
        // Release memory

        Node* iterator = this->head; // iterates on each node
        Node* nextOne = nullptr; // for remembering the next node

        while( iterator != nullptr){

            // remember the next one
            nextOne = iterator->Next;

            // release this node
            delete iterator;

            // keep going with the next one
            iterator = nextOne;
        }

        return;
    }
}

LinkedList::~LinkedList(){
    /*
        custom desturctor for the linked list class
        it frees all the memory allocated by the linked list
    */  

    this->releaseMemoryAllocated();
    
    return;
}

void LinkedList::insertEnd(int value){
    /*
        this method insert a new element at the end of the linked list
        by allocating a dynamic memory on heap
    */

    // first allocated memory 
    Node* newNode = new Node(value);

    if(this->isEmpty()){
        // CASE : LINKED LIST IS EMPTY
        
        this->head = newNode;
        return;
    }
    else{
        // go to the at the end of the list

        Node* iterator = this->head;

        while( iterator->Next != nullptr){
            // we gotta go to the next element in the list
            iterator = iterator->Next;
        }

        // now we are the end of the linked list

        iterator->Next = newNode; // added at the end of the linked list

        return; 
    }
}

Node* LinkedList::getHeadNode(){
    /*
        this method gives the head node of the linked list
    */

    return this->head;
}

bool LinkedList::areIdentical(LinkedList* list1, LinkedList* list2){
    /*  
        this method gets two linked lists and figures out
        whether they are identical or not
    */

    enum ConfigurationsInside
    {
        IDENTICAL = true,
        DISTINCT = false
    };

    Node* headFirst = list1->getHeadNode();
    Node* headSecond = list2->getHeadNode();

    if(headFirst == nullptr && headSecond == nullptr){
        // if they are both empty
        // that means they are identical
        return IDENTICAL;
    }
    else if(headFirst == nullptr && headSecond != nullptr
            || headFirst != nullptr && headSecond == nullptr){
        // if only one of them is null and the other is not null
        // they are definitely not identical

        return DISTINCT;
    }
    else{
        // Lets start comparing
        // First assume that they are identical 
        // and try to prove that they are not identical

        bool identical = true;

        Node* iterator1 = headFirst;
        // FOR ITERATION ON FIRST LL
        Node* iterator2 = headSecond;
        // FOR ITERATION ON SECOND LL

        while(iterator1 != nullptr && iterator2 != nullptr){
            // ITERATE ON THE LIST 
            // AS LONG AS ONE IS NOT NULL
            // AND WHEN ONE IS NULL, STOP

            if(iterator1->Value == iterator2->Value){
                // if they are the same, keep going
                iterator1 = iterator1->Next;
                iterator2 = iterator2->Next;
                continue;
            }
            else{
                identical = false;
                break;
            }

        }

        // Here 
        // if two pointers are null, they are identical
        // if not, they are not identical

        if(iterator1 == nullptr && iterator2 == nullptr && identical == true){
            return IDENTICAL;
            // if one of the pointer is not null
            // it means they are of different length
        }
        else{
            return DISTINCT;
        }
    }
}

void LinkedList::insertMultipleValues(vector<int>& values){
    /*
        this method insert multiple values at once
        to the linked list
    */

    for ( int counter = 0; counter < values.size(); counter++){

        this->insertEnd(values[counter]);
    }
    
    return;
}


void LinkedList::testFunctionality(){
    /*
        tests the functionality of the areIdentical() function
    */

   /* TEST 1 */

    cout << "TEST 1" << endl;

    LinkedList* ll11 = new LinkedList();
    vector<int> values11{9,101,309,411};
    ll11->insertMultipleValues(values11);

    LinkedList* ll12 = new LinkedList();
    vector<int> values12 {9,101, 309, 411};
    ll12->insertMultipleValues(values12);

    cout << "List1: "; ll11->printList();
    cout << "List2: "; ll12->printList();

    cout << "Expected: True" << endl;

    cout << "Result: ";
    bool result1 = LinkedList::areIdentical(ll11, ll12);
    if(result1 == true){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }

    /* TEST 2 */

    cout << "TEST 2" << endl;

    LinkedList *ll21 = new LinkedList();
    vector<int> values21{1,2,3,4};
    ll21->insertMultipleValues(values21);

    LinkedList *ll22 = new LinkedList();
    vector<int> values22{1,2,3};
    ll22->insertMultipleValues(values22);

    cout << "List1: ";
    ll21->printList();
    cout << "List2: ";
    ll22->printList();

    cout << "Expected: False" << endl;

    cout << "Result: ";
    bool result2 = LinkedList::areIdentical(ll21, ll22);
    if (result2 == true)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }

    /* TEST 3 */

    cout << "TEST 3" << endl;

    LinkedList *ll31 = new LinkedList();
    vector<int> values31;
    ll31->insertMultipleValues(values31);

    LinkedList *ll32 = new LinkedList();
    vector<int> values32{4,7,109,181,1000,34};
    ll32->insertMultipleValues(values32);

    cout << "List1: ";
    ll31->printList();
    cout << "List2: ";
    ll32->printList();

    cout << "Expected: False" << endl;

    cout << "Result: ";
    bool result3 = LinkedList::areIdentical(ll31, ll32);
    if (result3 == true)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
}


int main(){

    LinkedList::testFunctionality();

    return 0;
}
