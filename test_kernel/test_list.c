#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct person
{
	int age;
	struct list_head list;
};

struct list_head person_list;

int main(int argc,char* argv[])
{
	int i =0;
	struct person *p;
	struct list_head *tmp;
	struct list_head *pos;

	INIT_LIST_HEAD(&person_list);
	for(i=0;i<5;i++)
	{
		p =(struct person*)malloc(sizeof(struct person));
		p->age = 20+i;
		INIT_LIST_HEAD(&p->list);
		list_add(&p->list,&person_list);
	}

//	list_for_each(pos,&person_list)
//	{
//		p=list_entry(pos,struct person,list);
//		printf("age:%d\n",p->age);
//	}

	list_for_each_safe(pos,tmp,&person_list)
	{
		p = list_entry(pos,struct person,list);
		if(p->age == 21)
		{
			list_del(&p->list);
			free(p);
		}
	}

	list_for_each_safe(pos,tmp,&person_list)
	{
		p=list_entry(pos,struct person,list);
//		printf("age:%d\n",p->age);
//		free(pos);
		list_del(&p->list);
		free(p);
	}

	list_for_each(pos,&person_list)
	{
		p=list_entry(pos,struct person,list);
		printf("age:%d\n",p->age);
	}
}
