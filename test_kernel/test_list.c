#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

struct person {
	uint32_t index;
	uint32_t age;
	char* name;
	uint32_t sex;
	char* id;
	struct list_head list;
};

void test_list() {
	int i = 0;
	struct list_head person_list;
	struct list_head *pos;
	struct list_head *tmp;
	struct person *p;
	int count = 0;

	srand(time(NULL));
	INIT_LIST_HEAD(&person_list);

	//插入元素
	for (i = 0; i < 20; i++) {
		p = (struct person*) malloc(sizeof(struct person));
		p->index = i + 1;
		p->age = rand() % 100 + 1;
		//p->name = (char*)malloc(5);
		//strncpy(p->name,"abcd",strlen("abcd")+1);

		list_add_tail(&p->list, &person_list);
	}

	//遍历
	list_for_each_safe(pos,tmp,&person_list) {
		p = list_entry(pos,struct person,list);
		printf("index:%d age:%d\n", p->index, p->age);
		count++;
	}
	printf("total:%d\n", count);

	//找到第一个元素
	p = list_first_entry(&person_list,struct person,list);
	printf("first index:%d ,age:%d\n", p->index, p->age);

	//list左旋
	list_rotate_left(&person_list);
	p = list_first_entry(&person_list,struct person,list);
	printf("first index:%d age:%d\n", p->index, p->age);

	//删除元素
	list_for_each_safe(pos,tmp,&person_list) {
		p = list_entry(pos,struct person,list);
		free(p);
		list_del(pos);
	}

	//list是否为空
	printf("%s\n", list_empty(&person_list) ? "empty" : "not empty");
}

int main(int argc, char* argv[]) {
	test_list();
}
