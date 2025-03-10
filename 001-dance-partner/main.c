#include <stdio.h>
#include "sq_queue.h"

int dancer_match(sq_queue_t *m_dancer_pt, sq_queue_t *f_dancer_pt)
{
	int count = 0;
	while (!queue_empty(m_dancer_pt) && !queue_empty(f_dancer_pt))
	{
		QElemType m_elem, f_elem;
		queue_pop(m_dancer_pt, &m_elem);
		queue_pop(f_dancer_pt, &f_elem);
		printf("%d dance team: [%s(M), %s(F)]\n", ++count, m_elem.name, f_elem.name);
	}
	if (0 == count)
	{
		printf("Not combine any dance team.");
	}
	return OK;
}

int main()
{
	/* define male and female dancer queue */
	sq_queue_t m_dancer_t;
	sq_queue_t f_dancer_t;
	person_t person[MAX_Q_SIZE] = {0};
	int num_of_person = 0;

	queue_init(&m_dancer_t);
	queue_init(&f_dancer_t);

	printf("Please input numbers of dancer(numbers > 0):");
	scanf("%d", &num_of_person);
	printf("\n");

	printf("Please input dancer info(name and sex).\n"
		   "the input format is name \\space sex.\n"
		   "name: max len is 10 characters.\n"
		   "sex: M is male, F is female. you can only input M or F.\n");
	for (int i = 0; i < num_of_person; i++)
	{
		printf("The %d dancer info:", i + 1);
		scanf("%s %c", person[i].name, &person[i].sex);
	}

	for (int i = 0; i < num_of_person; i++)
	{
		if (person[i].sex == 'M')
			queue_push(&m_dancer_t, person[i]);
		else if (person[i].sex == 'F')
			queue_push(&f_dancer_t, person[i]);
	}
	printf("\n");
	dancer_match(&m_dancer_t, &f_dancer_t);
	
	printf("After male and female combine a team, numbers of surplus male: %d\n", queue_length(&m_dancer_t));
	printf("After male and female combine a team, numbers of surplus female: %d\n", queue_length(&f_dancer_t));
	
	queue_destory(&m_dancer_t);
	queue_destory(&f_dancer_t);
	return 0;
}