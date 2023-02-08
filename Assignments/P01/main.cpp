/*****************************************************************************
*                    
*  Author:           Daniel Hernandez
*  Email:            dhernandez1023@my.msutexas.edu
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Spring 2023
* 
*  Description:
*        The program creates a linked list vector class that has 
*        four different ways to initialize a vector. This vector
*        class also has methods that allow the user to manipulate
*        data in the linked list.
* 
*  Files:            
*    main.cpp    :driver program
*    input.dat   :input file w/ numbers
*    test.out    :output file
*****************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

struct Node{
  public:
    int data;
    Node* next;

  // default constructor
  Node() {
    data = 0;
    next = nullptr;
  }

  // overloaded constructor
  Node(int x){
    data = x;
    next = nullptr;
  }
};

/**
 * Vector
 * 
 * Description:
 *      This class 
 * 
 * Public Methods:
 *                Vector()
 *                Vector(int array[], int size)
 *                Vector(string fileName)'
 *                Vector(const Vector &v1)
 *      void      pushFront(int val)
 *      void      pushFront(Vector v2)
 *      void      pushRear(int val)
 *      void      pushRear(Vector v2)
 *      void      inOrderPush(int val)
 *      int       popFront()
 *      int       popRear()
 *      int       popAt(int loc)
 *      int       find(int val)
 *      void      print(ofstream &outfile)
 * 
 * Private Methods:
 *      Node* head    // initializes head of linked list
        Node* tail    // initializes tail of linked list
 * 
 * Usage: 
 * 
 *      Vector(v1)            // initializes a vector v1
 *      Vector(array,size)    // reads array & size into a vector
 *      Vector(fileName)      // reads a file into a vector
 *      Vector(Vector v1)     // adds a current vector in a new vector
 *      v1.pushFront(val)     // pushes val to front of list
 *      v1.pushFront(v2)      // pushes entire list into the front of 
 *                            // a new one
 *      v1.pushRear(val)      // pushes val to rear of list
 *      v1.pushRear(v2)       // pushes entire list into the rear of
 *                            // a new one
 *      v1.inOrderPush(val)   // pushes val into correct spot in list
 *                            // (descending & ascending)
 *      v1.popFront()         // pops front of list
 *      v1.popRear()          // pops rear of list
 *      v1.popAt(val)         // pops val at a certain index in list
 *      v1.find(val)          // will search for index of val
 *      print(outfile)        // prints to outfile     
 */
class Vector{
  private:
    Node* head;
    Node* tail;

  public:

  Vector(){
    head = nullptr;
    tail = nullptr;
  }

  Vector(int array[], int size){
    head = nullptr;
    tail = nullptr;

    for(int i = 0; i < size; i++){
      pushRear(array[i]);
    }
  }

  Vector(string fileName){
    int num;
    head = nullptr;
    tail = nullptr;
    ifstream infile;
    infile.open(fileName);

    while(!infile.eof()){
      infile >> num;
      pushRear(num);
    }
  }

  Vector(const Vector &v1){
    head = nullptr;
    tail = nullptr;

    Node* temp = v1.head;

    while(temp != nullptr){
      this->pushRear(temp->data);
      temp = temp->next;
    }
  }


  /**
  * Public : pushFront
  * 
  * Description:
  *      This function will push val to the front of the 
  *      list.
  * 
  * Params:
  *      int val  :  # to be pushed to front
  * 
  * Returns:
  *      Returns nothing
  */
  void pushFront(int val){
    Node* temp = new Node(val);

    if(head == nullptr)
    {
      head = temp;
      tail = temp;
    }
    else{
      temp->data = val;
      temp->next = head;

      head = temp;
    }
  }


  /**
  * Public : pushFront
  * 
  * Description:
  *      This function will push another list in front
  *      of the current list
  * 
  * Params:
  *      Vector v2  :  list to be pushed in front of current
  * 
  * Returns:
  *      Returns nothing
  */
  void pushFront(Vector v2){
    Node* temp = v2.tail;

    v2.tail->next = this->head;
    this->head = v2.head;
  }


  /**
  * Public : pushRear
  * 
  * Description:
  *      This function will push a val to the rear of the list
  * 
  * Params:
  *      int val  :  # to be pushed to rear
  * 
  * Returns:
  *      Returns nothing
  */
  void pushRear(int val){
    Node* temp = new Node(val);
    
    if(head == nullptr)
    {
      head = temp;
      tail = temp;
    }
    else{
      temp->data = val;
      tail->next = temp;

      tail = temp;
    }
  }

  /**
  * Public : pushRear
  * 
  * Description:
  *      This function will push another list in the rear
  *      of the current list.
  * 
  * Params:
  *      Vector v2  :  other list being pushed into currents rear (lol)
  * 
  * Returns:
  *      Returns nothing
  */
  void pushRear(Vector v2){
    Node* temp = v2.head;

    while(temp != nullptr){
      this->pushRear(temp->data);
      temp = temp->next;
    }
  }

  /**
  * Public : inOrderPush
  * 
  * Description:
  *      This function adds a val to the correct location
  *      in the list by number order.
  * 
  * Params:
  *      int val  :  # being put in order
  * 
  * Returns:
  *      Returns nothing
  */
  void inOrderPush(int val){
    Node* temp = new Node(val);

    if(head == nullptr){
      head = temp;
      tail = temp;
    }
    else if (temp->data < head->data){
      pushFront(temp->data);
    }
    else if (temp->data > tail->data){
      pushRear(temp->data);
    }
    else{
      Node* travel = head;

      while(travel->next->data < temp->data){
        travel = travel->next;
      }

      temp->next = travel->next;
      travel->next = temp;
    }
  }

  /**
  * Public : popFront
  * 
  * Description:
  *      This function will pop the value at the beginning of the list
  * 
  * Params:
  *      -
  * 
  * Returns:
  *      Returns the value that was removed from the front
  */
  int popFront(){
    int poppedValue;
    Node* temp = new Node();

    temp = head;
    head = head->next;
    poppedValue = temp->data;
    delete temp;
    return poppedValue;
  }

  /**
  * Public : popRear
  * 
  * Description:
  *      This function will pop the value at the rear of the list
  * 
  * Params:
  *      -
  * 
  * Returns:
  *      Returns the value that was popped from the rear
  */
  int popRear(){
    Node* traverse = new Node();
    Node* previous = nullptr;
    traverse = head;

    int poppedValue;

    while(traverse->next != nullptr){
      previous = traverse;
      traverse = traverse->next;
    }

    poppedValue = traverse->data;
    delete traverse;
    traverse = nullptr;
    previous->next = nullptr;
    return poppedValue;
  }

  /**
  * Public : popAt
  * 
  * Description:
  *      This function will pop a value at the location passed in.
  * 
  * Params:
  *      int loc  :  location of # being popped
  * 
  * Returns:
  *      Returns the number that was popped
  */
  int popAt(int loc){
    int index = 0;
    int num;
    Node* traverse = head;

    if(loc == 0){
      return popFront();
    }
    else{
      while(traverse->next != nullptr){
        traverse = traverse->next;
        index++;
        
        if(index == loc){
          num = traverse->data;
          return num;
          delete traverse;
          traverse = nullptr;
        }
      }
    } 
  }

  /**
  * Public : find
  * 
  * Description:
  *      This function will find the val passed in.
  * 
  * Params:
  *      int val  :  # being searched for
  * 
  * Returns:
  *      Returns the index of where the # is located
  */
  int find(int val){
    Node* traverse = head;
    int index = 0;

    while(traverse != nullptr){
      if(traverse->data == val){
        return index;
      }
      traverse = traverse->next;
      index++;
    }
    return -1; // If val is not found
  }

  /**
  * Public : print
  * 
  * Description:
  *      This function will print the lists to console and
  *      to the outfile
  * 
  * Params:
  *      ofstream &outfile  :  name of outfile
  * 
  * Returns:
  *      Returns nothing
  */
  void print(ofstream &outfile){
    Node* temp = head;

    outfile << "[";
    cout << "[";
    while (temp != nullptr)
    {
      outfile << temp->data;
      cout << temp->data;
      if(temp->next != nullptr){
      outfile << ", ";
      cout << ", ";
      }
      temp = temp->next;
    }
    outfile << "]" << endl;
    cout << "]" << endl;
  }

};

int main() {
ofstream outfile;
outfile.open("test.out");
int x = 0;

// Heading for the console print
cout << "Daniel Hernandez" << endl;
cout << "2/8/2023" << endl;
cout << "Spring 2143\n" << endl;

// Heading for the outfile print
outfile << "Daniel Hernandez" << endl;
outfile << "2/8/2023" << endl;
outfile << "Spring 2143\n" << endl;

Vector v1;
v1.pushFront(18);
v1.pushFront(20);
v1.pushFront(25);
v1.pushRear(18);
v1.pushRear(20);
v1.pushRear(25);
v1.print(outfile);
// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};
Vector v2(A,5);
v2.print(outfile);
// // [11, 25, 33, 47, 51]

v2.pushFront(9);
v2.inOrderPush(27);
v2.pushRear(63);
v2.print(outfile);
// [9, 11, 25, 27, 33, 47, 51, 63]

v1.pushRear(v2);
v1.print(outfile);
// [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

x = v1.popFront();
x = v1.popFront();
x = v1.popFront();
v1.print(outfile);
// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
outfile << x << endl;
cout << x << endl;
// 18

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.print(outfile);
// [18, 20, 25, 9, 11, 25, 27, 33]
outfile << x << endl;
cout << x << endl;
// 47

x = v2.popAt(3);
v2.print(outfile);
// [9, 11, 25, 33, 47, 51, 63]
outfile << x << endl;
cout<<x<<endl;
// 27

x = v2.find(51);
outfile << x << endl;
cout<<x<<endl;
// 5

x = v2.find(99);
outfile << x << endl;
cout<<x<<endl;
// -1

Vector v3(v1);
v3.print(outfile);
// [18, 20, 25, 9, 11, 25, 27, 33]

v3.pushFront(v2);
v3.print(outfile);
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

Vector v4("input.dat");
v4.pushRear(v3);
v4.print(outfile);
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

outfile.close();
}  