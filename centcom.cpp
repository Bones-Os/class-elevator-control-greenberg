
// UMBC - CMSC 341 - Spring 2025 - Proj1

/*
  File: centcom.cpp
  Author: Andrew Greenberg
  eMail: andrew82@umbc.edu
  Date: 2/16/25
  Desc: this file holds all member function definitions for the CentCom and Elevator classes
*/

#include "centcom.h"

//Name: CentCom (only constructor, takes parameters that have default values of 0)
//Preconditions: parameters should not be negative
//Postconditions: creates a CentCom object with the parameters given
CentCom::CentCom(int numElevators, int buildingID){
  // override passed values and make them 0 if they are negative
  if (numElevators < 0) {
    numElevators = 0;
  }
  if (buildingID < 0) {
    buildingID = 0;
  }

  // set all values to passed and default values
  m_id = buildingID;
  m_numElevators = numElevators;

  // initialize the elevator list based on the number of elevators
  if (numElevators == 0) {
    m_elevatorsList = nullptr;
  }
  else {
    m_elevatorsList = new Elevator*[numElevators];
  }
  
  // allocate memory for the list of elevators
  for (int i = 0; i < numElevators; i++) {
    m_elevatorsList[i] = new Elevator(i); // set current element to a new elevator with id
                                            //matching its index in the elevator list
  }
}

//Name: ~CentCom (destructor)
//Precondition: the CentCom object exists
//Postcondition: all member variables get reset to default values and all memory deallocated
CentCom::~CentCom(){
  // delete all of the elevators in the list
  for (int i = 0; i < m_numElevators; i++) {
    delete m_elevatorsList[i]; // delete the elevator
    m_elevatorsList[i] = nullptr; // reset the pointer to the elevator
  }

  // delete the array/list itself
  delete[] m_elevatorsList;

  // reset member variables
  m_id = -1;
  m_numElevators = 0;
  m_elevatorsList = nullptr;  
}

//Name: addElevator
//Preconditions: passed parameters are valid for an elevator
//Postconditions: adds the specified elevator and returns true if successful, else does not
                //add the elevator and returns false
bool CentCom::addElevator(int ID, int bottomFloor, int topFloor){
  // exit function if the elevator is of invalid ID (doesn't exist or isn't the next ID)
  if (ID < 0 or ID > m_numElevators) {
    return false;
  }

  // exit the function if the floors for the elevator are nonsensical
  if (topFloor < bottomFloor) {
    return false;
  }

  // check if an elevator with the passed ID already exists
  if (ID >= 0 and ID < m_numElevators) {
    // delete old elevator
    delete m_elevatorsList[ID];
    m_elevatorsList[ID] = nullptr;

    m_numElevators--; // when adding an elevator, increment the count, so decrement if replacing
  }
  else {
    // adjust size of the elevator list and variable storing its size
    Elevator** tempList = m_elevatorsList;

    m_elevatorsList = nullptr;
    m_elevatorsList = new Elevator*[m_numElevators + 1];

    // copy over the old list
    for (int i = 0; i < m_numElevators; i++) {
      m_elevatorsList[i] = tempList[i];
    }

    // delete the temporary list
    delete [] tempList;
  }

  // add in the new elevator
  m_elevatorsList[ID] = new Elevator(ID);

  // populate the floors of the new elevator
  m_elevatorsList[ID]->setUp(bottomFloor, topFloor);

  // correct the number of elevators
  m_numElevators++;

  return true;
}

//Name: getElevator
//Preconditions: passed ID exists
//Postconditions: returns pointer of elevator if found, else nullptr
Elevator* CentCom::getElevator(int ID){
  // return nullptr if the ID doesn't exist
  if (ID < 0 or ID >= m_numElevators) {
    return nullptr;
  }

  // return a pointer to the target elevator
  return m_elevatorsList[ID];
}

//Name: setSecure
//Preconditions: N/A
//Postconditions: sets the floor of elevator ID to secure or not secure
bool CentCom::setSecure(int ID, int floorNum, bool yes_no){
  // exit the function if the elevator doesn't exist
  if (ID < 0 or ID >= m_numElevators) {
    return false;
  }

  // exit if the target elevator doesn't have any floors
  if (m_elevatorsList[ID]->m_bottom == nullptr or m_elevatorsList[ID]->m_top == nullptr) {
    return false;
  }
  
  // exit the function if the elevator doesn't have the target floor
  if (floorNum < m_elevatorsList[ID]->m_bottom->m_floorNum
      or floorNum > m_elevatorsList[ID]->m_top->m_floorNum) {

    return false;
  }
  
  // change the value of m_secure for the elevator's floor
  Floor* curr = m_elevatorsList[ID]->m_bottom; // for iterating thru the floors
  for (int i = m_elevatorsList[ID]->m_bottom->m_floorNum;
       i < floorNum; i++) { // get curr to the target floor
    curr = curr->m_next;
  }
  curr->m_secured = yes_no;
  return true;
}

//Name: clearEmergency
//Preconditions: given elevator ID exists
//Postconditions: sets the emergency state to false and returns true only if successful
bool CentCom::clearEmergency(int ID){
  // exit the function if the elevator doesn't exist
  if (ID < 0 or ID >= m_numElevators) {
    return false;
  }

  // set the target elevator's emergency state to false
  m_elevatorsList[ID]->m_emergency = false;
  return true;
}


//Name: Elevator (overloaded constructor with just one parameter, which has a default value)
//Preconditions: passed integer is a valid ID
//Postconditions: an empty Elevator object is created with default-value member variables
Elevator::Elevator(int ID){
  const int DEFAULT_ID = 0; // the default value for m_id should be, if passed an invalid one
  
  // if passed ID is valid, change it, otherwise set it to 0
  if (ID > INVALIDID) {
    m_id = ID;
  }
  else {
    m_id = DEFAULT_ID;
  }
  
  // initialize the rest of the member variables to their default values
  m_bottom = nullptr;
  m_top = nullptr;
  m_upRequests = nullptr;
  m_downRequests = nullptr;
  m_currentFloor = nullptr;
  m_moveState = IDLE;
  m_doorState = CLOSED;
  m_emergency = false;
  m_load = 0;
}

//Name: ~Elevator (destructor)
//Precondition: N/A
//Postcondition: change all member variables back to default values and deallocate all memory
Elevator::~Elevator(){
  // delete all the linked lists
  deleteLinkedList(m_upRequests);
  deleteLinkedList(m_downRequests);
  deleteLinkedList(m_bottom);
  m_top = nullptr; // nodes were deleted with above call, but do set it to nullptr
  m_currentFloor = nullptr; // deleted its floor when deleting m_bottom
  
  // reinitialize values to default
  m_id = INVALIDID;
  m_moveState = IDLE;
  m_doorState = CLOSED;
  m_emergency = false;
  m_load = 0;
}

//Name: clear
//Preconditions: N/A
//Postconditions: deallocates all memory in the Elevator object and sets member variables back
                //to default values
void Elevator::clear(){
  // *same as the destructor*

  // delete all the linked lists
  deleteLinkedList(m_upRequests);
  deleteLinkedList(m_downRequests);
  deleteLinkedList(m_bottom);
  m_top = nullptr; // nodes were deleted with above call, but do set it to nullptr
  m_currentFloor = nullptr; // deleted its floor when deleting m_bottom

  // reinitialize values to default
  m_id = INVALIDID;
  m_moveState = IDLE;
  m_doorState = CLOSED;
  m_emergency = false;
  m_load = 0;
}

//Name: setUp
//Preconditions: the elevator is empty
//Postconditions: creates floors from passed firstFloor to lastFloor in the LL pointed to
                //by m_bottom and m_top. If the elevator isn't empty, no action is taken
void Elevator::setUp(int firstFloor, int lastFloor){
  // cancel the function if the elevator is not empty or if the last floor is before the first
   //or if they are equal (there is only one floor - so why need an elevator?? You don't)
  if (m_top != nullptr or firstFloor >= lastFloor) {
    return;
  }
  
  m_bottom = new Floor(firstFloor); // start the LL / set up m_bottom
  m_bottom->m_previous = nullptr;
  Floor* curr = m_bottom; // to iterate thru the LL
  
  
  // from firstFloor to lastFloor, create the new floor and set it's m_next and m_previous
   //appropriately
  for (int i = (firstFloor + 1); i <= lastFloor; i++) {
    //cout << "curr: " << curr << endl;
    curr->m_next = new Floor(i); // create the next floor, set m_next
    curr->m_next->m_previous = curr; // set new floor's m_previous
    curr = curr->m_next; // move along curr
  }

  // set up the last floor
  m_top = curr;
  curr->m_next = nullptr;

  // put the elevator at the bottom floor, so it is somewhere
  m_currentFloor = m_bottom;
}

//Name: insertFloor
//Preconditions: passed a valid floor (whose number is one below the current *m_bottom's)
//Postconditions: if valid, the function inserts the passed floor at the bottom and returns
                //true, else false
bool Elevator::insertFloor(int floor){
  // case 1: elevator is empty. add the floor and set the current floor to it (so the elevator
   //exists somewhere)
  if (m_bottom == nullptr) {
    m_bottom = new Floor(floor);
    m_top = m_bottom;
    m_currentFloor = m_bottom;
    return true;
  }
  
  // case 2: elevator is not empty; exit if the passed floor is invalid
  if (floor != (m_bottom->m_floorNum - 1)) {
    return false;
  }
 
  // add the floor, adjust m_bottom and floors' pointers
  m_bottom->m_previous = new Floor(floor);
  m_bottom->m_previous->m_next = m_bottom;
  m_bottom = m_bottom->m_previous;

  return true;
}

//Name: checkSecure
//Preconditions: the floor exists
//Postconditions: the function returns if the floor is secure or not, or false if there is an
                //error
bool Elevator::checkSecure(int floor){
  Floor* curr = nullptr; // floor pointer used to traverse thru the LL

  // error (return false) if there are no floors
  if (m_bottom == nullptr) {
    return false;
  }

  // there must be floors, so look for the one with num "floor"
  curr = m_bottom;
  while (curr != nullptr) {
    if (curr->m_floorNum == floor) {
      return curr->m_secured;
    }
    curr = curr->m_next;
  }
  
  // did not find the target floor, failed
  return false;
}

//Name: pushEmergency
//Preconditions: N/A
//Postconditions: m_emergency is set to true, if true was passed (there is no reason to call
                //with false, nothing will happen then)
void Elevator::pushEmergency(bool pushed){
  if (m_emergency == false) {
    m_emergency = pushed;
  }
  else {
    // a passenger can't clear an emergency, and setting it to true while it already is does
     //nothing, so exit the function
    return;
  }
}

//Name: pushButton
//Preconditions: passed a floor that isn't already in the queue and exists in the building
//Postconditions: adds the floor to the proper queue, and may update the move state. returns
                //true if successful, false otherwise
bool Elevator::pushButton(int floor){
  Floor* curr = nullptr; // used to iterate thru the LLs
  Floor* temp = nullptr; // ephemeral pointer to save the new floor, if being added
  
  // exit if the passed floor does not exist
  if (floor < m_bottom->m_floorNum or floor > m_top->m_floorNum) {
    return false;
  }

  // exit if the passed floor is a secured floor (first have to navigate to the floor)
  curr = m_bottom;

  while (curr != nullptr and curr->m_floorNum != floor) {
    curr = curr->m_next;
  }

  if (curr->m_floorNum == floor and curr->m_secured) {
    return false; // can't add a secured floor
  }

  // exit if the passed floor is already in a queue

      //check down requests
  curr = m_downRequests;
  while (curr != nullptr) {
    if (curr->m_floorNum == floor) {
      return false;
    }
    curr = curr->m_next;
  }

      //check up requests
  curr = m_upRequests;
  while (curr != nullptr) {
    if (curr->m_floorNum == floor) {
      return false;
    }
    curr = curr->m_next;
  }

  // exit if the passed floor is the current floor
  if (m_currentFloor->m_floorNum == floor) {
    return false;
  }
  
  // add the floor to the proper queue
  if (floor > m_currentFloor->m_floorNum) { // up requests
    // if upRequests is empty, add it
    if (m_upRequests == nullptr) {
      m_upRequests = new Floor(floor);
      return true;
    }
    
    curr = m_upRequests;
    while (curr != nullptr and floor > curr->m_floorNum) {
      curr = curr->m_next;
    }
    
    // if the new floor should be last in upRequests
    if (curr == nullptr) {
      curr = m_upRequests;
      while (curr->m_next != nullptr) {
	curr = curr->m_next;
      }
      curr->m_next = new Floor(floor);
      curr->m_next->m_previous = curr;
      return true;
    }
    
    // insert the floor one before curr
    temp = new Floor(floor);
    temp->m_next = curr;

    if (curr->m_previous != nullptr) { // only adjust m_previous pointers if there is one
      temp->m_previous = curr->m_previous;
      curr->m_previous->m_next = temp;
    }
    else { // adding the new first node, adjust m_downRequests
      m_upRequests = temp;
    }
    curr->m_previous = temp;
    return true;
  }
  else { // down requests
    // if downRequests is empty, just add it in
    if (m_downRequests == nullptr) {
      m_downRequests = new Floor(floor);
      return true;
    }

    curr = m_downRequests;
    while (curr != nullptr and floor < curr->m_floorNum) {
      curr = curr->m_next;
    }

    // if it should be last in downRequests
    if (curr == nullptr) {
      curr = m_downRequests;
      while (curr->m_next != nullptr) {
	curr = curr->m_next;
      }
      curr->m_next = new Floor(floor);
      curr->m_next->m_previous = curr;
      return true;
    }

    // insert the floor one before curr
    temp = new Floor(floor);
    temp->m_next = curr;

    if (curr->m_previous != nullptr) { // only adjust m_previous pointers if there is one
      temp->m_previous = curr->m_previous;
      curr->m_previous->m_next = temp;
    }
    else { // adding the new first node, adjust m_downRequests
      m_downRequests = temp;
    }
    curr->m_previous = temp;
    return true;
  }  

  return false;
}

//Name: processNextRequest
//Preconditions: should be no emergency or overloaded elevator
//Postconditions: moves to the next requested floor and returns true, or false if it fails
bool Elevator::processNextRequest(){
  Floor* curr = nullptr; // to iterate thru main LL of floors
  Floor* temp = nullptr; // to assist in deleting a processed request
  
  // exit if there is an emergency
  if (m_emergency) {
    m_moveState = IDLE; // can't move in an emergency
    m_doorState = OPEN; // don't want to lock people inside the elevator in case of emergency
    return false;
  }
  
  // exit if the load is exceeded
  if (m_load > LOADLIMIT) {
    m_doorState = OPEN; // allow ppl to get off
    return false;
  }

  // exit if there are no requests
  if (m_downRequests == nullptr and m_upRequests == nullptr) {
    m_moveState = IDLE;
    return false;
  }

  // close the doors before moving
  m_doorState = CLOSED;
  
  // check the direction we're moving
  if (m_moveState == UP) { // go to next up request
    // see if there are anymore up requests
    if (m_upRequests != nullptr) {
      m_currentFloor = m_upRequests; // change current floor / move the elevator
      
      curr = m_bottom;
      while (curr != nullptr and curr->m_floorNum != m_upRequests->m_floorNum) {
	curr = curr->m_next;
      }
      m_currentFloor = curr; // adjust currentFloor
      m_doorState = OPEN; // let ppl get off/on

      // begin the process of deleting the processed request from the LL of requests
      if (m_upRequests->m_next != nullptr) {
	temp = m_upRequests->m_next;
      }
      
      m_upRequests->m_floorNum = 0;
      m_upRequests->m_previous = nullptr;
      m_upRequests->m_next = nullptr;
      m_upRequests->m_secured = false;
      delete m_upRequests;
      m_upRequests = temp;

      // stop going up if there are no more requests above
      if (m_upRequests == nullptr) {
	m_moveState = IDLE;
      }
    }
    return true;
  }
  else if (m_moveState == DOWN) { // go to next down request - copied from above, paired if statement
    
    // see if there are anymore down requests
    if (m_downRequests != nullptr) {
      m_currentFloor = m_downRequests; // change current floor / move the elevator

      curr = m_bottom;
      while (curr != nullptr and curr->m_floorNum != m_downRequests->m_floorNum) {
	curr = curr->m_next;
      }
      m_currentFloor = curr; // adjust currentFloor
      m_doorState = OPEN; // let ppl get off/on

      // begin the process of deleting the processed request from the LL of requests
      if (m_downRequests->m_next != nullptr) {
	temp = m_downRequests->m_next;
      }

      m_downRequests->m_floorNum = 0;
      m_downRequests->m_previous = nullptr;
      m_downRequests->m_next = nullptr;
      m_downRequests->m_secured = false;
      delete m_downRequests;
      m_downRequests = temp;

      // stop going down if there are no more requests below
      if (m_downRequests == nullptr) {
	m_moveState = IDLE;
      }
    }
    return true;
  }
  else { // elevator is idle. go to nearest requested floor
    // check if there are any more requests. If so, just change the moveState to match the
     //closest next request and then recursion to avoid repeating TOO much code
    if (m_upRequests == nullptr and m_downRequests == nullptr) {
      return false; // nothing to do
    }
    else if (m_upRequests != nullptr and m_downRequests != nullptr) {
      // decide which is closer, set direction appropriately and recursive call
      if (m_upRequests->m_floorNum - m_currentFloor->m_floorNum > m_currentFloor->m_floorNum 
	  - m_downRequests->m_floorNum) {

	// go down first, it's closer
	m_moveState = DOWN;
	return processNextRequest();
      }
      else {
	// go up first, it's closer or they are equidistant
	m_moveState = UP;
	return processNextRequest();
      }
    }
    else if (m_upRequests != nullptr) {
      // only have upRequests left, change direction and recursive call
      m_moveState = UP;
      return processNextRequest();
    }
    else if (m_downRequests != nullptr) {
      // only have down requests left, change direction and recursive call
      m_moveState = DOWN;
      return processNextRequest();
    }
    // shouldn't be able to make it to here, so exit with failure
    return false; 
  }
}

//Name: enter
//Preconditions: passed int is positive
//Postconditions: the passed load will be added to the elevator's load
void Elevator::enter(int load){
  // can't have a negative load. Would just call exit() instead
  if (load < 0) {
    return;
  }

  // load must be positive or 0, so add it
  m_load += load;
}

//Name: exit
//Preconditions: passed load is positive
//Postconditions: passed load will be subtracted from the elevator's load, which can't be neg.
int Elevator::exit(int load){
  // subtract passed load from m_load
  m_load -= load;

  // make sure m_load isn't negative, if it is then set to 0
  if (m_load < 0) {
    m_load = 0;
  }

  return m_load;
}

//Name: deleteLinkedList
//Preconditions: passed LL holds nodes that are Floor objects
//Postconditions: LL will be deallocated and values reinitialized 
void Elevator::deleteLinkedList(Floor* &LL) {
  Floor* curr = nullptr; // used to iterate through all of the LLs
   
  curr = LL;

  // case 0: empty LL
  if (curr == nullptr) {
    return;
  }		      
  
  // case 1: more than one floor in LL
  // iterate thru the list (while the next floor exists)
  while (curr != nullptr and curr->m_next != nullptr) {
 
    // move to next floor
    curr = curr->m_next;
    
    // reinitialize values before deleting the floor
    curr->m_previous->m_floorNum = 0;
    curr->m_previous->m_next = nullptr;
    curr->m_previous->m_previous = nullptr;
    curr->m_previous->m_secured = false;

    // delete the (second-to-) last floor
    delete curr->m_previous;
    curr->m_previous = nullptr;
  }

  // case 2: just one floor in LL
  // should also be a continuation of case 1, which leaves one floor un-deleted
  if (curr != nullptr and curr->m_next == nullptr) {
 
    // reset values to default
    curr->m_previous = nullptr;
    curr->m_next = nullptr;
    curr->m_secured = false; 
    curr->m_floorNum = 0;

    // delete last floor
    delete curr;
    curr = nullptr;
  }
  
  // set passed LL to nullptr
  LL = nullptr;
}


void Elevator::dump(){
    if (m_moveState == IDLE) cout << "Elevator " << m_id << " is idle.";
    else if (m_moveState == UP) cout << "Elevator " << m_id << " is moving up.";
    else if (m_moveState == DOWN) cout << "Elevator " << m_id << " is moving down.";
    cout << endl;
    if (m_emergency == true) cout << "someone pushed the emergency button!" << endl;
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top" << endl;
        while(temp->m_previous != nullptr){
	    cout << temp->m_floorNum;
	    if (temp->m_floorNum == m_currentFloor->m_floorNum) cout << " current ";
            if (temp->m_secured == true) cout << " secured ";
            cout << endl;
            temp = temp->m_previous;
        }
        cout << temp->m_floorNum;
        if (temp->m_floorNum == m_currentFloor->m_floorNum) cout << " current ";
        if (temp->m_secured == true) cout << " secured ";
        cout << endl;
        cout << "Bottom" << endl;
    }
}
