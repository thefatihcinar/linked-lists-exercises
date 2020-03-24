/*
    GEEKSFORGEEKS
        DATA STRUCTURES
            SINGLY LINKED LIST EXERCISE
    FLATTENIG A LINKED LIST

    coded by Fatih Cinar
    on March 24th, 2020
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Node
{
    public:
        int Value;
        Node* Right;
        Node* Down; 
    public:
        Node(); // default constructor
        Node(int value); // create a new node with a value
};

class LinkedList
{
    private:
        Node* head; // head Pointer of the linked list

    /* FUNCTIONALITIES */
    private:
        void releaseAllMemory(); // releases all the memory of a linked list of any type
        void printAsTable(); // private print function that prints the linked list as table - 2D linked list
        void printAsVector(); // prints the linked list as a vector like 1D format 

        LinkedList* convertVectorToLinkedList(vector<int>& values);
        // get a vector of integers
        // and create a singly-one dimensional linked list out of it
        void insertOneDimensionalLinkedList(LinkedList* toBeInsertedLL); 
        // insert a linked list inside a linked list, create a table form

        int determineTheType(); // determines whether the linked list is 1D or 2D linked list 


    public:
        LinkedList(); // default constructor
        bool isEmpty(); // figures out whether the linked list empty or not
        Node* getHeadNode(); // get the head node of the linked list
        ~LinkedList(); // destructor of a linked list of any type, releases all the memory allocated
        void print(); // prints the linked list to the console, figuring out its type
        void insertInAscendingOrder(int value); // insert bigger value at the end, i.e. sorts ascending order
        void insertValuesAsColumn(vector<int>& values); // take an array of values and insert them as a column in the table
        void insertSingleValueAtEnd(int value); // insert a single value in downwards direction at the end of the linked list
};

class FlattenEngine
{
    public:
        static LinkedList* flattenGivenLinkedList(LinkedList* thelinkedList);
        // this method flattens and sorts a given 2D linked-list
};

enum TypeInformation
{
    NO_DIMENSION = 0,
    ONE_DIMENSIONAL = 1,
    TWO_DIMENSIONAL = 2
};

enum ContainerInformation
{
    EMPTY = true,
    NOT_EMPTY = false
};


LinkedList::LinkedList(){
    /*  
        default constructor for the linked list class
    */

    this->head = nullptr; // make it null, guaranteed

}


bool LinkedList::isEmpty(){
    /*
        figures out whether the given linked list is empty or not
    */

    if(this->head == nullptr){
        
        return EMPTY;
    }
    else
    {
        return NOT_EMPTY;
    }
    
}


Node* LinkedList::getHeadNode(){
    /*  
        this method gives the head of the desired linked list
    */

    return this->head;
}



void LinkedList::releaseAllMemory(){
    /*  
        this method releases all the memory allocated by the linked list efficiently
    */

    if(this->isEmpty()){
        return;
    }
    else{
        Node* right = this->head; // iterator for right nodes
        Node* down = nullptr; // iterator for down nodes

        Node* nextOneRight = nullptr; // for remembering the next node for right nodes
        Node*  nextOneDown = nullptr; // for remembering the next node for down nodes

        while(right != nullptr){
            // as long as all the main nodes are not done releasing

            nextOneRight = right->Right;  // remember the next node in the right

            down = right->Down; // get the node in the below direction 
            // might be null 

            while( down != nullptr){
                // as long as down is not null 
                // keep releasing the memory

                // remember next one below
                nextOneDown = down->Down; // might be null

                delete down; 

                down = nextOneDown; // keep going
            }

            // Release the right one as well

            delete right;

            right = nextOneRight; // keep going in the right also

        }
    }

}



Node::Node(){
    /*
        a default constructor for the node class 
    */
    
    enum Information
    {
        DEFAULT_VALUE = 0
    };

    this->Value = DEFAULT_VALUE;

    // make the right & down pointers NULL , Guarantee it 

    this->Right = nullptr;
    this->Down = nullptr;
}

Node::Node(int value){
    /*
        a custom constructor for the Node class
        create a node with a value
    */

    // Make the rigth & down pointers NULL, Guarantee it

    this->Value = value;

    this->Right = nullptr;
    this->Down = nullptr;
}


void LinkedList::insertSingleValueAtEnd(int value){
    /* 
        This method inserts a single value to a ONE-DIMENSINAL LINKED LIST
        at the end of it 
    */

    // create new node 
    Node* newNode = new Node(value);

    if(this->isEmpty()){
        // LINKED LIST EMPTY CASE
        this->head = newNode;

        return;

    }
    else{
        // LINKED LIST IS NOT EMPTY CASE

        // go to the end of the linked list
        Node* iterator = this->head;
        
        while(iterator->Down != nullptr){
            
            iterator = iterator->Down;
        }   

        // we are at the end

        iterator->Down = newNode; // inserted

        return;
    }
}


int LinkedList::determineTheType(){
    /*
        This method figures out the type of the linked list
        whether its a vector i.e. 1D
        or its a table i.e. 2D
    */

    if(this->isEmpty()){
        return NO_DIMENSION;
    }

    bool ONE_D = true;
    // assuming it's one-dimensional

    // try to disprove what you've just assumed
    Node* iterator = this->head;
    while(iterator != nullptr){
        // go as far right as possible, untill its null
        // check every node whether or not they have a downward node or not

        if(iterator->Down != nullptr){
            // if any of the nodes have a down node 
            // it's 2D
            ONE_D = false;
            break;
        }
        else{
            iterator = iterator->Right;
            continue;
        }

    }

    switch(ONE_D){
        case true:
            return ONE_DIMENSIONAL;
        case false:
            return TWO_DIMENSIONAL;
    }
}


void LinkedList::printAsVector(){
    /*
        this method print the linked list as a vector 
        in ONE-DIMENSIONAL FORMAT
    */

    if(this->isEmpty()){
        // LINKED LIST EMPTY CASE
        cout << "Empty Linked List !" << endl;
        return;
    }
    else{
        // LINKED LIST IS NOT EMPTY CASE
        
        Node* iterator = this->head;
        // start iterating, start from the head node

        while( iterator != nullptr ){

            cout << iterator->Value << " ";

            iterator = iterator->Right; // keep iterating thru the right, 1D APPROACH IN RIGHTWARD
        }

        cout << endl;

        return;
    }
}

void LinkedList::printAsTable(){
    /*
        this method print the linked list in a table format 
    */

    if(this->isEmpty()){

        cout << "Empty Linked List!" << endl;
        return;
    }

    // as long as the are nodes at the right
    // first the columns as row 
    
    int column = 1; // column number

    Node* iterator = this->head;

    while(iterator != nullptr){

        cout << "COLUMN " << column << ":  " ; 

        Node* innerIterator = iterator;
        // go deep, go down
        while(innerIterator != nullptr){

            cout << innerIterator->Value << " ";
            
            innerIterator = innerIterator->Down;
        }

        column++; // talk about the next column

        iterator = iterator->Right;

        cout << endl;
    }
}

void LinkedList::print(){
    /*
        this method print the linked list
        figuring out its type whether its a vector or a table
        prints accordingly
    */

    if(this->isEmpty()){
        // LINKED LIST EMPTY CASE

        cout << "Empty List!" << endl;
        return;
    }

    int type = this->determineTheType(); // get the type 

    switch(type){

        case ONE_DIMENSIONAL:
            this->printAsVector();
            return;
        case TWO_DIMENSIONAL:
            this->printAsTable();
            return;
    }

}

void LinkedList::insertValuesAsColumn(vector<int>& values){
    /*
        this method gets a bunch of integer values 
        and inserts them into a linked list as a column 
        by converting the linked list to a table approact
    */

    // FIRST WE HAVE TO CONVERT THE GIVEN VECTOR TO A ONE-DIMENSIONAL DOWNWARD LINKED LIST
    LinkedList* list = this->convertVectorToLinkedList(values);
    // we got the one-dimensional downward linked list

    // SECOND ADD THIS ONE DIMENSINAL LINKED LIST TO THE MAIN LINKED LIST AS A COLUMN
    
    if(this->isEmpty()){
        // CASE 1: LINKED LIST IS EMPTY
        this->head = list->getHeadNode();
        return;
    }
    else{
        // CASE 2: LINKED LIST IS NOT EMPTY

        // go as far as you can to insert this column

        Node* iterator = this->head;

        while(iterator->Right != nullptr){
            iterator = iterator->Right;
        }

        // now we are the righest position
        // now add this new node
        iterator->Right = list->getHeadNode();
        return;
    }

 
}

LinkedList* LinkedList::convertVectorToLinkedList(vector<int>& values){
    /*
        this private method gets a vector of integers and turns them
        into one dimensional linked list
    */

    LinkedList* newLinkedList = new LinkedList();

    for (int coun = 0; coun < values.size(); coun++)
    {
        // get all the values and insert it to the linked list
        // in the downward direction

        newLinkedList->insertSingleValueAtEnd(values[coun]);
    }

    return newLinkedList; 

}

void LinkedList::insertOneDimensionalLinkedList(LinkedList* oneDimensionalList){
    /*
        this method is given a one-dimensional downward linked list
        and it inserts it the main linked list
        as a column
    */

    if(this->isEmpty()){
        // LINKED LIST EMPTY CASE   

        this->head = oneDimensionalList->getHeadNode(); 
        
        return;
    }
    else{
        // LINKED LIST IS NOT EMPTY CASE

        // go to the end of the linked list and insert there

        Node* iterator = this->head;

        while( iterator->Right != nullptr){
            // go to the last node at the right

            iterator = iterator->Right;
        }

        // at the last node

        iterator->Right = oneDimensionalList->getHeadNode();

        return;
    }
}

/*
    void insertInAscendingOrder(int value); // insert bigger value at the end, i.e. sorts ascending order
*/


void LinkedList::insertInAscendingOrder(int value){
    /*
        this method inserts a given value to the linked list
        in one-dimensinal manner and to the right
        and insert in an ascending order
    */

    // create the new node first always
    Node* newNode = new Node(value);

    if(this->isEmpty()){
        // CASE 1 : LINKED LIST EMPTY
        this->head = newNode;

        return;
    }
    else{
        /*
            ALGORITHM
            # There are two pointers
                previous pointer
                iterator pointer = now pointer
                find the right place to insert the value using the iterator pointer
                and then complete the insertion process using previous pointer
        */
        Node* iterator = this->head;
        Node* previous = this->head; 

        // find the right place to insert 
        while( iterator != nullptr && value >= iterator->Value){
            // keep going as long as the newNode's value is greater
            previous = iterator;
            iterator = iterator->Right;
            
            // VERY IMPORTANT
            // IF ITERATOR IS NULL DO NOT TRY TO READ ITS VALUE !!

        }

        // Here we got the place right
        
        // CASE 2: AT THE END OF THE LINKED LIST
        if(iterator == nullptr){
            previous->Right = newNode; // inserted at the end of the linked list
            return;
        }
        // CASE 3: AT THE BEGINING OF THE LINKED LIST
        else if (previous == iterator){
            // In this case we know that the iterator has not moved actually
            Node* oldHead = this->head; // remember the old head
            this->head = newNode; // this new node is now the head
            newNode->Right = oldHead; // now it points to the old node
            return;
        }
        
        // INSERTION INTO THE MIDDLE OF THE LINKED LIST
        else{
            // we know the place to insert
            
            // THE PLACE THE ITERATOR POINTS TO IS THE PLACE TO INSERT
            // VERY IMPORTANT
            // SO TO INSERT THERE WE NEED TO USE PREVOUS POINTER

            previous->Right = newNode; // this is the place that the iterator shows
            newNode->Right = iterator; // now iterator is pointing to the one place further
            
            return;
        }
        

    }
}


LinkedList* FlattenEngine::flattenGivenLinkedList(LinkedList* theLinkedList){
    /*
        this class method gets a 2-Dimensional linked list
        and flattens it to a 1-dimensional linked list
        at the same time, sorting in an ascending order
    */

    if(theLinkedList->isEmpty()){
        // CASE : LINKED LIST IS EMPTY
    
        return nullptr;
    }
    else{
        /*
            ALGORITHM
            # send all the nodes to the sorting-insertion function
                first start iteration on the right direction
                and at each right node
                go deepest as you can
        */

       LinkedList* newList = new LinkedList(); 
       // This 1D Sorted Linked List will be returned

       Node* right = theLinkedList->getHeadNode();
       Node* down = nullptr;

       while( right != nullptr){
           // go rightest in this while loop
            down = right->Down; // get the first down node as well
            // might be null, remember

            // first give the right node to the new linked list
            newList->insertInAscendingOrder(right->Value);
            // go deepest you can
            while(down != nullptr){
                // as long as down is not null
                
                // give this node to the linked list
                newList->insertInAscendingOrder(down->Value);

                down = down->Down; // go deeper man
            }

            // Now go righter one more place
            right = right->Right; 
       }

       return newList; 
       // New 1D sorted linked list will be returned
    }
}


LinkedList::~LinkedList(){
    /*
        destructor function for the linked list class
        RELEASES ALL THE MEMORY ALLOCATED
        deals with both type of linked lists 
        both 1-dimensional and 2-dimensional
    */

    this->releaseAllMemory();

    return;
}


int main(){

    LinkedList* newList = new LinkedList();

    vector<int> column1{5,9,11};
    vector<int> column2{19,7};
    vector<int> column3{21};
    vector<int> column4{7,190,21};
    newList->insertValuesAsColumn(column1);
    newList->insertValuesAsColumn(column2);
    newList->insertValuesAsColumn(column3);
    newList->insertValuesAsColumn(column4);

    /* TRYINGH THE FUNCTIONALITY OF 
        FlattenEngine::flattenGivenLinkedList()

    */
    
    LinkedList* flattenedVersion1 = FlattenEngine::flattenGivenLinkedList(newList);

    cout << "Flattened Version: " ;
    flattenedVersion1->print();

    cout << endl;

    LinkedList* newList2 = new LinkedList();

    vector<int> column21{5,7,8,30};
    vector<int> column22{10,20};
    vector<int> column23{19,22,50};
    vector<int> column24{28,35,40,45};
    newList2->insertValuesAsColumn(column21);
    newList2->insertValuesAsColumn(column22);
    newList2->insertValuesAsColumn(column23);
    newList2->insertValuesAsColumn(column24);

    LinkedList* flattenedVersion2  = FlattenEngine::flattenGivenLinkedList(newList2);

    cout << "Flattened Version: ";
    flattenedVersion2->print();

    cout << endl;

    /* TRYING THE FUNCTIONALITY OF THE 
        insertInAscendingOrder()
    */
    /*

   LinkedList* testing1 = new LinkedList();

   testing1->insertInAscendingOrder(101); testing1->print();
   testing1->insertInAscendingOrder(79); testing1->print();
   testing1->insertInAscendingOrder(53);testing1->print();
   testing1->insertInAscendingOrder(21); testing1->print();
   testing1->insertInAscendingOrder(66); testing1->print();
   testing1->insertInAscendingOrder(100); testing1->print();
   testing1->insertInAscendingOrder(190); testing1->print();
   testing1->insertInAscendingOrder(590); testing1->print();
   
    */
    return 0;
}
