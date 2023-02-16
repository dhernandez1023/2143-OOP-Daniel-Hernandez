/*****************************************************************************
 *
 *  Author:           Daniel Hernandez
 *  Email:            dhernandez1023@my.msutexas.edu
 *  Label:            P02
 *  Title:            MyVector Class 2
 *  Course:           CMPS 2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        This program creates a MyVector class using linked list.
 *        The vectors can be initialized and manipulated in various
 *        different ways. This program also overloads C++ operators
 *        like <<, +, -, *, =, ==, and [].
 *
 *  Files:
 *      main.cpp     : driver of the program
 *      output.txt   : output file
 *****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000 // infinity

using namespace std;

// Node for our linked list
struct Node {
  int data;
  Node *next;

  Node(int x) {
    data = x;
    next = NULL;
  }
};

/**
 * MyVector
 * 
 * Description:
 *      This class has 4 constructors. Using these 4 constructors
 *      the user can manipulate the linked list vector with various
 *      different methods.
 * 
 * Public Methods:
 *                MyVector()
 *                MyVector(int A[], int aSize)
 *                MyVector(string FileName)
 *                MyVector(const MyVector &other)
 *      void      init()
 *      void      inorderPush(int x)
 *      void      sortList()
 *      void      pushFront(int x)
 *      void      pushFront(const MyVector &other)
 *      void      pushRear(const MyVector &other)
 *      bool      pushAt(int i, int x) 
 *      void      pushRear(int x)
 *      Node*     _find(int location)
 * 
 * Private Methods:
 *       void      _inOrderPush(int x)
 * 
 */
class MyVector {
private:
  Node *head; // base pointer of list
  Node *tail;
  int size; // Will keep track of list size
  static ofstream fout;
  string fileName;
  bool sorted;

  /**
   * @brief Private version of inOrder push.
   *
   * @param x
   */
  void _inorderPush(int x) {
    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (curr->data > x) { // loop to find proper location
      prev = curr;
      curr = curr->next;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
  }

public:
  /**
   * @brief Find a value in the linked list.
   *
   * @returns value at location
   */
  Node *_Find(int location) {
    Node *travel = head;
    int index = 0;

    while (travel && location--) {

      travel = travel->next;
    }
    return travel;
  }

  /**
   * @brief Default constructor
   *
   */
  MyVector() { init(); }

  /**
   * @brief Overloaded Constructor
   *
   * @param int   *A - pointer to array
   * @param int   aSize - size of array
   */
  MyVector(int A[], int aSize) {
    init();

    for (int i = 0; i < aSize; i++) {
      pushRear(A[i]);
    }
  }

  /**
   * @brief Overloaded Constructor
   *
   * @param string FileName - file to open and read
   *
   * Assumes infile will contain numbers only delimited by spaces or
   * new lines.
   */
  MyVector(string FileName) {
    init();

    ifstream fin;
    int x = 0;

    fin.open(FileName);
    while (!fin.eof()) {
      fin >> x;
      pushRear(x);
    }
  }

  /**
   * @brief Copy Constructor
   *
   * @param MyVector &other
   */
  MyVector(const MyVector &other) {
    init();

    Node *temp = other.head;

    while (temp) {
      pushRear(temp->data);
      temp = temp->next;
    }
  }

  /**
   * @brief - Initialize the data members so we don't
   *      have duplicate lines in each constructor.
   *
   */
  void init() {
    head = tail = nullptr;
    fileName = "";
    size = 0;
    sorted = 0;
  }

  /**
   * @brief Public version of inOrder push.
   *
   * @param x
   */
  void inorderPush(int x) {
    if (!sorted) {
      sortList();
    }

    if (!head) {
      pushFront(x); // call push front for empty list (or pushRear would work)
    } else if (x < head->data) {
      pushFront(x); // call push front if x is less than head
    } else if (x > tail->data) {
      pushRear(x); // call push rear if x > tail
    } else {
      _inorderPush(x); // call private version of push in order
    }
  }

  /**
   * @brief Sort the current values in the linked list.
   *
   * @returns None
   */
  void sortList() {
    Node *newFront = head;
    while (newFront->next) {
      Node *smallest = newFront;
      Node *current = newFront;
      int minimum = INF;
      while (current) {
        if (current->data < minimum) {
          smallest = current;
          minimum = current->data;
        }
        current = current->next;
      }
      smallest->data = newFront->data;
      newFront->data = minimum;
      newFront = newFront->next;
    }
    sorted = true;
  }

  /**
   * @brief Add value to front of list.
   *
   * @param x
   */
  void pushFront(int x) {
    Node *tempPtr = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
      head = tail = tempPtr;
      // otherwise adjust head pointer
    } else {
      tempPtr->next = head;
      head = tempPtr;
    }
    size++;
  }

  /**
   * @brief This method loads values from 'other' list in 'this' list.
   *          It loads an array first so we can process the values in
   *          reverse so they end up on 'this' list in the proper order.
   *          If we didn't use the array, we would reverse the values
   *          from the 'other' list.
   *
   * @depends - Uses `pushFront(int)`
   * @param MyVector& other
   * @return None
   */
  void pushFront(const MyVector &other) {
    Node *otherPtr = other.head;         // get copy of other lists head
    int *tempData = new int[other.size]; // allocate memory to hold values

    // load other list into array
    int i = 0;
    while (otherPtr) {
      tempData[i] = otherPtr->data;
      otherPtr = otherPtr->next;
      ++i;
    }

    // process list in reverse in order to keep them
    // in their original order.
    for (int i = other.size - 1; i >= 0; i--) {
      pushFront(tempData[i]);
    }
  }

  /**
   * @brief -  Add 'other' list's values to end of 'this' list.
   * @note - Uses `pushRear(int)`
   * @param MyVector& other
   * @return None
   */
  void pushRear(const MyVector &other) {
    Node *otherPtr = other.head; // get copy of other lists head

    while (otherPtr) { // traverse and add
      pushRear(otherPtr->data);
      otherPtr = otherPtr->next;
    }
  }

  /**
   * @brief Push value onto list at soecified position, if it exists.
   *
   * @param int i - location index
   * @param inr x - value to add
   * @return bool - true add successful / false add failed
   */
  bool pushAt(int i, int x) {
    if (i >= size) {
      return false;
    }

    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (i > 0) { // loop to find proper location
      prev = curr;
      curr = curr->next;
      i--;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
    return true;
  }

  /**
   * @brief - Add value to rear of list
   *
   * @param int x - value to be added
   * @return None
   */
  void pushRear(int x) {
    Node *tempPtr = new Node(x);

    if (!head) {
      head = tail = tempPtr;

    } else {
      tail->next = tempPtr;
      tail = tempPtr;
    }
    size++; // add to size of list
  }

  /**
   * @brief - Overloads + operator and adds
   *          vectors.
   *
   * @param   Vector - Right hand side
   *
   * @return   V   : Vector after adding
   */
  MyVector operator+(const MyVector &Vector) {
    MyVector V;
    Node *shorter;
    Node *longer;
    if (Vector.size < this->size) {
      shorter = Vector.head;
      longer = this->head;
    } else {
      longer = Vector.head;
      shorter = this->head;
    }

    // Pushes data after addition to rear of V
    while (shorter != nullptr) {
      V.pushRear(shorter->data + longer->data);
      shorter = shorter->next;
      longer = longer->next;
    }

    // Pushes to rear of V the remaining data of Vector
    while (longer != nullptr) {
      V.pushRear(longer->data);
      longer = longer->next;
    }
    return V;
  }

  /**
   * @brief - Overloads - operator and subtracts
   *          vectors.
   *
   * @param   Vector - Right hand side
   *
   * @return   V   : Vector after subtracting
   */
  MyVector operator-(const MyVector &Vector) {
    MyVector V;
    Node *shorter;
    Node *longer;
    if (Vector.size < this->size) {
      shorter = Vector.head;
      longer = this->head;
    } else {
      longer = Vector.head;
      shorter = this->head;
    }

    if (Vector.size < this->size) {
      // Pushes data after subtraction to rear of V
      while (shorter != nullptr) {
        V.pushRear(longer->data - shorter->data);
        shorter = shorter->next;
        longer = longer->next;
      }

      // Pushes to rear of V the remaining data of vector
      while (longer != nullptr) {
        V.pushRear(longer->data);
        longer = longer->next;
      }
    } else {
      // Pushes data after subtraction to rear of V
      while (shorter != nullptr) {
        V.pushRear(shorter->data - longer->data);
        shorter = shorter->next;
        longer = longer->next;
      }

      // Pushes to rear of V the remaining data of vector
      while (longer != nullptr) {
        V.pushRear(longer->data);
        longer = longer->next;
      }
    }
    return V;
  }

  /**
   * @brief - Overloads * operator and multiplies
   *          vectors.
   *
   * @param   Vector - Right hand side
   *
   * @return   V   : Vector after multiplying
   */
  MyVector operator*(const MyVector &Vector) {
    MyVector V;
    Node *shorter;
    Node *longer;
    if (Vector.size < this->size) {
      shorter = Vector.head;
      longer = this->head;
    } else {
      longer = Vector.head;
      shorter = this->head;
    }
    // Pushes data after multiplication to rear of V
    while (shorter != nullptr) {
      V.pushRear(shorter->data * longer->data);
      shorter = shorter->next;
      longer = longer->next;
    }

    // Pushes to rear of V the remaining data of vector
    while (longer != nullptr) {
      V.pushRear(longer->data);
      longer = longer->next;
    }
    return V;
  }

  /**
   * @brief - Overloads = operator and sets the right hand
   *          side to the left hand side.
   *
   * @param   Vector - Right hand side
   *
   * @return   V   : Vector after setting RHS to LHS
   */
  MyVector operator=(const MyVector &Vector) {
    MyVector V;
    Node *traveling = Vector.head;   // Node to travel vector
    MyVector *copy = new MyVector(); // Will hold copy of vector

    // While loop that will push Vectors data into copy's rear
    while (traveling != nullptr) {
      copy->pushRear(traveling->data);
      traveling = traveling->next;
    }

    // While loop that pushes copy's data into V's rear
    // and returns V
    this->head = copy->head;
    Node *traveling2 = copy->head;
    while (traveling2 != copy->head) {
      V.pushRear(traveling2->data);
      traveling2 = traveling2->next;
    }
    return V;
  }

  /**
   * @brief - Overloads == operator and returns if comparison
   *          is true or false.
   *
   * @param   Vector - Right hand side
   *
   * @return   true (1)   : If comparison is true
   *           false (0)  : If comparison is false
   */
  bool operator==(const MyVector &Vector) {
    Node *lhs = head;
    Node *rhs = Vector.head;

    // While loop that will return true if vectors are equal
    // and false if not equal.
    while (lhs != nullptr) {
      if (lhs->data != rhs->data) {
        return false;
      }
      lhs = lhs->next;
      rhs = rhs->next;
    }
    return true;
  }

  /**
   * @brief - Overloads [] operator and allows MyVector
   *          to be treated as an array.
   *
   * @params - int location
   *
   * @return    temp->data  : Int stored at location
   */
  int &operator[](int location) {
    Node *temp = _Find(location);

    return temp->data;
  }

  /**
   * @brief - Overloads << (ostream) operator and allows
   *          for easy console printing
   *
   * @return   os
   */
  friend ostream &operator<<(ostream &os, const MyVector &Vector) {
    Node *temp = Vector.head; // temp pointer copies head

    os << "[";
    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      os << temp->data; // print data from Node
      if (temp->next) {
        os << ",";
      }
      temp = temp->next; // move to next Node
    }
    os << "]";
    os << endl;
    return os;
  }

  /**
   * @brief - Overloads << (ofstream) operator and allows
   *          for easy output file printing
   *
   * @return   of
   */
  friend ofstream &operator<<(ofstream &of, const MyVector &Vector) {
    Node *temp = Vector.head; // temp pointer copies head

    of << "[";
    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      of << temp->data; // print data from Node
      if (temp->next) {
        of << ",";
      }
      temp = temp->next; // move to next Node
    }
    of << "]";
    of << endl;
    return of;
  }

  /**
   * @brief Destroy the My Vector object
   *
   */
  ~MyVector() {
    Node *curr = head;
    Node *prev = head;

    while (curr) {
      prev = curr;
      curr = curr->next;
      // cout << "deleting: " << prev->data << endl;
      delete prev;
    }
  }
};

int main() {
  int a1[] = {1, 2, 3, 4, 5};
  int a2[] = {10, 20, 30};

  MyVector v1(a1, 5);
  MyVector v2(a2, 3);

  ofstream fout;
  fout.open("output.txt");

  // console heading
  cout << "Daniel Hernandez\n";
  cout << "2/15/2023\n";
  cout << "Spring 2143\n\n";

  // output file heading
  fout << "Daniel Hernandez\n";
  fout << "2/15/2023\n";
  fout << "Spring 2143\n\n";

  cout << v1[2] << endl << endl;
  fout << v1[2] << endl << endl;
  // writes out 3 to console and output file.

  v1[4] = 9;
  // v1 now = [1,2,3,4,9]

  cout << v1 << endl;
  // writes out [1,2,3,4,9] to console.

  fout << v1 << endl;
  // writes out [1,2,3,4,9] to your output file.

  MyVector v3 = v1 + v2;
  cout << v3 << endl;
  fout << v3 << endl;
  // writes out [11,22,33,4,9] to console and output file.

  v3 = v1 - v2;
  cout << v3 << endl;
  fout << v3 << endl;
  // writes out [-9,-18,-27,4,9] to console and output file.

  v3 = v2 - v1;
  cout << v3 << endl;
  fout << v3 << endl;
  // writes out [9,18,27,4,9] to console and output file.

  v3 = v2 * v1;
  cout << v3 << endl;
  fout << v3 << endl;
  // writes out [10,40,90,4,9] to console and output file.

  v3 = v1 * v2;
  cout << v3 << endl;
  fout << v3 << endl;
  // writes out [10,40,90,4,9] to console and output file.

  cout << (v2 == v1) << endl << endl;
  fout << (v2 == v1) << endl << endl;
  // writes 0 to console and output file (false).

  MyVector v4 = v1;
  cout << (v4 == v1) << endl;
  fout << (v4 == v1) << endl;
  // writes 1 to console and output file (true).
}