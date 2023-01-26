/*****************************************************************************
*
*  Author:           Daniel Hernandez
*  Email:            dhernandez1023@my.msutexas.edu
*  Label:            A03
*  Title:            Basic Project Organization
*  Course:           CMPS 2143
*  Semester:         Spring 2023
*
*  Description:
*           This program implements a queue using an array. The user will be 
*           able to create, write a name, and choose a size for the queue. 
*           The use of pop and push will also be available to edit the integers
*           stored within the queue.
*
*  Usage:
*       - $ ./main filename
*
*  Files:
*       main.cpp    : driver program
*****************************************************************************/


#include <iostream>

using namespace std;

/**
 * Class: CircularArrayQue
 *
 * Description:
 *      This class will create a queue and allow for the use of pop and push to add and remove
 *      items.
 *
 * Public Methods:
 * 
 *      void      Push(int item)
 *      int       Pop()
 *
 * Private Methods:
 * 
 *      void      init(int size)
 *      bool      Full()
 *
 * Usage:
 *
 *      CircularArrayQue [UserChosenName](size)    :    Allows for the queue to be created.
 *                                                      User will choose name and size of queue
 */
class CircularArrayQue {
private:
    int* Container;     // Pointer to allocate dynamic array for the queue
    int Front;          // front integer of the queue
    int Rear;           // rear integer of the queue
    int QueSize;        // items in the queue
    int CurrentSize;    // current size of the queue

    /**
     * Private : init
     *
     * Description:
     *      This function will initialize the queue with a size of 0 integers.
     *
     * Params:
     *       
     *        [int] size    :   The size of the queue (init. to 0)
     *
     * Returns:
     * 
     *      Function is a void. Returns nothing.
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    /**
     * Private : Full
     *
     * Description:
     *      This function will determine if the queue is full or not and return
     *      true or false.
     *
     * Params:
     *
     * 
     *
     * Returns:
     * 
     *      If CurrentSize == QueSize is T or F.
     */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }


    /**
     * Public : Push
     *
     * Description:
     *      This function will push an integer to the rear of the queue.
     *
     * Params:
     *
     *        [int] item    :    The integer being added to the queue
     *
     * Returns:
     * 
     *      Function is a void. Returns nothing.
     */
    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        }
        else {
            cout << "FULL!!!!" << endl;
        }
    }


    /**
     * Public : Pop
     *
     * Description:
     *      This function will pop an integer from the front of the queue.
     *
     * Params:
     *
     *      [int] temp    :    Will hold the front of the queue
     *
     * Returns:
     *      temp    :    The new front of the queue
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream& operator<<(ostream& os, const CircularArrayQue& other);
};

ostream& operator<<(ostream& os, const CircularArrayQue& other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 *
 * For this program, the main driver was used to test the CircularArrayQue class
 *
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}