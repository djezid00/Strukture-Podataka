# Data Structures and Algorithms in C - Laboratory Exercises

This repository contains a set of C programming exercises designed to reinforce understanding of fundamental data structures and algorithms. These exercises are suitable for students or anyone looking to improve their C programming skills and data structures knowledge.

## Exercises Overview

1.  **Student Records:**
    *   Reads student data (name, surname, points) from a file.
    *   Dynamically allocates memory for an array of student structures.
    *   Calculates and displays absolute and relative scores.

2.  **Linked List of People:**
    *   Defines a structure for a person (name, surname, year of birth).
    *   Implements functions to:
        *   Add a new element to the beginning of the list.
        *   Print the list.
        *   Add a new element to the end of the list.
        *   Find an element by surname.
        *   Delete a specific element from the list.
    *   *Note: No global variables allowed.*

3.  **Advanced Linked List Operations:**
    *   Extends the previous exercise with functions to:
        *   Add a new element after a given element.
        *   Add a new element before a given element.
        *   Sort the list by surname.
        *   Write the list to a file.
        *   Read the list from a file.

4.  **Polynomial Arithmetic:**
    *   Reads polynomial coefficients and exponents from a file.
    *   Implements polynomial addition and multiplication.
    *   *Note: Exponents in the file are not necessarily sorted.*

5.  **Postfix Expression Evaluation:**
    *   Reads a postfix expression from a file.
    *   Evaluates the expression using a stack implemented with a linked list.

6.  **Invoice Management:**
    *   Reads a list of invoice filenames from `racuni.txt`.
    *   Each invoice file contains a date (YYYY-MM-DD) and a list of articles (name, quantity, price).
    *   Creates a sorted linked list of invoices (by date).
    *   Each invoice node contains a sorted linked list of articles (by name).
    *   Allows querying the total amount and quantity of a specific article within a given time period.

7.  **Directory Structure Simulation:**
    *   Simulates a directory structure using linked lists (trees).
    *   Implements a menu-driven interface for DOS-like commands:
        *   `md` (create directory)
        *   `cd dir` (change directory)
        *   `cd..` (go to parent directory)
        *   `dir` (list directory contents)
        *   `exit`

8.  **Binary Search Tree Operations:**
    *   Implements a binary search tree.
    *   Provides functions for:
        *   Inserting a new element.
        *   Printing elements (inorder, preorder, postorder, level order).
        *   Deleting an element.
        *   Finding an element.

9.  **Binary Tree Construction and Manipulation:**
    *   Constructs a binary tree from a predefined array of numbers: `2, 5, 7, 8, 11, 1, 4, 2, 3, 7`.
        *   `insert()`: Creates the tree structure based on the given sequence.
        *   `replace()`: Replaces each node's value with the sum of its left and right subtrees.
    *   Modifies the program to generate random numbers (range: 10-90) instead of using the predefined array.
    *   Writes the inorder traversal of the tree to a file after applying both `insert()` and `replace()`.

10. **Country and City Data Management:**
    *   Reads country names from `drzave.txt`. Each country has an associated file containing city data (city name, population).
        *   Creates a sorted linked list of countries (by name). Each country node contains a tree of cities sorted by population (then by name).
        *   Creates a tree of countries sorted by name. Each country node contains a linked list of cities sorted by population (then by name).
    *   Allows the user to search for cities in a specific country with a population greater than a given value.

11. **Hash Table of Countries:**
    *   Modifies exercise 10 to use a hash table for storing countries.
    *   The hash table has 11 slots.
    *   The hash function calculates the hash key by summing the ASCII values of the first five letters of the country name and taking the modulo with the table size.
    *   Collisions are handled using linked lists sorted by country name.
    *   Each country node contains a tree of cities sorted by population (then by name).


These exercises are written in C.


