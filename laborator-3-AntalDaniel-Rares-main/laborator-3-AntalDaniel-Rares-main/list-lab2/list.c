#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * TASK 1.
 *
 * Completati structura din fisierul header.
 */

int main()
{	
	printf("Lab 2 - Liste inlantuite.\n");
	
	/**************************************************************************
	 * Test Task 2.
	 * Creati un nod cu o anumita valoare.
	 * Afisati valoarea la stdout.
	 */
	node_t *node = NULL;
	node = (node_t *)malloc(sizeof(node_t));
	node->val = 100;
	node->next = NULL;

	print_list(node);
	

	/* ... your code comes here ... */




	/**************************************************************************
	 * Test Task 3.
	 *
	 * Creati o variabila de tip 'node_t' cu numele 'head'.
	 * Ea va reprezenta cap-ul listei cu care veti lucra mai jos.
	 *
	 * Adaugati 5-6 noduri cu valori diferite la final listei.
	 * Aveti un exemplu.
	 */
	node_t *head = NULL;

	head = (node_t *) malloc(sizeof(node_t));
	head->val = 1;
	head->next = NULL;
	
	int i = 0;
	node_t *current = NULL;
	
	head->next = (node_t*) malloc(sizeof(node_t));
	current = head->next;

	while(i<5)
	{
		current->next = (node_t *) malloc(sizeof(node_t));
		current->val = rand()%100;
		current = current->next;
		i++;
	}

	current->val = rand()%100;
	current->next = NULL;

	print_list(head);

	/* ... some cool code... */


	

	/* Raspunsul universal :). */
	/* ... more badass code ... */

	

	/**************************************************************************
	 * Test Task 4.
	 */
	current->next = create(11);
	print_list(head);
	/* ... a long time ago ... */


	/**************************************************************************
	 * Test Task 5.
	 */
	head = append_node(head,42); 
	print_list(head);


	/**************************************************************************
	 * Test Task 5.
	 */

	/* ... in a galaxy far far away ... */


	/**************************************************************************
	 * Test Task 5.
	 */
	head = prepend_node(head,49);
	print_list(head);


	/**************************************************************************
	 * Test Task 6.
	 */
	current = get_node(head,11);
	print_list(current);


	/**************************************************************************
	 * Test Task 7.
	 */
	current = modify_node(head,11,rand()%100);
	print_list(current); 


	/**************************************************************************
	 * Test Task 8.
	 */
	current = insert_node(head,34,27);
	print_list(head);


	/**************************************************************************
	 * Test Task 9.
	 */
	current = remove_node(head,27);
	print_list(head);

	return 0;
}

/**
 * TASK 2.
 *
 * Functia primeste o valoare, creeaza un nou nod cu aceasta
 * valoare si returneaza un pointer catre nodul creat.
 */
node_t *create(int val)
{
	node_t * current;

	current = (node_t *) malloc(sizeof(node_t));
    current->val = val;
    current->next = NULL;

	return current;
}


/**
 * TASK 3.
 *
 * Functia creaza un nou nod cu valoarea 'val' 
 * si il adauga la finalul listei.
 *
 * Functia returneaza noul cap al listei (daca e cazul), sau vechiul.
 */
node_t *append_node(node_t *list_head, int val)
{
	node_t * current = list_head;
    while (current->next != NULL) 
	{
        current = current->next;
    }

    current->next = create(val);

	return list_head;
}

/**
 * TASK 4.
 *
 * Functia afiseaza la stdout continutul listei.
 * Valorile sunt separate prin virgula.
 */
void print_list(node_t *list_head)
{
	node_t * current = list_head;

    while (current != NULL) 
	{
		if(current->next != NULL)
        	printf("%d, ", current->val);
		else printf("%d", current->val);
		
        current = current->next;
    }

	printf("\n");

}

/**
 * TASK 5.
 *
 * Functia creaza un nou nod cu valoarea 'val' 
 * si il adauga la finalul liste.
 *
 * Functia returneaza noul cap al listei (daca e cazul), sau vechiul.
 */
node_t *prepend_node(node_t *list_head, int val)
{
	node_t *new_head;

	new_head = (node_t *) malloc(sizeof(node_t));
	new_head->val = val;
	new_head->next = list_head;

	return new_head;
}

/**
 * TASK 6.
 *
 * Functia primeste un numar intreg si cauta in lista acest numar.
 * Daca gaseste numarul in lista, returneaza nodul care il contine.
 * Daca nu il gaseste returneaza NULL.
 * Daca elementul apare de mai multe ori, se returneaza prima aparitie.
 */
node_t *get_node(node_t *list_head, int val)
{
	node_t* current;

	current = (node_t *) malloc(sizeof(node_t));
	current = list_head;

	while(current->val != val && current != NULL)
	{
		current=current->next;
	}

	if(current->val == val)
		return current;

	return NULL;
}

/**
 * TASK 7.
 *
 * Functia cauta valoarea 'val' in lista si daca gaseste un element
 * cu aceasta valoare o schimba cu 'new_val'.
 *
 * Functia returneaza un pointer catre acest element, sau
 * NULL daca nodul nu exista.
 */
node_t *modify_node(node_t *list_head, int val, int new_val)
{
	node_t* current;

	current = (node_t *) malloc(sizeof(node_t));

	current = get_node(list_head,val);

	if(current != NULL)
	{
		current->val = new_val;
		return current;
	}

	return NULL;
}

/**
 * TASK 8.
 *
 * Functia creaza un nod nou cu valoarea 'after_val' si il 
 * insereaza dupa nodul cu valoarea 'val'. 
 * Se returneaza un pointer catre nodul nou creat.
 *
 * Daca nodul cu valoarea 'val' nu exista in lista, lista
 * ramane nemodificata si se returneaza capul listei.
 */
node_t *insert_node(node_t *list_head, int val, int after_val)
{
	node_t* new;

	new = (node_t *) malloc(sizeof(node_t));

	new = get_node(list_head,val);

	if(new != NULL)
	{
		new->next = prepend_node(new->next,after_val);
		return new;
	}

	return list_head;

}


/**
 * TASK 9.
 *
 * Functia cauta nodul cu valoarea 'val' si il sterge din lista.
 * Functia returneaza noul cap al listei (daca e cazul), sau vechiul.
 *
 * Daca nodul cu valoarea 'val' nu exista in lista, lista
 * ramane nemodificata si se returneaza capul listei.
 */
node_t *remove_node(node_t *list_head, int val)
{
	node_t *current;

	current = (node_t *) malloc(sizeof(node_t));

	current = list_head;
	
	while(current->next->val != val && current != NULL)
		current = current->next;

	if(current != NULL)
		current->next = current->next->next;

	return current;

}
