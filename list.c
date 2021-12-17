#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*	
Allocate a linked list node with a given key
Allocate a node using malloc(),
initialize the pointers to NULL,
set the key value to the key provided by the argument
 */
struct list_node *allocate_node_with_key(int keyAlloc) 
{									// keyAlloc = slloated node's key value
	struct list_node *nodeAlloc = NULL; 
	nodeAlloc = (struct list_node*)malloc(sizeof(struct list_node)); 
	(*nodeAlloc).key = keyAlloc; 	// allocated node has a key value of keyAlloc
	(*nodeAlloc).value = NULL;
	(*nodeAlloc).next = NULL;
	(*nodeAlloc).prev = NULL; 		// allocated an independent and empty node (not connected)

	return nodeAlloc;				// return the newly allocated node
}

/*	
Initialize the key values of the head/tail list nodes (I used -1 key values)
Also, link the head and tail to point to each other
 */
void initialize_list_head_tail(struct list_node *head, struct list_node *tail)
{
	(*head).next = tail; 	// as it is linked to tail for both sides 
	(*head).prev = tail;
	(*head).value = NULL;
	(*head).key = -1; 		// -1 is an invalid key
	(*tail).next = head; 	// as it is lined to head for both sides
	(*tail).prev = head;
	(*tail).value = NULL;
	(*tail).key = -1; 		// -1 is an invalid key
	return;
}

/*	
Insert the *new_node* after the *node*
 */
void insert_node_after (struct list_node *node, struct list_node *new_node)
{
	// a new node is inserted after the node.
	(*new_node).next = (*node).next; 	// connect new node's next to original node's next.
	(*new_node).prev = node; 			// connect new node's prev to original node.
	(*((*node).next)).prev = new_node; 	// connect original node's next node's prev to the new node.
	(*node).next = new_node; 			// connect original node's next to the new node. 
	return;
}

/*	
Remove the *node* from the list
 */
void del_node (struct list_node *node)
{
	(*((*node).prev)).next = (*node).next;	// connect previous node's next to the node.next (note N-1.next to N+1)
	(*((*node).next)).prev = (*node).prev; 	// connect next node's prev to the node.prev (node N+1.prev to N-1)
	free(node); 							// remove the disconnected node (adios!)
	return;
}

/*	
Search from the head to the tail (excluding both head and tail,
as they do not hold valid keys), for the node with a given *search_key*
and return the node.
You may assume that the list will only hold nodes with unique key values
(No duplicate keys in the list)
 */
struct list_node *search_list (struct list_node *head, int search_key)
{
	struct list_node *nodeSearch = (*head).next; 	// initial pointer to the next node of the head
	while (nodeSearch != (*head).prev) 				// while ((*nodeSearch).next != head)
	{ 
		if ((*nodeSearch).key == search_key) {		// nodeSearch's key == key to be searched?
			return nodeSearch; 						// return the node's pointer 
		}
		nodeSearch = (*nodeSearch).next; 			// continue to the next node
	}
	return NULL;									// NULL when no such key is found
}

/*	
Count the number of nodes in the list (excluding head and tail), 
and return the counted value
 */
int count_list_length (struct list_node *head)
{
	int cnt = 0;
	struct list_node *nodeCnt = head; 				// initialize the counting node from the head.
	while ((*nodeCnt).next != (*head).prev) {
		cnt++; 										// add 1 to the counter.
		nodeCnt = (*nodeCnt).next; 					// continue to the next node.
	}
	return cnt;
}

/*	
Check if the list is empty (only head and tail exist in the list)
Return 1 if empty. Return 0 if list is not empty.
 */
int is_list_empty (struct list_node *head)
{
	int georgeBoole = 0;
	if ((*head).next == (*head).prev) {
		georgeBoole = 1;
	}
	return georgeBoole;
}

/*	
Loop through the list and print the key values
This function will not be tested, but it will aid you in debugging your list.
You may add calls to the *iterate_print_keys* function in the test.c
at points where you need to debug your list.
But make sure to test your final version with the original test.c code.
 */
void iterate_print_keys (struct list_node *head)
{
	// idk how to use this... sorry.
}

/*	
Insert a *new_node* at the sorted position so that the keys of the nodes of the
list (including the key of the *new_node*) is always sorted (increasing order)

Also, is_list_sorted() is a function that checks whether the keys of the nodes are sorted or not. 
 */

int is_list_sorted(struct list_node *head)
{
	struct list_node *temp = (*head).next; // start from the 2nd node, as head's key is an invalid value. 
	while ((*temp).key != -1) // while the key is valid,
	{ 
		if ( (*temp).key > (*(*temp).next).key ) // if the key of the next node is smaller, 
		{  
			return 0; // escape loop, with return value 'false'.
		}
		temp = (*temp).next; // continue to check the next node. 
	}
	return 1;
}

int insert_sorted_by_key (struct list_node *head, struct list_node *new_node)
{
	if(is_list_empty(head)) // if the list is empty then just add the new node
	{
 		insert_node_after(head,new_node);
 		return is_list_sorted(head); // return 1 if the list after insert is in order. 
	}

	struct list_node *nodeList = (*head).next; // start from the 2nd node. 
	int a = 0;

	while (a == 0) {
		if ( (*new_node).key < (*nodeList).key ) // key of new node to be inserted is less then nodeList's key?
		{
			a = 1; // escape the loop and add the new node!
		}
		else {
			if ((*head).prev == nodeList) // nodeList reach the tail, thus new node's key is the largest of all.
			{
				insert_node_after( (*(*head).prev).prev , new_node); // insert a new node before the tail.
				return is_list_sorted(head); // return 1 if the list after insert is in order. 
			}
			nodeList = (*nodeList).next; // continue to find next node's key in the list that is larger than new node's key. 
		}
	}
	insert_node_after((*nodeList).prev, new_node); // insert a new node before the nodeList (which has a larger key)
	return is_list_sorted(head); // return 1 if the list after insert is in order. 
}
