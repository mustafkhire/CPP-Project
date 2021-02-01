# Project Overview

The purpose of this term project is to put your C++ Object Oriented skills to practice by developing a simulated Assembly Line.

The project simulates an assembly line that fills customer orders from inventory. Each customer order consists of a list of items that need to be filled. The line consists of a set of stations. Each station holds an inventory of items for filling customer orders and a queue of orders to be filled. Each station fills the next order in the queue if that order requests its item and that item is still in stock. A line manager moves the customer orders from station to station until all orders have been processed. Any station that has used all of the items in stock cannot fill any more orders. Orders become incomplete due to a lack of inventory at one or more stations. At the end of all processing, the line manager lists the completed orders and the orders that are incomplete.

The project is broken down into 3 milestones to help guide you through the process of implementing, debugging and execution of a more complex application than a regular lab/workshop.



## Project Deadlines

The deadlines for the project's milestones are on Saturday at midnight (see the schedule below).

| Milestone |   Date |
|-----------|--------|
| #1        | Nov 14 |
| #2        | Nov 21 |
| #3        | Nov 28 |


All files that you submit (`*.h` and `*.cpp`) should contain the following comment at the top (with your information filled):
```cpp
// Name:
// Seneca Student ID:
// Seneca email:
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
```

**Milestone #3** can have an extension until December 08 2020, with a penalty of 10% for each day that the submission is late. After December 08 2020, the submission process is considered closed.
- submissions received on Nov 29 2020 can receive **max 90%**;
- submissions received on Nov 30 2020 can receive **max 80%**;
- submissions received on Dec 01 2020 can receive **max 70%**;
- submissions received on Dec 02 2020 can receive **max 60%**;
- submissions received on Dec 03 2020 can receive **max 50%**;
- submissions received on Dec 04 2020 can receive **max 40%**;
- submissions received on Dec 05 2020 can receive **max 30%**;
- submissions received on Dec 06 2020 can receive **max 20%**;
- submissions received on Dec 07 2020 can receive **max 10%**;
- submissions received on Dec 08 2020 can receive **max  0%**;


**The project is mandatory!** Students that don't submit a complete working project, cannot pass this course. A project is considered complete if all three milestones have been submitted by the deadline and the implementation follows the requirements.








# Milestone 1

## `Utilities` and `Station` classes

This milestone will implement and test the `Utilities` and `Station` classes.

- `Utilities` class is an object used to support the parsing of input files to setup and configure the assembly line simulation.
- `Station` class encapsulates the information about a given station on the assembly line that fills customer orders.

The specifications of the classes are defined below.


### `Utilities` Class

Parsing string data from input files is performed the same way for all objects within the system.  The `Utilities` type provides the basic functionality required for all objects in the assembly line system.

Each `Utilities` object holds the following information:
-  `m_widthField` -- specifying the length of the token extracted; used for display purpose later; default value is `1`.
-  `m_delimiter` -- separates the tokens from a given `std::string`. All `Utilities` objects **share the same delimiter**.

The member functions of the `Utilities` class include:
-  `void setFieldWidth(size_t newWidth)` -- sets the field width of the current object to the value of the parameter
-  `size_t getFieldWidth() const` -- returns the field width of the current object
-  `std::string extractToken(const std::string& str, size_t& next_pos, bool& more)` -- extracts tokens from the first parameter
    - This function uses the delimiter to extract the next token from `str` starting at `next_pos`.
    - If successful, it returns the extracted token found and sets `more` to `true`; `false` otherwise.
    - This function reports an exception if there are two delimiters with no token between them.
    - This function updates the current object's `m_widthField` data member if its current value is less than the size of the token extracted.
    - **Note:**  `str` represents a single line read from an input file
-  `static void setDelimiter(char newDelimiter)` -- sets the delimiter for this class to the character received
-  `static char getDelimiter()` -- returns the delimiter character.



### `Station` Class

An `Station` object manages a single station on the assembly line. Each station handles a single item in the customer order.

Each `Station` holds the following information:
- the id of a station (integer)
- the name of the item handled that the station (array of characters)
- the description of the station (array of characters)
- the next serial number to be assigned to an item at this station (integer)
- the number of current items left in stock (integer)


***Static Data***

- `m_widthField` -- the maximum characters required to print to screen the *item name*, *serial number* and *quantity* for any object of type `Station`.  Initial value is 0.
- `id_generator` -- a variable used to generate IDs for new instances of type `Station`. Every time a new instance is created, the current value of the `id_generator` is stored in the instance, and `id_generator` is incremented.  Initial value is 0.


***Public Functions***

-  custom constructor
    - upon instantiation, an `Station` object receives a reference to an unmodifiable `std::string`.  This string contains a single record (one line) that has been retrieved from the input file specified by the user.
    - the constructor uses an `Utilities` object (created local in the function) to extract each token from the record and populates the `Station` object accordingly.
    - **Note:**  You can assume that a record from the file contains 4 fields separated by a delimiter, in the following order:
        - name of the item
        - starting serial number
        - quantity in stock
        - description
    - the delimiter of the tokens is a single character, specified by the client and stored into the `Utilities` object.
    - once the constructor has extracted *name*, *starting serial number*, and *quantity* from the record, it updates `Station::m_widthField` to the maximum value of `Station::m_widthField` and `Utilities::m_widthField`.
    - **Note:**  the `display(...)` member function uses this field width to align the output across all of the records retrieved from the file.

-  `const std::string& getItemName() const` - returns the name of the current `Station` object
-  `unsigned int getNextSerialNumber()` – returns the next serial number to be used on the assembly line and increments `m_serialNumber`
-  `unsigned int getQuantity() const` – returns the remaining quantity of the current `Station` object
-  `void updateQuantity()` – subtracts 1 from the available quantity; should not go below 0.
-  `void display(std::ostream& os, bool full) const` -- inserts the content of the current object into first parameter.
    - if the second parameter is `false`, this function inserts only the ID, name and serial number in the format: `[ID] Item: NAME [SERIAL]`
    - if the second parameter if `true`, this function uses the following format: `[ID] Item NAME [SERIAL] Quantity: QTY Description: DESCRIPTION`
    - `ID` field will use 3 characters, the `NAME` and `QTY` fields will use `m_widthField` characters, serial number field will use 6 characters; the `DESCRIPTION` has no formatting options
    - this function will terminate the printed message with an endline


## Tester Module

The tester module and input files have been added to the repository. Do not modify any of them.

## Sample Output

Look in the file `ms1_output.txt` for the command line necessary to start the application and the expected output.

#### Submission

Before the due date, upload to your matrix account the following files:
-  `Utilities.h`
-  `Utilities.cpp`
-  `Station.h`
-  `Station.cpp`

From a command prompt, execute the following command:

```bash
~profname.proflastname/submit 305_ms1
```

and follow the instructions.

**A successful submission does not guarantee full credit!**
