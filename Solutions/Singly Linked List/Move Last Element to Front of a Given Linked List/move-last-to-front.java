/*
    GEEKSFORGEEKS
        DATA STRUCTURES
            SINGLY LINKED LIST EXERCISE
    
    MOVE LAST ELEMENT TO FRONT OF A GIVEN LINKED LIST
    coded by Fatih Cinar
    on March 10th, 2020
*/


import java.util.Random;

class LinkedList
{
    public Node Head; 

    class Node
    {
        public int Value;
        public Node Next;

        public Node(){
            this.Next = null;
            this.Value = 0;
        }

        public Node(int mValue){
            this.Value = mValue;
            this.Next = null;
        }
    }

    public static void main(String[] args){

        LinkedList.TesterFunction();

    }

    public LinkedList(){
        this.Head = null;
    }

    public static LinkedList getRandomLinkedList(){

        LinkedList newList = new LinkedList();

        Random rand = new Random();

        final int maximumLength = 15;
        final int lengthLinkedList = rand.nextInt(maximumLength);
        
        int length = lengthLinkedList;

        if(length == 0){
            
            newList.Head = null;

            return newList;
        }
        else{

            int randomChosenValue = 0;
            final int maximumValue = 250;

            while(length >= 0){

                randomChosenValue = rand.nextInt(maximumValue);
                newList.insertEnd(randomChosenValue);

                length--;
            }

            return newList;
        }
        
        
    }

    public void insertEnd(int mValue){

        Node newNode = new Node(mValue);

        if(this.Head == null){
            this.Head = newNode;
        }
        else{

            Node iterator = this.Head;

            while(iterator.Next != null){

                iterator = iterator.Next;
            }

            iterator.Next = newNode;
        }

        return;

    }


    public void print(){

        if(this.Head == null){
            System.out.println("Empty List!");
            return;
        }
        else{
            Node iterator = this.Head;

            while(iterator != null){

                System.out.print(iterator.Value);
                System.out.print(" ");

                iterator = iterator.Next;
            }

            System.out.println("");
        }

    }


    public void moveLastNodeToFront(){
        /*
            This function moves the last node to front of the linked list
        */

        if(this.Head == null){
            // Empty Linked List
            return;
        }

        if(this.Head.Next == null){
            // Only one value
            return;
        }


        Node previous = null;
        Node iterator = this.Head;

        while(iterator.Next != null){

            previous = iterator;
            iterator = iterator.Next;
        }

        // iterator = last node
        // previous = second last node

        // Break the link at the second last node

        previous.Next = null;

        // make the last node new head node
        Node oldHead = this.Head;

        this.Head = iterator;

        iterator.Next = oldHead;

        return;
    }

    public static void TesterFunction(){
        /*
            This function tests the functionality of the linked list
        */

        Random rand = new Random(); 

        final int howManyTests = rand.nextInt(4) + 1;

        for(int test = 1; test <= howManyTests; test++){
            String testLabel = "--------" + "TEST " + String.valueOf(test) + "--------" ;
            System.out.println(testLabel);

            LinkedList newList = LinkedList.getRandomLinkedList();

            newList.print();

            int circleTimes = rand.nextInt(4) + 2;
            for(int i = 0; i < circleTimes; i++){
                newList.moveLastNodeToFront();
                newList.print();
            }

        }
    
    }


}
