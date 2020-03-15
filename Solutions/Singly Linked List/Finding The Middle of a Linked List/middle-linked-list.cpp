/*
    GEEKSFORGEEKS
        DATA STRUCTURES
            SINGLY LINKED LIST EXERCISE

    FINDING THE MIDDLE OF A LINKED LIST

    coded by Fatih Cinar
    on March 16th, 2020
*/

#include <iostream>
using namespace std;

class Node
{
    public:
        int Value;
        Node* Next;
    public:
        Node(); // default constructor
        Node(int value); // custom constructor
};

class LinkedList
{
    private:
        Node* head; // head pointer of the linked list
    
    private:
        bool isEmpty(); // figures out whether the linked list is empty or not

    public:
        LinkedList(); // default constructor
        ~LinkedList(); // destructor for memory releases
        void insertEnd(int value); // inserts at the end of the linked list
        void printList(); // prints the whole linked list to the screen
        
        Node* getMiddleElement(); // gets the middle element of the linked list, i.e. address

    public:
        static LinkedList* getRandomLinkedList(); // creates a randomly-filled linked list for testing
        
        static void TestFunctionality(); // Tests the functionality of the getMiddleElement() function

};


Node::Node(){
    // Default constructor of Node Class

    const int DEFAULT_VALUE = 0;

    this->Next = nullptr;
    this->Value = DEFAULT_VALUE;
}

Node::Node(int value){
    /*
        Custom consturctor for Node class
        create the node with an initial value
    */

    this->Next = nullptr;
    this->Value = value;

}

LinkedList::LinkedList(){
    /*
        Default constructor for LinkedList Class
    */

    this->head = nullptr; // make it safe first

}

Node* LinkedList::getMiddleElement(){
    /*
        This method will return the middle element in the linked list
    */

    /*
        ALGORITHM
        # Use two pointers 
            one moves fast
            other moves slow
            fast means 2 steps
            slow means 1 step
        # when you stop, slow pointer shows the middle
    */


    if( !this->isEmpty() ){
        // CASE 2 LINKED LIST IS NOT EMPTY 

        Node* slow = this->head;
        Node* fast = this->head; 
        // Start from the head pointer

        Node* middle = nullptr; // figure this out and return this
        
        while(fast != nullptr  && fast->Next != nullptr){
            // as long as fast is not NULL and the same time
            // next of fast is not null
            
            slow = slow->Next;
            fast = fast->Next->Next;
            // keep iterating on the linked list

        }

        middle = slow; // the slow pointer points to the middle element now

        return middle;
    }
    else {
        // CASE 1: EMPTY LINKED LIST
        return nullptr; 
    }
}

LinkedList::~LinkedList(){
    /*
        This method gives back the all memory it has taken to the FREE POOL
    */


    if(this->isEmpty()){
        return;
    }
    else{
        // Visit Each Node and Release Memory One-by-One
        
        Node* nextOne = nullptr;
        Node* iterator = this->head;

        while(iterator != nullptr){
            
            nextOne = iterator->Next; // remember the next one

            iterator->Next = nullptr; // break the link

            delete iterator; // give it back to the free pool

            iterator = nextOne; // keep going

        }

    }
}

bool LinkedList::isEmpty(){
    /*
        This method figures out whether the linked list is empty or not
    */

    const bool EMPTY = true;
    const bool NOT_EMPTY = false;

    if(head == nullptr){
        return EMPTY;
    }
    else{
        return NOT_EMPTY;
    }
}

void LinkedList::insertEnd(int value){
    /*
        This method will insert the given value to the end of the linked list
    */

    //Create memory first
    Node* newNode = new Node(value);
    

    if(this->isEmpty()){
        // this is the first node
        head = newNode;
        return;
    }
    else{
        // iterate over linked list till the last node
        Node* iterator = head; 

        while(iterator->Next != nullptr){
            // get to the last node
            iterator = iterator->Next;
        }

        // iterator = last node
        iterator->Next = newNode;

        return;
    }

}


void LinkedList::printList(){
    /*
        This method print the linked list to the console
    */

    

    if(this->isEmpty()){

        cout << "Empty List!" << endl;
    }
    else{
        // Print all the elements one-by-one
        // by iterating over them

        Node* iterator = this->head;

        while(iterator != nullptr){
            cout << iterator->Value << " ";
            iterator = iterator->Next;
        }

        cout << endl;
        
        return;
    }
}

LinkedList* LinkedList::getRandomLinkedList(){
    /*
        This static class function will create a random-sized
        and randomly-filled linked list for testing purposes
    */

   // Create New Linked List
   LinkedList* newList = new LinkedList();

    const int maximumSizeItCanBe = 10;
    const int determinedSize = rand() % maximumSizeItCanBe + 3;
    
    // have at least 3 elements

    const int maximumValue = 200;

    int valueAdd;

    for(int count = 0; count < determinedSize; count++){

        valueAdd = rand() % maximumValue;
        newList->insertEnd(valueAdd);
    }

    return newList;
}


int main(){
 
    LinkedList::TestFunctionality();

    return 0;
}

void LinkedList::TestFunctionality(){
    /*
        This static class function tests the functionality
        of get-middle-element function 
        It runs test for each cases
    */

    Node* middleElement = nullptr;

    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;
    // CASE 1 : EMPTY LINKED LIST
    LinkedList* ll1 = new LinkedList();
    cout << "CASE 1 : EMPTY LINKED LIST" << endl;
    cout << "List: ";
    ll1->printList();

    middleElement = ll1->getMiddleElement();
    if(middleElement == nullptr){
        cout << "Empty List, there is not any middle element!" << endl;
    }

    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;



    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;
    // CASE 2 : ONE ELEMENT LINKED LIST
    LinkedList* ll2 = new LinkedList();
    ll2->insertEnd(109);

    cout << "CASE 2 : ONE ELEMENT LINKED LIST" << endl;
    cout << "List: ";
    ll2->printList();    

    middleElement = ll2->getMiddleElement();
    cout << "Middle: " << middleElement->Value << endl;

    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;



    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;
    // CASE 3 : TWO ELEMENTS LINKED LIST
    LinkedList* ll3 = new LinkedList();
    ll3->insertEnd(301);
    ll3->insertEnd(405);

    cout << "CASE 3: TWO ELEMENTS LINKED LIST" << endl;
    cout << "List: ";
    ll3->printList();

    middleElement = ll3->getMiddleElement();
    cout << "Middle: " << middleElement->Value << endl;

    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;



    cout << endl 
         << "- - - - - - - - - - - - - - - - - - " << endl;
    // CASE 4 : THREE ELEMENTS
    LinkedList* ll4 = new LinkedList();
    ll4->insertEnd(67);
    ll4->insertEnd(34);
    ll4->insertEnd(12);

    cout << "CASE 4: THREE ELEMENTS LINKED LIST" << endl;
    cout << "List: ";
    ll4->printList();
    middleElement = ll4->getMiddleElement();
    cout << "Middle: " << middleElement->Value << endl;

    cout << endl
         << "- - - - - - - - - - - - - - - - - - " << endl;


    LinkedList* randomLL = nullptr;


    cout << " <<<<< RANDOM TEST CASES >>>>> " << endl;
    const int numberofTests = 4;
    for(int count = 1; count <= numberofTests; count++ ){
        cout << endl
             << "- - - - - - - - - - - - - - - - - - " << endl;
        
        randomLL = LinkedList::getRandomLinkedList();
        cout << "List: ";
        randomLL->printList();


        middleElement = randomLL->getMiddleElement();
        cout << "Middle: " << middleElement->Value << endl;

        cout << endl
             << "- - - - - - - - - - - - - - - - - - " << endl;

    
        randomLL->~LinkedList();

    }
}
