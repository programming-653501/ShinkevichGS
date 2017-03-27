/* Программа создает двусвязный циклический список, где хранятся стеки */
/* Программа сортирует символы в стеках в алфавитном порядке */
/* Программа сливает все стеки в один */
/* version 1.0 */


#include <iostream>
using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

struct stack // Стек в виде односвязного списка
{
	char data;
	stack* next;
};

void initStack(stack** s)
{
	*s = nullptr;
}

int isEmpty(stack* s)
{
	if (s == nullptr)
		return 1;
	return 0;
}

void push(stack** s, int x)
{
	stack* p = new stack();

	if (p == nullptr)
	{
		cerr << "Memory allocation failed." << endl;
		return;
	}

	p->data = x;
	p->next = *s;
	*s = p;
}

int pop(stack** s)
{
	int x;
	stack* temp;

	x = (*s)->data;
	temp = *s;
	(*s) = (*s)->next;
	delete temp;

	return x;
}

int top(stack* s)
{
	return s->data;
}

void sortedInsert(stack** s, int x)
{
	if (isEmpty(*s) || x < top(*s))
	{
		push(s, x);
		return;
	}

	int temp = pop(s);
	sortedInsert(s, x);
	push(s, temp);
}

void sortStack(stack** s)
{
	if (!isEmpty(*s))
	{
		int x = pop(s); // Удаляем верхний элемент
		sortStack(s); // Сортируем оставшийся стек
		sortedInsert(s, x); // Возвращаем верхний элемент в сортированный стек
	}
}

void printStack(stack* s)
{
	while (s)
	{
		cout << s->data;
		s = s->next;
	}
	cout << endl;
}

void mergeStack(stack*& s1, stack*& s2)
{
	if (s1->next != nullptr)
		mergeStack(s1->next, s2);
	push(&s2, s1->data);

	delete s1;
	s1 = nullptr;
}


struct list
{ //Двусвязный циклический список
	stack* field;
	list *next, *prev;
};

list* init(stack* start)
{
	list* lst = new list();

	lst->field = start;
	lst->next = lst;
	lst->prev = lst;
	return lst;
}

list* addelem(list* lst, stack* number)
{
	list* temp = new list();
	list* p;

	p = lst->next;
	lst->next = temp;
	temp->field = number;
	temp->next = p;
	temp->prev = lst;
	p->prev = temp;

	return temp;
}

void listprint(list* lst)
{
	list* p;
	p = lst;
	do
	{
		printStack(p->field);
		p = p->next;
	}
	while (p != lst);
}

void mergeAll(list* lst)
{
	list* p;
	p = lst;
	do
	{
		mergeStack(p->field, lst->field);
		p = p->next;
	}
	while (p != lst);
}

void sortAll(list* lst)
{
	list* p;
	p = lst;
	do
	{
		sortStack(&p->field);
		p = p->next;
	}
	while (p != lst);
}

int main()
{
	stack* start;
	initStack(&start);
	push(&start, NULL);

	list* list1;
	list1 = init(start);

	stack* s1;
	initStack(&s1);
	push(&s1, 'k');
	push(&s1, 'f');
	push(&s1, 'i');
	push(&s1, 'a');
	push(&s1, 'p');
	push(&s1, 's');

	stack* s2;
	initStack(&s2);
	push(&s2, 'h');
	push(&s2, 'p');
	push(&s2, 'r');
	push(&s2, 'x');
	push(&s2, 'b');

	stack* s3;
	initStack(&s3);
	push(&s3, 'a');
	push(&s3, 'b');
	push(&s3, 'c');
	push(&s3, 'd');
	push(&s3, 'e');

	addelem(list1, s1);
	addelem(list1, s2);
	addelem(list1, s3);

	cout << "Initial stacks: ";
	listprint(list1);
	cout << endl;

	sortAll(list1);
	cout << "Sorted stacks: ";
	listprint(list1);
	cout << endl;

	mergeAll(list1);
	sortAll(list1);
	cout << "Merged stacks: ";
	listprint(list1);

	keep_window_open();
}
