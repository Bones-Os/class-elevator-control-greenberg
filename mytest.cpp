/*
  File: mytest.cpp
  Author: Andrew Greenberg
  eMail: andrew82@umbc.edu
  Date: 2/17/25
  Desc: file holding the Tester class, used to test CentCom and Elevator
*/

#include "centcom.h"
#include <iostream>
#include <string>
using namespace std;

// define constants
const string FAIL_STATEMENT = "*****TEST FAILED: ";
const string PASS_STATEMENT = "     TEST PASSED: ";


class Tester {
public:
  // elevator tests
  bool testElevatorConstructorNormal();
  bool testElevatorConstructorEdge();
  bool testElevatorConstructorError();

  bool testElevatorSetUpNormal();
  bool testElevatorSetUpEdge();
  bool testElevatorSetUpError();

  bool testElevatorInsertFloorNormal();
  bool testElevatorInsertFloorEdge();
  bool testElevatorInsertFloorError();

  bool testElevatorCheckSecureNormal();
  bool testElevatorCheckSecureEdge();
  bool testElevatorCheckSecureError();

  bool testElevatorPushEmergencyNormal();
  bool testElevatorPushEmergencyError();

  bool testElevatorPushButtonNormalDown();
  bool testElevatorPushButtonNormalUp();
  bool testElevatorPushButtonEdgeMin();
  bool testElevatorPushButtonEdgeMax();
  bool testElevatorPushButtonEdgeEqual();
  bool testElevatorPushButtonError();

  bool testElevatorProcessNextRequestNormalIdle();
  bool testElevatorProcessNextRequestNormalMoving();
  bool testElevatorProcessNextRequestEdge();
  bool testElevatorProcessNextRequestErrorEmpty();
  bool testElevatorProcessNextRequestErrorEmergency();
  bool testElevatorProcessNextRequestErrorLoad();

  bool testElevatorEnterNormal();
  bool testElevatorEnterEdge();
  bool testElevatorEnterError();

  bool testElevatorExitNormal();
  bool testElevatorExitEdge();
  bool testElevatorExitError();

  // centcom tests
  bool testCentComConstructorNormal();
  bool testCentComConstructorEdge();
  bool testCentComConstructorError();

  bool testCentComAddElevatorNormalNew();
  bool testCentComAddElevatorNormalReplace();
  bool testCentComAddElevatorEdge();
  bool testCentComAddElevatorError();

  bool testCentComGetElevatorNormal();
  bool testCentComGetElevatorEdgeMin();
  bool testCentComGetElevatorEdgeMax();
  bool testCentComGetElevatorError();

  bool testCentComSetSecureNormal();
  bool testCentComSetSecureEdgeMin();
  bool testCentComSetSecureEdgeMax();
  bool testCentComSetSecureError();

  bool testCentComClearEmergencyNormal();
  bool testCentComClearEmergencyEdgeMin();
  bool testCentComClearEmergencyEdgeMax();
  bool testCentComClearEmergencyError();
};


//Name: testElevatorConstructorNormal
//Case: normal
//Expected result: an elevator object is created with member variables containing
                 //correct default values and passed ID
bool Tester::testElevatorConstructorNormal() {
  const int ID = 3; // int to be passed to the default constructor
  const Floor* DEFAULT_POINTER = nullptr;
  
  Elevator elevator(ID);

  // confirm that the Elevator object contains the correct values
  if (elevator.m_id == ID and elevator.m_bottom == DEFAULT_POINTER
      and elevator.m_top == DEFAULT_POINTER and elevator.m_upRequests == DEFAULT_POINTER
      and elevator.m_downRequests == DEFAULT_POINTER
      and elevator.m_currentFloor == DEFAULT_POINTER and elevator.m_moveState == IDLE
      and elevator.m_doorState == CLOSED and elevator.m_emergency == false
      and elevator.m_load == 0) {

    cout << PASS_STATEMENT << "Elevator's constructor passed the normal case" << endl;
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's constructor failed the normal case" << endl;
  return false;
}

//Name: testElevatorConstructorEdge
//Case: edge
//Expected result: an elevator object is created with member variables containing
//correct default values and passed ID (0)
bool Tester::testElevatorConstructorEdge() {
  const int ID = 0; // int to be passed to the default constructor
  const Floor* DEFAULT_POINTER = nullptr;

  Elevator elevator(ID);

  // confirm that the Elevator object contains the correct values
  if (elevator.m_id == ID and elevator.m_bottom == DEFAULT_POINTER
            and elevator.m_top == DEFAULT_POINTER and elevator.m_upRequests == DEFAULT_POINTER
            and elevator.m_downRequests == DEFAULT_POINTER
            and elevator.m_currentFloor == DEFAULT_POINTER and elevator.m_moveState == IDLE
            and elevator.m_doorState == CLOSED and elevator.m_emergency == false
      and elevator.m_load == 0) {

    cout << PASS_STATEMENT << "Elevator's constructor passed the edge case" << endl;
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's constructor failed the edge case" << endl;
  return false;
}

//Name: testElevatorConstructorError
//Case: error
//Expected result: an elevator object is created with member variables containing
//correct default values and an ID of 0
bool Tester::testElevatorConstructorError() {
  const int ID = -10; // int to be passed to the default constructor
  const int EXPECTED_ID = 0; // int value that should be taken as the elevator's ID

  const Floor* DEFAULT_POINTER = nullptr;

  Elevator elevator(ID);

  // confirm that the Elevator object contains the correct values
  if (elevator.m_id == EXPECTED_ID and elevator.m_bottom == DEFAULT_POINTER
            and elevator.m_top == DEFAULT_POINTER and elevator.m_upRequests == DEFAULT_POINTER
            and elevator.m_downRequests == DEFAULT_POINTER
            and elevator.m_currentFloor == DEFAULT_POINTER and elevator.m_moveState == IDLE
            and elevator.m_doorState == CLOSED and elevator.m_emergency == false
      and elevator.m_load == 0) {

    cout << PASS_STATEMENT << "Elevator's constructor passed the error case" << endl;
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's constructor failed the error case" << endl;
  return false;
}

//Name: testElevatorSetUpNormal
//Case: normal
//Expected result: empty elevator object gets filled with floors from the first to last floor
bool Tester::testElevatorSetUpNormal() {
  const int ID = 1; // ID of the elevator object
  const int INTERMEDIATE_FLOOR_A = 3; // floor after FIRST_FLOOR
  const int INTERMEDIATE_FLOOR_B = 4; // floor before LAST_FLOOR
  const int FIRST_FLOOR = 2; // starting number floor
  const int LAST_FLOOR = 5; // last floor (inclusive)
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);
  

  // check if all the floors are in elevator, and if the current floor isn't nullptr (the
   //elevator has to be somewhere) then return true or false
  if (elevator.m_bottom->m_floorNum == FIRST_FLOOR
      and elevator.m_bottom->m_next->m_floorNum == INTERMEDIATE_FLOOR_A 
      and elevator.m_top->m_previous->m_floorNum == INTERMEDIATE_FLOOR_B
      and elevator.m_top->m_floorNum == LAST_FLOOR
      and elevator.m_currentFloor == elevator.m_bottom) {

    cout << PASS_STATEMENT << "Elevator's SetUp passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's SetUp failed the normal case\n";
  return false;
}

//Name: testElevatorSetUpEdge
//Case: edge
//Expected result: nonempty elevator object doesn't get filled a second time
bool Tester::testElevatorSetUpEdge() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 2; // starting number floor
  const int LAST_FLOOR = 5; // last floor (inclusive)
  const int NEW_FIRST_FLOOR = 0; // starting floor number for second call of setUp
  const int NEW_LAST_FLOOR = 6; // last floor for the second call of setUp
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);
  elevator.setUp(NEW_FIRST_FLOOR, NEW_LAST_FLOOR);


  // check the first and last floor, to confirm they were not changed with the second
   //call of setUp
  if (elevator.m_bottom->m_floorNum != NEW_FIRST_FLOOR
      and elevator.m_top->m_floorNum != NEW_LAST_FLOOR) {

    cout << PASS_STATEMENT << "Elevator's SetUp passed the edge case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's SetUp failed the edge case\n";
  return false;
}

//Name: testElevatorSetUpError
//Case: error
//Expected result: the elevator object is left empty (if passed a greater number floor before
                 //the lesser one---if passed last_floor, first_floor
bool Tester::testElevatorSetUpError() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 2; // starting number floor
  const int LAST_FLOOR = 5; // last floor (inclusive)
  
  Elevator elevator(ID);

  elevator.setUp(LAST_FLOOR, FIRST_FLOOR); // pass values so that first > last
  
  // confirm that the elevator object remains empty
  if (elevator.m_bottom == nullptr
      and elevator.m_top == nullptr) {

    cout << PASS_STATEMENT << "Elevator's SetUp passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's SetUp failed the error case\n";
  return false;
}

//Name: testElevatorInsertFloorNormal
//Case: normal
//Expected result: the floor will be added at the head of the LL, or m_bottom
bool Tester::testElevatorInsertFloorNormal() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 0; // starting number floor
  const int LAST_FLOOR = 6; // last floor (inclusive)
  const int NEW_FLOOR = -1; // the floor to be inserted
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // insert the floor, and make sure the function think it succeeded before further testing
  if (!(elevator.insertFloor(NEW_FLOOR))) {
    cout << FAIL_STATEMENT << "Elevator's insertFloor failed the normal case\n";
    return false;
  }
  
  // check if there is a new m_bottom, and that the second floor is the old first one
  if (elevator.m_bottom->m_floorNum == NEW_FLOOR
      and elevator.m_bottom->m_next->m_floorNum == FIRST_FLOOR) {

    cout << PASS_STATEMENT << "Elevator's insertFloor passed the normal case\n";
    return true;
  }
  else {
    cout << FAIL_STATEMENT << "Elevator's insertFloor failed the normal case\n";
    return false;
  }
}

//Name: testElevatorInsertFloorEdge
//Case: edge
//Expected result: the floor will not be added (it already exists in the LL)
bool Tester::testElevatorInsertFloorEdge() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 0; // starting number floor
  const int LAST_FLOOR = 6; // last floor (inclusive)
  const int NEW_FLOOR = 0; // the floor to be inserted

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // try to insert the floor, and confirm that it was not added
  if (!(elevator.insertFloor(NEW_FLOOR))
      and elevator.m_bottom->m_next->m_floorNum != FIRST_FLOOR) {

    cout << PASS_STATEMENT << "Elevator's insertFloor passed the edge case\n";
    return true;
  }
  
  cout << FAIL_STATEMENT << "Elevator's insertFloor failed the edge case\n";
  return false;
}

//Name: testElevatorInsertFloorError
//Case: error
//Expected result: the floor will not be added (it is more than one floor below the bottom)
bool Tester::testElevatorInsertFloorError() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 0; // starting number floor
  const int LAST_FLOOR = 6; // last floor (inclusive)
  const int NEW_FLOOR = -2; // the floor to be inserted

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // try to insert the floor, and confirm that it was not added
  if (!(elevator.insertFloor(NEW_FLOOR))
      and elevator.m_bottom->m_floorNum != NEW_FLOOR) {

    cout << PASS_STATEMENT << "Elevator's insertFloor passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's insertFloor failed the error case\n";
  return false;
}

//Name: testElevatorCheckSecureNormal
//Case: normal
//Expected result: checkSecure will return the correct bool value
bool Tester::testElevatorCheckSecureNormal() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 1; // starting number floor
  const int SECOND_FLOOR = 2; // the second floor
  const int LAST_FLOOR = 5; // last floor (inclusive)
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // confirm that checkSecure returns the correct value
  if (elevator.checkSecure(SECOND_FLOOR) == elevator.m_bottom->m_next->m_secured) {
    cout << PASS_STATEMENT << "Elevator's checkSecured passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's checkSecured failed the normal case\n";
  return false;
}

//Name: testElevatorCheckSecureEdge
//Case: edge
//Expected result: checkSecure will return the correct bool value
bool Tester::testElevatorCheckSecureEdge() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 1; // starting number floor
  const int LAST_FLOOR = 5; // last floor (inclusive)

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // change the state of the last floor's m_secured to be true, for some variety in testing
  elevator.m_top->m_secured = true;

  // confirm that checkSecure returns the correct value
  if (elevator.checkSecure(LAST_FLOOR) == elevator.m_top->m_secured) {
    cout << PASS_STATEMENT << "Elevator's checkSecured passed the edge case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's checkSecured failed the edge case\n";
  return false;
}

//Name: testElevatorCheckSecureError
//Case: error
//Expected result: checkSecure will return the correct bool value
bool Tester::testElevatorCheckSecureError() {
  const int ID = 1; // ID of the elevator object
  const int FIRST_FLOOR = 1; // starting number floor
  const int LAST_FLOOR = 2; // last floor (inclusive)
  const int FAKE_FLOOR = -12; // floor that does not exist in the LL

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // change the state of the floor's m_secured to be true, to confirm that checkSecure is not
   //just returning the value of m_secured (false) and getting lucky
  elevator.m_bottom->m_secured = true;
  elevator.m_top->m_secured = true;

  // confirm that checkSecure returns the correct value
  if (elevator.checkSecure(FAKE_FLOOR) == false) {
    cout << PASS_STATEMENT << "Elevator's checkSecured passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's checkSecured failed the error case\n";
  return false;
}

//Name: testElevatorPushEmergencyNormal
//Case: normal
//Expected result: after calling pushEmergency(), m_emergency will be true
bool Tester::testElevatorPushEmergencyNormal() {
  const int ID = 1; // ID of the elevator
  const bool INPUT = true; // what pushEmergency should be passed
  
  Elevator elevator(ID);

  elevator.pushEmergency(INPUT);

  // confirm that m_emergency know holds INPUT
  if (elevator.m_emergency == INPUT) {
    cout << PASS_STATEMENT << "Elevator's pushEmergency passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's pushEmergency failed the normal case\n";
  return false;
}

//Name: testElevatorPushEmergencyError
//Case: error
//Expected result: after calling pushEmergency(), m_emergency will remain false
bool Tester::testElevatorPushEmergencyError() {
  const int ID = 1; // ID of the elevator
  const bool INPUT = false; // what pushEmergency should be passed

  Elevator elevator(ID);

  elevator.pushEmergency(INPUT);

  // confirm that m_emergency know holds INPUT
  if (elevator.m_emergency == INPUT) {
    cout << PASS_STATEMENT << "Elevator's pushEmergency passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's pushEmergency failed the error case\n";
  return false;
}

//Name: testElevatorPushButtonNormalDown
//Case: normal
//Expected result: pushButton() will correctly add the new floor request to down requests
bool Tester::testElevatorPushButtonNormalDown() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST = 2; // the parameter to be passed to pushButton
  
  Elevator elevator(ID);
  
  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // try to call pushButton
  if (elevator.pushButton(NEW_FLOOR_REQUEST) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the normal \"down\"  case\n";
    return false;
  }
  
  // check values to see that pushButton behaved correctly
  if (elevator.m_downRequests->m_floorNum != NEW_FLOOR_REQUEST) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the normal \"down\" case\n";
    return false;
  }

  cout << PASS_STATEMENT << "Elevator's pushButton passed the normal \"down\" case\n";
  return true;
}

//Name: testElevatorPushButtonNormalUp
//Case: normal
//Expected result: pushButton() will correctly add the new floor request to up requests
bool Tester::testElevatorPushButtonNormalUp() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST = 8; // the parameter to be passed to pushButton

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  
  elevator.m_currentFloor = curr;

  // try to call pushButton
  if (elevator.pushButton(NEW_FLOOR_REQUEST) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the normal \"up\"  case\n";
    return false;
  }

  // check values to see that pushButton behaved correctly
  if (elevator.m_upRequests->m_floorNum != NEW_FLOOR_REQUEST) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the normal \"up\" case\n";
    return false;
  }

  cout << PASS_STATEMENT << "Elevator's pushButton passed the normal \"up\" case\n";
  return true;
}

//Name: testElevatorPushButtonEdgeMin
//Case: edge
//Expected result: pushButton() will correctly add the new floor request to down requests, as
                 //the first one. Should not be in chronological order but numerical
bool Tester::testElevatorPushButtonEdgeMin() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 3; // parameter to be passed to pushButton (first call)
  const int NEW_FLOOR_REQUEST_2 = 2; // parameter to be passed to pushButton (second call)
  const int NEW_FLOOR_REQUEST_3 = 4; // parameter to be passed to pushButton (third call)
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // try to call pushButton, thrice
  if (elevator.pushButton(NEW_FLOOR_REQUEST_1) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\"  case\n";
    return false;
  }
  if (elevator.pushButton(NEW_FLOOR_REQUEST_2) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\"  case\n";
    return false;
  }
  if (elevator.pushButton(NEW_FLOOR_REQUEST_3) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\"  case\n";
    return false;
  }

  
  if (elevator.m_downRequests->m_floorNum != NEW_FLOOR_REQUEST_3) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\" case\n";
    return false;
  }
  if (elevator.m_downRequests->m_next->m_floorNum != NEW_FLOOR_REQUEST_1) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\" case\n";
    return false;
  }
  if (elevator.m_downRequests->m_next->m_next->m_floorNum != NEW_FLOOR_REQUEST_2) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"min\" case\n";
    return false;
  }
  
  cout << PASS_STATEMENT << "Elevator's pushButton passed the edge \"min\" case\n";
  return true;
}

//Name: testElevatorPushButtonEdgeMax
//Case: edge
//Expected result: pushButton() will correctly add the new floor request to up requests, as
                 //the first one. Should not be in chronological order but numerical
bool Tester::testElevatorPushButtonEdgeMax() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 7; // parameter to be passed to pushButton (first call)
  const int NEW_FLOOR_REQUEST_2 = 8; // parameter to be passed to pushButton (second call)
  const int NEW_FLOOR_REQUEST_3 = 6; // parameter to be passed to pushButton (third call)

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // try to call pushButton, thrice
  if (elevator.pushButton(NEW_FLOOR_REQUEST_1) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\"  case\n";
    return false;
  }
  if (elevator.pushButton(NEW_FLOOR_REQUEST_2) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\"  case\n";
    return false;
  }
  if (elevator.pushButton(NEW_FLOOR_REQUEST_3) == false) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\"  case\n";
    return false;
  }

  
  if (elevator.m_upRequests->m_floorNum != NEW_FLOOR_REQUEST_3) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\" case\n";
    return false;
  }
  if (elevator.m_upRequests->m_next->m_floorNum != NEW_FLOOR_REQUEST_1) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\" case\n";
    return false;
  }
  if (elevator.m_upRequests->m_next->m_next->m_floorNum != NEW_FLOOR_REQUEST_2) {
    cout << FAIL_STATEMENT << "Elevator's pushButton failed the edge \"max\" case\n";
    return false;
  }

  cout << PASS_STATEMENT << "Elevator's pushButton passed the edge \"max\" case\n";
  return true;
}

//Name: testElevatorPushButtonEdgeEqual
//Case: edge
//Expected result: pushButton() will not add the final floor request to down or up requests
bool Tester::testElevatorPushButtonEdgeEqual() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST = CURR_FLOOR; // parameter to be passed to pushButton

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // try to call pushButton - should fail - and both queues empty
  if (elevator.pushButton(NEW_FLOOR_REQUEST) == false and elevator.m_upRequests == nullptr
      and elevator.m_downRequests == nullptr) {
    cout << PASS_STATEMENT << "Elevator's pushButton passed the edge \"equal\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's pushButton faileded the edge \"equal\" case\n";
  return false;
}

//Name: testElevatorPushButtonEdgeError
//Case: error
//Expected result: pushButton() will not add the floor request - the floor doesn't exist!
bool Tester::testElevatorPushButtonError() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = FIRST_FLOOR - 1; // parameter to be passed to pushButton
                                                    //(first call)

  const int NEW_FLOOR_REQUEST_2 = LAST_FLOOR + 1; // parameter to be passed to pushButton
                                                   //(second call)

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // try to call pushButton twice- should fail - and  both queues empty
  if (elevator.pushButton(NEW_FLOOR_REQUEST_1) == false
      and elevator.pushButton(NEW_FLOOR_REQUEST_2) == false
      and elevator.m_upRequests == nullptr
      and elevator.m_downRequests == nullptr) {

    cout << PASS_STATEMENT << "Elevator's pushButton passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's pushButton faileded the error case\n";
  return false;
}

//Name: testElevatorProcessNextRequestNormalIdle
//Case: normal
//Expected result: the elevator will move to the closest floor and update that request LL
bool Tester::testElevatorProcessNextRequestNormalIdle() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 8; // should add to up requests
  const int NEW_FLOOR_REQUEST_2 = 3; // should add to down requests, and be traveled to first
  const int NEW_FLOOR_REQUEST_3 = 1; // should add to down requests, after NEW_FLOOR_REQUEST_2

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // populate the request LLs
  elevator.pushButton(NEW_FLOOR_REQUEST_1);
  elevator.pushButton(NEW_FLOOR_REQUEST_2);
  elevator.pushButton(NEW_FLOOR_REQUEST_3);

  // attempt to call process request
  if (elevator.processNextRequest() == false) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"idle\" case\n";
    return false;
  }

  // check if the elevator moved to the correct floor - whichever NEW_FLOOR_REQUEST is closest
   //to CURR_FLOOR
  if (elevator.m_currentFloor->m_floorNum != NEW_FLOOR_REQUEST_2) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"idle\" case\n";
    return false;
  }

  // check if the request LL hold the correct floors - up requests should be unchanged, down
   //requests should have just NEW_FLOOR_REQUEST_3 in it
  if (elevator.m_upRequests->m_floorNum != NEW_FLOOR_REQUEST_1
      or elevator.m_downRequests->m_floorNum != NEW_FLOOR_REQUEST_3) {

    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"idle\" case\n";
    return false;
  }
  
  cout << PASS_STATEMENT << "Eevator's processNextRequest passed the normal \"idle\" case\n";
  return true;
}

//Name: testElevatorProcessNextRequestNormalMoving
//Case: normal
//Expected result: the elevator will continue moving up, and update the up requests
bool Tester::testElevatorProcessNextRequestNormalMoving() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
  //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 8; // should add to up requests
  const int NEW_FLOOR_REQUEST_2 = 3; // should add to down requests, and be traveled to first
  const int NEW_FLOOR_REQUEST_3 = 1; // should add to down requests, after NEW_FLOOR_REQUEST_2

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // set the move state to up, to simulate a processNextRequest() call mid-program
  elevator.m_moveState = UP;
  
  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // populate the request LLs
  elevator.pushButton(NEW_FLOOR_REQUEST_1);
  elevator.pushButton(NEW_FLOOR_REQUEST_2);
  elevator.pushButton(NEW_FLOOR_REQUEST_3);

  // attempt to call process request
  if (elevator.processNextRequest() == false) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"moving\""
	 << " case\n";
    return false;
  }

  // check if the elevator moved to the correct floor - whichever NEW_FLOOR_REQUEST is closest
   //to and above CURR_FLOOR
  if (elevator.m_currentFloor->m_floorNum != NEW_FLOOR_REQUEST_1) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"moving\""
	 << " case\n";
    return false;
  }
  
  // check if the request LL hold the correct floors - up requests should be empty, down
   //requests should be unchanged
  if (elevator.m_upRequests != nullptr
      or elevator.m_downRequests->m_floorNum != NEW_FLOOR_REQUEST_2) {

    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the normal \"moving\""
	 << " case\n";
    return false;
  }

  cout << PASS_STATEMENT << "Eevator's processNextRequest passed the normal \"moving\""
       << " case\n";
  return true;
}

//Name: testElevatorProcessNextRequestEdge
//Case: edge
//Expected result: with requests equidistant from the current floor, and idle move state, the
                 //elevator picks a direction to pursue
bool Tester::testElevatorProcessNextRequestEdge() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
  //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = CURR_FLOOR + 1; // up request, one away from current floor
  const int NEW_FLOOR_REQUEST_2 = CURR_FLOOR - 1; // down request, one away from current floor
  const int NEW_FLOOR_REQUEST_3 = LAST_FLOOR;
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // populate the request LLs
  elevator.pushButton(NEW_FLOOR_REQUEST_1);
  elevator.pushButton(NEW_FLOOR_REQUEST_2);
  elevator.pushButton(NEW_FLOOR_REQUEST_3);
  
  // attempt to call process request
  if (elevator.processNextRequest() == false) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the edge case\n";
    return false;
  }

  // confirm that the move state was updated
  if (elevator.m_moveState == IDLE) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the edge case\n";
    return false;
  }
  
  // check if the elevator moved to a floor and updated the request LL
  if ((elevator.m_currentFloor->m_floorNum == NEW_FLOOR_REQUEST_1
       and elevator.m_upRequests->m_floorNum == NEW_FLOOR_REQUEST_3)
      or (elevator.m_currentFloor->m_floorNum == NEW_FLOOR_REQUEST_2
	  and (elevator.m_downRequests == nullptr))) {

    cout << PASS_STATEMENT << "Elevator's processNextRequest passed the edge case\n";
    return true;
  }

  // processNextRequest() was successfully called, and moveState was updated, but LL and/or
   //current floor are incorrect
  cout << FAIL_STATEMENT << "Eevator's processNextRequest failed the edge case\n";
  return true;
}

//Name: testElevatorProcessNextRequestErrorEmpty
//Case: error
//Expected result: elevator will stay at the current floor and remain idle
bool Tester::testElevatorProcessNextRequestErrorEmpty() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // attempt to call process request
  if (elevator.processNextRequest() == false
      and elevator.m_currentFloor->m_floorNum == CURR_FLOOR and elevator.m_moveState == IDLE) {
    
    cout << PASS_STATEMENT << "Elevator's processNextRequest passed the error \"empty\""
	 << " case\n";
    return true;
  }
  
  cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the error \"empty\""
       << " case\n";
  return false;
}

//Name: testElevatorProcessNextRequestErrorEmergency
//Case: error
//Expected result: elevator will stay at the current floor, be idle, and open the doors
bool Tester::testElevatorProcessNextRequestErrorEmergency() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 6;
  const int NEW_FLOOR_REQUEST_2 = 7;
  const int NEW_FLOOR_REQUEST_3 = 8;
  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);
  
  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // populate the request LLs
  elevator.pushButton(NEW_FLOOR_REQUEST_1);
  elevator.pushButton(NEW_FLOOR_REQUEST_2);
  elevator.pushButton(NEW_FLOOR_REQUEST_3);

  // go to a floor, don't have IDLE move state
  elevator.processNextRequest();
  
  // make it an emergency situation
  elevator.pushEmergency(true);
  
  // attempt to call process request
  if (elevator.processNextRequest() == true) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the error \"emergency\""
	 << " case\n";
    return false;
  }

  // confirm that all variables are set for an emergency state
  if (elevator.m_currentFloor->m_floorNum == NEW_FLOOR_REQUEST_1
      and elevator.m_moveState == IDLE
      and elevator.m_doorState == OPEN) {

    cout << PASS_STATEMENT << "Elevator's processNextRequest passed the error \"emergency\""
	 << " case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the error \"emergency\""
       << " case\n";
  return false;
  
}

//Name: testElevatorProcessNextRequestErrorLoad
//Case: error
//Expected result: elevator will stay at the current floor, maintain the moveState (it's just
                 //temperarily stopped, and open the doors
bool Tester::testElevatorProcessNextRequestErrorLoad() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int CURRENT_LOAD = LOADLIMIT + 1; // exceed the max load
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor
  const int NEW_FLOOR_REQUEST_1 = 6;
  const int NEW_FLOOR_REQUEST_2 = 7;
  const int NEW_FLOOR_REQUEST_3 = 8;

  
  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // populate the request LLs
  elevator.pushButton(NEW_FLOOR_REQUEST_1);
  elevator.pushButton(NEW_FLOOR_REQUEST_2);
  elevator.pushButton(NEW_FLOOR_REQUEST_3);

  // go to a floor, don't have IDLE move state
  elevator.processNextRequest();

  // exceed the load limit
  elevator.m_load = CURRENT_LOAD;

  // attempt to call process request
  if (elevator.processNextRequest() == true) {
    cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the error \"load\""
	 << " case\n";
    return false;
  }

  // confirm that all variables are set for an emergency state
  if (elevator.m_currentFloor->m_floorNum == NEW_FLOOR_REQUEST_1
            and elevator.m_moveState != IDLE
      and elevator.m_doorState == OPEN) {

    cout << PASS_STATEMENT << "Elevator's processNextRequest passed the error \"load\""
	 << " case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's processNextRequest failed the error \"load\""
       << " case\n";
  return false;
}

//Name: testElevatorEnterNormal
//Case: normal
//Expected result: the "entered" load will be added to the m_load
bool Tester::testElevatorEnterNormal() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int ADDITIONAL_LOAD = LOADLIMIT / 3; // weight to add, have it not exceed the LOADLIMIT
  const int FINAL_LOAD = BEGIN_LOAD + ADDITIONAL_LOAD; // expected ending value of m_load
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.enter(ADDITIONAL_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == FINAL_LOAD) {
    cout << PASS_STATEMENT << "Elevator's enter passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's enter failed the normal case\n";
  return false;
}

//Name: testElevatorEnterEdge
//Case: edge
//Expected result: m_load will remain the same with enter(0) called on the elevator
bool Tester::testElevatorEnterEdge() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int ADDITIONAL_LOAD = 0; // weight to add
  const int FINAL_LOAD = BEGIN_LOAD + ADDITIONAL_LOAD; // expected ending value of m_load
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
  //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.enter(ADDITIONAL_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == FINAL_LOAD) {
    cout << PASS_STATEMENT << "Elevator's enter passed the edge case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's enter failed the edge case\n";
  return false;
}

//Name: testElevatorEnterError
//Case: error
//Expected result: m_load will remain the same with enter doing nothing
bool Tester::testElevatorEnterError() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int ADDITIONAL_LOAD = -20; // weight to add
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
  //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.enter(ADDITIONAL_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == BEGIN_LOAD) {
    cout << PASS_STATEMENT << "Elevator's enter passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's enter failed the error case\n";
  return false;
}

//Name: testElevatorExitNormal
//Case: normal
//Expected result: m_load will decrease by REMOVED_LOAD
bool Tester::testElevatorExitNormal() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int REMOVED_LOAD = LOADLIMIT / 3; // weight to subtract, is less than BEGIN_LOAD
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
  //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.exit(REMOVED_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == BEGIN_LOAD - REMOVED_LOAD) {
    cout << PASS_STATEMENT << "Elevator's exit passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's exit failed the normal case\n";
  return false;
}

//Name: testElevatorExitEdge
//Case: edge
//Expected result: m_load will remain the same with exit subtracting 0 from it
bool Tester::testElevatorExitEdge() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int REMOVED_LOAD = 0; // weight to subtract
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.exit(REMOVED_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == BEGIN_LOAD) {
    cout << PASS_STATEMENT << "Elevator's exit passed the edge case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's exit failed the edge case\n";
  return false;
}

//Name: testElevatorExitError
//Case: error
//Expected result: m_load will be 0
bool Tester::testElevatorExitError() {
  const int ID = 1; // ID of the elevator
  const int FIRST_FLOOR = 0; // bottom floor
  const int LAST_FLOOR = 10; // top floor
  const int CURR_FLOOR = 5; // the current floor
  const int BEGIN_LOAD = LOADLIMIT / 2; // start with a valid load
  const int REMOVED_LOAD = LOADLIMIT + 1; // weight to remove
  Floor* curr = nullptr; // floor pointer for iterator thru the LL and initializing
                          //m_currentFloor

  Elevator elevator(ID);

  elevator.setUp(FIRST_FLOOR, LAST_FLOOR);

  // manually set the current floor
  curr = elevator.m_bottom;
  for (int i = FIRST_FLOOR; i < CURR_FLOOR; i++) {
    curr = curr->m_next;
  }
  elevator.m_currentFloor = curr;

  // set the load limit
  elevator.m_load = BEGIN_LOAD;

  // call enter() to add the new load
  elevator.exit(REMOVED_LOAD);

  // confirm that the new load is correct
  if (elevator.m_load == 0) {
    cout << PASS_STATEMENT << "Elevator's exit passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "Elevator's exit failed the error case\n";
  return false;
}

//Name: testCentComConstructorNormal
//Case: normal
//Expected result: a new CentCom object is created with several elevators
bool Tester::testCentComConstructorNormal() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // confirm that the values were initialzed as expected
  if (centcom.m_id == ID and centcom.m_numElevators == NUM_ELEVATORS) {
    // check the created elevator objects
    for (int i = 0; i < NUM_ELEVATORS; i++) {
      if (centcom.m_elevatorsList[i]->m_id != i) {
	cout << FAIL_STATEMENT << "CentCom's constructor failed the normal case\n";
	return false;
      }
    }
    cout << PASS_STATEMENT << "CentCom's constructor passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's constructor failed the normal case\n";
  return false;
}

//Name: testCentComConstructorEdge
//Case: edge
//Expected result: a new CentCom object (ID of 0) is created with 0 elevators
bool Tester::testCentComConstructorEdge() {
  const int ID = 0; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // confirm that the values were initialzed as expected
  if (centcom.m_id == ID and centcom.m_numElevators == NUM_ELEVATORS) {
    // check the created elevator objects
    for (int i = 0; i < NUM_ELEVATORS; i++) {
      if (centcom.m_elevatorsList[i]->m_id != i) {
	cout << FAIL_STATEMENT << "CentCom's constructor failed the edge case\n";
	return false;
      }
    }
    if (centcom.m_elevatorsList == nullptr) {
      cout << PASS_STATEMENT << "CentCom's constructor passed the edge case\n";
      return true;
    }
  }

  cout << FAIL_STATEMENT << "CentCom's constructor failed the edge case\n";
  return false;
}

//Name: testCentComConstructorError
//Case: error
//Expected result: a new CentCom object (ID of 0) is created with 0 elevators
bool Tester::testCentComConstructorError() {
  const int ID = -1; // invalid ID of the CentCom object
  const int NUM_ELEVATORS = -1; // invalid number of elevators
  const int DEFAULT_ID = 0; // expected ID for the CentCom object
  const int DEFAULT_NUM_ELEVATORS = 0; // expected number of elevators
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // confirm that the values were initialzed as expected
  if (centcom.m_id == DEFAULT_ID and centcom.m_numElevators == DEFAULT_NUM_ELEVATORS
      and centcom.m_elevatorsList == nullptr) {
    
    cout << PASS_STATEMENT << "CentCom's constructor passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's constructor failed the error case\n";
  return false;
}

//Name: testCentComAddElevatorNormalNew
//Case: normal
//Expected result: a centcom object will have four elevators in it with proper values
                 //(it will add a new elevator)
bool Tester::testCentComAddElevatorNormalNew() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int BOTTOM_FLOOR = 1; // lowest floor of new elevator
  const int TOP_FLOOR = 6; // highest floor of new elevator
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call addElevator
  if (centcom.addElevator(NUM_ELEVATORS, BOTTOM_FLOOR, TOP_FLOOR) == false) {
    cout << FAIL_STATEMENT << "CentCom's addElevator failed the normal \"new\" case\n";
    return false;
  }
  
  // check the created elevator object
  if (centcom.m_elevatorsList[NUM_ELEVATORS]->m_id == NUM_ELEVATORS
      and centcom.m_numElevators == NUM_ELEVATORS + 1
      and centcom.m_elevatorsList[NUM_ELEVATORS]->m_bottom->m_floorNum == BOTTOM_FLOOR
      and centcom.m_elevatorsList[NUM_ELEVATORS]->m_top->m_floorNum == TOP_FLOOR) {
    
    cout << PASS_STATEMENT << "CentCom's addElevator passed the normal \"new\" case\n";
    return true;
  }
  
  cout << FAIL_STATEMENT << "CentCom's addElevator failed the normal \"new\" case\n";
  return false;
}

//Name: testCentComAddElevatorNormalReplace
//Case: normal
//Expected result: a centcom object will have three elevators in it with updated values
//(it will replace an existing elevator)
bool Tester::testCentComAddElevatorNormalReplace() {
  const int ID = 1; // ID of the CentCom object
  const int ELEVATOR_ID = 0; // ID of elevator that is being replaced
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int BOTTOM_FLOOR = 1; // lowest floor of new elevator
  const int TOP_FLOOR = 6; // highest floor of new elevator

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call addElevator
  if (centcom.addElevator(ELEVATOR_ID, BOTTOM_FLOOR, TOP_FLOOR) == false) {
    cout << FAIL_STATEMENT << "CentCom's addElevator failed the normal \"replace\" case\n";
    return false;
  }

  // check the created elevator object
  if (centcom.m_elevatorsList[ELEVATOR_ID]->m_id == ELEVATOR_ID
      and centcom.m_numElevators == NUM_ELEVATORS
      and centcom.m_elevatorsList[ELEVATOR_ID]->m_bottom->m_floorNum == BOTTOM_FLOOR
      and centcom.m_elevatorsList[ELEVATOR_ID]->m_top->m_floorNum == TOP_FLOOR) {

    cout << PASS_STATEMENT << "CentCom's addElevator passed the normal \"replace\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator failed the normal \"replace\" case\n";
  return false;
}

//Name: testCentComAddElevatorEdge
//Case: edge
//Expected result: a centcom object will have one elevator in it with proper values
bool Tester::testCentComAddElevatorEdge() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int BOTTOM_FLOOR = 1; // lowest floor of new elevator
  const int TOP_FLOOR = 10; // highest floor of new elevator

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call addElevator
  if (centcom.addElevator(NUM_ELEVATORS, BOTTOM_FLOOR, TOP_FLOOR) == false) {
    cout << FAIL_STATEMENT << "CentCom's addElevator failed the edge case\n";
    return false;
  }

  // check the created elevator object
  if (centcom.m_elevatorsList[NUM_ELEVATORS]->m_id == NUM_ELEVATORS
      and centcom.m_numElevators == NUM_ELEVATORS + 1
      and centcom.m_elevatorsList[NUM_ELEVATORS]->m_bottom->m_floorNum == BOTTOM_FLOOR
      and centcom.m_elevatorsList[NUM_ELEVATORS]->m_top->m_floorNum == TOP_FLOOR) {

    cout << PASS_STATEMENT << "CentCom's addElevator passed the edge case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator failed the edge case\n";
  return false;
}

//Name: testCentComAddElevatorError
//Case: error
//Expected result: a centcom object will have no elevators in it and addElevator() will return
                 //false
bool Tester::testCentComAddElevatorError() {
  const int ID = 1; // ID of the CentCom object
  const int ELEVATOR_ID = -1; // ID of the elevator object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int BOTTOM_FLOOR = 10; // lowest floor of new elevator
  const int TOP_FLOOR = 1; // highest floor of new elevator

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call addElevator (should fail) and confirm centcom variables have expected values
  if (centcom.addElevator(ELEVATOR_ID, BOTTOM_FLOOR, TOP_FLOOR) == false
      and centcom.m_numElevators == NUM_ELEVATORS and centcom.m_elevatorsList == nullptr) {
    cout << PASS_STATEMENT << "CentCom's addElevator passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator failed the error case\n";
  return false;
}

//Name: testCentComGetElevatorNormal
//Case: normal
//Expected result: elevator of ID (variable ID) will be returned via pointer
bool Tester::testCentComGetElevatorNormal() {
  const int ID = 1; // ID of the CentCom object
  const int ELEVATOR_ID = 1; // ID of elevator that is being get
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call getElevator
  if (centcom.getElevator(ELEVATOR_ID) == centcom.m_elevatorsList[ELEVATOR_ID]) {
    cout << PASS_STATEMENT << "CentCom's getElevator passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator passed the normal case\n";
  return false;
}

//Name: testCentComGetElevatorEdgeMin
//Case: edge
//Expected result: elevator of ID 0 will be returned via pointer
bool Tester::testCentComGetElevatorEdgeMin() {
  const int ID = 1; // ID of the CentCom object
  const int ELEVATOR_ID = 0; // ID of elevator that is being get
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call getElevator
  if (centcom.getElevator(ELEVATOR_ID) == centcom.m_elevatorsList[ELEVATOR_ID]) {
    cout << PASS_STATEMENT << "CentCom's getElevator passed the edge \"min\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator passed the edge \"min\" case\n";
  return false;
}

//Name: testCentComGetElevatorEdgeMax
//Case: edge
//Expected result: the last elevator will be returned via pointer
bool Tester::testCentComGetElevatorEdgeMax() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = NUM_ELEVATORS - 1; // ID of elevator that is being get

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call getElevator
  if (centcom.getElevator(ELEVATOR_ID) == centcom.m_elevatorsList[ELEVATOR_ID]) {
    cout << PASS_STATEMENT << "CentCom's getElevator passed the edge \"max\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator passed the edge \"max\" case\n";
  return false;
}

//Name: testCentComGetElevatorError
//Case: error
//Expected result: nullptr will be retured
bool Tester::testCentComGetElevatorError() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = NUM_ELEVATORS + 1; // ID of target elevator, doesn't exist

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // try to call getElevator
  if (centcom.getElevator(ELEVATOR_ID) == nullptr) {
    cout << PASS_STATEMENT << "CentCom's getElevator passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's addElevator passed the error case\n";
  return false;
}

//Name: testCentComSetSecureNormal
//Case: normal
//Expected result: chosen floor of chosen elevator will be set to secure
bool Tester::testCentComSetSecureNormal() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = 1; // ID of target elevator
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);
  
  // try to call setSecure
  if (centcom.setSecure(ELEVATOR_ID, BOTTOM_FLOOR + 1, true) == false) {
    cout << FAIL_STATEMENT << "CentCom's setSecure failed the normal case\n";
    return false;
  }

  // check that the floor is secure
  if (centcom.m_elevatorsList[ELEVATOR_ID]->m_bottom->m_next->m_secured) {
    cout << PASS_STATEMENT << "Centcom's setSecure passed the normal case\n";
    return true;
  }
  
  cout << FAIL_STATEMENT << "CentCom's setSecure failed the normal case\n";
  return false;
}

//Name: testCentComSetSecureEdgeMin
//Case: edge
//Expected result: chosen floor of chosen elevator will be set to secure
bool Tester::testCentComSetSecureEdgeMin() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = 1; // ID of target elevator
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // try to call setSecure
  if (centcom.setSecure(ELEVATOR_ID, BOTTOM_FLOOR, true) == false) {
    cout << FAIL_STATEMENT << "CentCom's setSecure failed the edge \"min\" case\n";
    return false;
  }

  // check that the floor is secure
  if (centcom.m_elevatorsList[ELEVATOR_ID]->m_bottom->m_secured) {
    cout << PASS_STATEMENT << "Centcom's setSecure passed the edge \"min\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's setSecure failed the edge \"min\" case\n";
  return false;
}

//Name: testCentComSetSecureEdgeMax
//Case: edge
//Expected result: chosen floor of chosen elevator will be set to secure
bool Tester::testCentComSetSecureEdgeMax() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = 1; // ID of target elevator
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // try to call setSecure
  if (centcom.setSecure(ELEVATOR_ID, TOP_FLOOR, true) == false) {
    cout << FAIL_STATEMENT << "CentCom's setSecure failed the edge \"max\" case\n";
    return false;
  }

  // check that the floor is secure
  if (centcom.m_elevatorsList[ELEVATOR_ID]->m_top->m_secured) {
    cout << PASS_STATEMENT << "Centcom's setSecure passed the edge \"max\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's setSecure failed the edge \"max\" case\n";
  return false;
}

//Name: testCentComSetSecureError
//Case: error
//Expected result: function returns false because passed floor doesn't exist
bool Tester::testCentComSetSecureError() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 0; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = 1; // ID of target elevator
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // try to call setSecure
  if (centcom.setSecure(ELEVATOR_ID, TOP_FLOOR + 1, true) == false) {
    cout << PASS_STATEMENT << "CentCom's setSecure passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's setSecure failed the error case\n";
  return false;
}

//Name: testCentComClearEmergencyNormal
//Case: normal
//Expected result: the elevator's emergency state is set to false
bool Tester::testCentComClearEmergencyNormal() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = 1; // ID of target elevator
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // make the target elevator's emergency state active
  centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency = true;
  
  // try to call clearEmergency
  if (centcom.clearEmergency(ELEVATOR_ID) == true
      and centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency == false) {

    cout << PASS_STATEMENT << "CentCom's clearEmergency passed the normal case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's clearEmergency failed the normal case\n";
  return false;
}

//Name: testCentComClearEmergencyEdgeMin
//Case: edge
//Expected result: the elevator's emergency state is set to false
bool Tester::testCentComClearEmergencyEdgeMin() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will have
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators
  const int ELEVATOR_ID = 0; // ID of target elevator
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // make the target elevator's emergency state active
  centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency = true;

  // try to call clearEmergency
  if (centcom.clearEmergency(ELEVATOR_ID) == true
      and centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency == false) {

    cout << PASS_STATEMENT << "CentCom's clearEmergency passed the edge \"min\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's clearEmergency failed the edge \"min\" case\n";
  return false;
}

//Name: testCentComClearEmergencyEdgeMax
//Case: edge
//Expected result: the elevator's emergency state is set to false
bool Tester::testCentComClearEmergencyEdgeMax() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will have
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators
  const int ELEVATOR_ID = NUM_ELEVATORS - 1; // ID of target elevator 
  
  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // make the target elevator's emergency state active
  centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency = true;

  // try to call clearEmergency
  if (centcom.clearEmergency(ELEVATOR_ID) == true
      and centcom.m_elevatorsList[ELEVATOR_ID]->m_emergency == false) {

    cout << PASS_STATEMENT << "CentCom's clearEmergency passed the edge \"max\" case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's clearEmergency failed the edge \"max\" case\n";
  return false;
}

//Name: testCentComClearEmergencyError
//Case: error
//Expected result: the elevator doesn't exist, so the function returns false
bool Tester::testCentComClearEmergencyError() {
  const int ID = 1; // ID of the CentCom object
  const int NUM_ELEVATORS = 3; // how many elevators the CentCom object will be created with
  const int ELEVATOR_ID = -1; // ID of target elevator, doesn't exist
  const int BOTTOM_FLOOR = 0; // lowest floor for all elevators
  const int TOP_FLOOR = 10; // highest floor for all elevators

  // create the CentCom object
  CentCom centcom(NUM_ELEVATORS, ID);

  // populate the centcom with elevators
  centcom.addElevator(0, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(1, BOTTOM_FLOOR, TOP_FLOOR);
  centcom.addElevator(2, BOTTOM_FLOOR, TOP_FLOOR);

  // try to call clearEmergency
  if (centcom.clearEmergency(ELEVATOR_ID) == false) {
    cout << PASS_STATEMENT << "CentCom's clearEmergency passed the error case\n";
    return true;
  }

  cout << FAIL_STATEMENT << "CentCom's clearEmergency failed the error case\n";
  return false;
}

int main() {
  Tester tester;
  
  tester.testElevatorConstructorNormal();
  tester.testElevatorConstructorEdge();
  tester.testElevatorConstructorError();

  tester.testElevatorSetUpNormal();
  tester.testElevatorSetUpEdge();
  tester.testElevatorSetUpError();

  tester.testElevatorInsertFloorNormal();
  tester.testElevatorInsertFloorEdge();
  tester.testElevatorInsertFloorError();

  tester.testElevatorCheckSecureNormal();
  tester.testElevatorCheckSecureEdge();
  tester.testElevatorCheckSecureError();

  tester.testElevatorPushEmergencyNormal();
  tester.testElevatorPushEmergencyError();
  
  tester.testElevatorPushButtonNormalDown();
  tester.testElevatorPushButtonNormalUp();
  tester.testElevatorPushButtonEdgeMin();
  tester.testElevatorPushButtonEdgeMax();
  tester.testElevatorPushButtonEdgeEqual();
  tester.testElevatorPushButtonError();

  tester.testElevatorProcessNextRequestNormalIdle();
  tester.testElevatorProcessNextRequestNormalMoving();
  tester.testElevatorProcessNextRequestEdge();
  tester.testElevatorProcessNextRequestErrorEmpty();
  tester.testElevatorProcessNextRequestErrorEmergency();
  tester.testElevatorProcessNextRequestErrorLoad();

  tester.testElevatorEnterNormal();
  tester.testElevatorEnterEdge();
  tester.testElevatorEnterError();

  tester.testElevatorExitNormal();
  tester.testElevatorExitEdge();
  tester.testElevatorExitError();

  tester.testCentComConstructorNormal();
  tester.testCentComConstructorEdge();
  tester.testCentComConstructorError();

  tester.testCentComAddElevatorNormalNew();
  tester.testCentComAddElevatorNormalReplace();
  tester.testCentComAddElevatorEdge();
  tester.testCentComAddElevatorError();

  tester.testCentComGetElevatorNormal();
  tester.testCentComGetElevatorEdgeMin();
  tester.testCentComGetElevatorEdgeMax();
  tester.testCentComGetElevatorError();

  tester.testCentComSetSecureNormal();
  tester.testCentComSetSecureEdgeMin();
  tester.testCentComSetSecureEdgeMax();
  tester.testCentComSetSecureError();

  tester.testCentComClearEmergencyNormal();
  tester.testCentComClearEmergencyEdgeMin();
  tester.testCentComClearEmergencyEdgeMax();
  tester.testCentComClearEmergencyError();
    
  return 0;
}
