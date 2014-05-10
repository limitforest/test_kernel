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
	struct hlist_node hash;
};

#define LIST_NUMBER 50
#define HASH_NUMBER (LIST_NUMBER*2)

struct hlist_head hash_table[HASH_NUMBER];

//哈希函数
int hash(struct person* p)
{
	return p->age % HASH_NUMBER;
}

void test_hlist() {
	int i = 0;
	int key = 0;
	int count = 0;
	int low ,high;
	struct person* p;
	struct hlist_node* pos;
	struct hlist_node* tmp;

	srand(time(NULL));

	for(i=0;i<HASH_NUMBER;i++)
	{
		INIT_HLIST_HEAD(&hash_table[i]);
	}

	for(i=0;i<LIST_NUMBER;i++)
	{
		p = (struct person*)malloc(sizeof(struct person));
		p->age = rand() % 100 + 1;
		p->index = i+1;

		//计算哈希值
		key=hash(p);
		//插入到哈希值对应的hlist
		hlist_add_head(&p->hash,&hash_table[key]);
	}

	for(i=0;i<HASH_NUMBER;i++)
	{
		printf("hash[%d]:",i);
		hlist_for_each_safe(pos,tmp,&hash_table[i])
		{
			p = hlist_entry(pos,struct person,hash);
			printf("[index:%d,age:%d]-->",p->index,p->age);
			count++;
		}
		printf("NULL\n");
	}
	printf("total:%d\n",count);

	//找到某个年龄范围的人，并删除
	for(low=30,high=40,i=low;i<=high;i++)
	{
		hlist_for_each_safe(pos,tmp,&hash_table[i])
		{
			p =hlist_entry(pos,struct person,hash);
			hlist_del(&p->hash);
			count--;
			printf("[index:%d,age:%d]",p->index,p->age);
			free(p);
		}
	}
	printf("\n");
	printf("remove age between 30 and 40,remain:%d\n",count);
}

int main(int argc, char* argv[]) {
	test_hlist();
}
