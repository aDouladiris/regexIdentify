#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_STATES 1
#define STATES 'A'

#define NUMBER_OF_INPUT_SYMBOLS 2
#define INPUT_SYMBOLS '(', ')'

#define NUMBER_OF_STACK_SYMBOLS 2
#define STACK_SYMBOLS 'I', 'V'

#define INITIAL_STATE 'A'
#define INITIAL_STACK_SYMBOL 'V'

typedef struct node
{
	char data;
	struct node* next;	
}type_list;

void stack_subroutine_push(type_list** stack_ptr, char symbol)
{
	if (*stack_ptr == NULL)
	{
		*stack_ptr = (type_list*)malloc(sizeof(type_list));
		(*stack_ptr)->data = symbol;
		(*stack_ptr)->next = NULL;
	}
	else
	{
		type_list* new_node = (type_list*)malloc(sizeof(type_list));
		new_node->data = symbol;
		new_node->next = (*stack_ptr);
		(*stack_ptr) = new_node;
	}
}

char stack_subroutine_pop(type_list** stack_ptr)
{	
	char symbol;
	
	if (*stack_ptr == NULL)
	{
		printf("The stack is empty. Cannot pop symbol\n");
	}
	else
	{
		symbol = (*stack_ptr)->data;
		type_list* tmp;
		
		tmp = *stack_ptr;		
		*stack_ptr = (*stack_ptr)->next;
		
		free(tmp);	

		return symbol;
	}
}

void stack_subroutine_pass(type_list** stack_ptr)
{			
	printf("----------------------------------------\n");
	printf("Leave stack as it is\n");

}

void input_subroutine_move(type_list** input_ptr)
{
	type_list* tmp;	
	
	//printf("inside: %c\n", (*input_ptr)->data );
	
	if (*input_ptr == NULL)
	{
		printf("The input is empty. Cannot pop symbol\n");
		return;
	}
	else
	{
		tmp = *input_ptr;
		*input_ptr = tmp->next;
		
		free(tmp);
	}
}

type_list* input_subroutine_hold(type_list* input_ptr)
{
	printf("----------------------------------------\n");
	printf("Input reader is on hold\n");
	return input_ptr;
	
}

void state_init(char* state, char symbol)
{
	*state = symbol;
}

void stack_init(type_list** stack_ptr, char symbol)
{
	if (*stack_ptr == NULL)
	{
		*stack_ptr = (type_list*)malloc(sizeof(type_list));
		(*stack_ptr)->data = symbol;
		(*stack_ptr)->next = NULL;
	}
}

char state_reader(char* state)
{
	printf("state %-15c\t\t", *state);
}

void input_init(type_list** input_ptr, char symbol)
{
	if (*input_ptr == NULL)
	{
		*input_ptr = (type_list*)malloc(sizeof(type_list));
		(*input_ptr)->data = symbol;
		(*input_ptr)->next = NULL;
	}
	else
	{
		type_list* new_node = (type_list*)malloc(sizeof(type_list));
		new_node->next = NULL;
		
		type_list* tmp = *input_ptr;
	 	while(tmp->next != NULL)
	 	{ 			 		
	 		tmp = tmp->next; 		
		}
		
		tmp->next = new_node;
		new_node->data = symbol;					
	}
}

void list_reader(type_list** list_ptr, char* name)
{
	if (*list_ptr == NULL)
	{
		printf("The %s is empty\t\t\t", name );
		return;
	}	
	
	type_list* cnt = *list_ptr;    
    
    int input_size = 0;
 	while(cnt != NULL)
 	{ 		 
		input_size++;
 		cnt = cnt->next; 		
	}
	
	char input_to_string[input_size];
	
	type_list* tmp = *list_ptr;
	
	char* cpy_to_array = input_to_string;
	
 	while(tmp != NULL)
 	{
 		*cpy_to_array = tmp->data;

 		tmp = tmp->next;
 		
		cpy_to_array++;
		
		if ( tmp == 0)
 		{
 			*cpy_to_array = '\0';
		}		
	}	
	
	printf("State of the %s %15s\t", name, input_to_string);

}

bool value_in_set(char val, char* arr, int size_arr)
{
	for ( int i=0; i<size_arr; i++ )
	{
		if (arr[i] == val)
		{
			return true;
		}
	}
	return false;
}

void transition_function(type_list** input_ptr, type_list** stack_ptr, char* state)
{
	//Rules
	if ( *state == 'A' && (*stack_ptr)->data == 'I' && (*input_ptr)->data == '(' )		//1st rule
	{
		stack_subroutine_push(stack_ptr, 'I');
		*state = 'A';
		input_subroutine_move(input_ptr);		
	}	
	else if ( *state == 'A' && (*stack_ptr)->data == 'I' && (*input_ptr)->data == ')' )		//2nd rule
	{
		stack_subroutine_pop(stack_ptr);
		*state = 'A';
		input_subroutine_move(input_ptr);		
	}
	else if ( *state == 'A' && (*stack_ptr)->data == 'V' && (*input_ptr)->data == '(' )		//3rd rule
	{
		stack_subroutine_push(stack_ptr, 'I');
		*state = 'A';
		input_subroutine_move(input_ptr);
	}	
	else
	{
		printf("No transition state detected\n");
	}

}

void acceptance_criteria(type_list** stack_ptr, char symbol)
{
	if ( (*stack_ptr)->data == symbol)
	{
		printf("Yes\n");		
	}
	else
	{
		printf("No\n");
	}
}

int main()
{	
	char states[NUMBER_OF_STATES] = {STATES};
	char input_symbols[NUMBER_OF_INPUT_SYMBOLS] = {INPUT_SYMBOLS};
	char stack_symbols[NUMBER_OF_STACK_SYMBOLS] = {STACK_SYMBOLS};

	//Var Initialization
	char state;
	type_list* input = NULL;
	type_list* stack = NULL;
	
	char symbol;
	int end_of_file;
	
	//Automaton initialization
	state_init(&state, INITIAL_STATE);
	stack_init(&stack, INITIAL_STACK_SYMBOL);
	
	
	//Stdin reading
	int symbol_counter = 0;
	while(end_of_file != EOF)
	{
		symbol = getc(stdin);
		end_of_file = (int)(symbol);
		
		if ( value_in_set(symbol, input_symbols, NUMBER_OF_INPUT_SYMBOLS) )
		{
			input_init(&input, symbol);
			symbol_counter++;
		}
			
	}


	int j = 0;
	list_reader(&input, "input" );
	list_reader(&stack, "stack" );	
	state_reader(&state);
	printf("Move %-15s\n", "No move");
	
	
	while (j < symbol_counter)
	{
		
		transition_function( &input, &stack, &state );	
		list_reader(&input, "input" );
		list_reader(&stack, "stack" );	
		state_reader(&state);
		printf("Move %-15i\n", j+1);
		j++;		
	}
	

	
	acceptance_criteria(&stack, INITIAL_STACK_SYMBOL);

}













