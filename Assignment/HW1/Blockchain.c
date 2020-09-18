#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/crypto.h>

#define SHA256_DIGEST_LENGTH 32

struct block {
	unsigned char prevHash[SHA256_DIGEST_LENGTH];
	int blockData;
	struct block *link;
}*head;

void addBlock(int);
void verifyChain();
void alterNthBlock(int, int);
void hackChain();
int hashCompare(unsigned char*, unsigned char*);
void hashPrinter();
//void printAllBlocks();

void addBlock(int data) {
	if (head == NULL) {
		head = malloc(sizeof(struct block));
		SHA256("", sizeof(""), head->prevHash);
		head->blockData = data;
		return;
	}
	struct block *currentBlock = head;
	while (currentBlock->link) {
		currentBlock = currentBlock->link;
	}
	struct block *newBlock = malloc(sizeof(struct block));
	currentBlock->link = newBlock;
	newBlock->blockData = data;
	SHA256(toString(*currentBlock), sizeof(*currentBlock), newBlock->prevHash);
}

void verifyChain() {
	if (head == NULL) {
		printf("Blockchain is empty! Please add some blocks first!\n");
		return;
	}
	struct block *curr = head->link, *prev = head;
	int count = 1;
	while (curr) {
		printf("%d\t[%d]\t", count++, curr->blockData);
		hashPrinter(SHA256(toString(*prev), sizeof(*prev), NULL), SHA256_DIGEST_LENGTH);
		printf("  --------  ");
		hashPrinter(curr->prevHash, SHA256_DIGEST_LENGTH);
		if (hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->prevHash))
			printf("Successful verification\n");
		else
			printf("verification failed\n");
		prev = curr;
		curr = curr->link;
	}
}

void alterNthBlock(int n, int newData) {
	struct block *curr = head;
	if (curr == NULL) {
		printf("Nth block does not exist!\n");
		return;
	}
	int count = 0;
	while (count != n) {
		if (curr->link == NULL && count != n) {
			printf("Nth block does not exist!\n");
			return;
		}else if (count == n) {
			break;
		}
		curr = curr->link;
		count++;
	}
	printf("Before: ");
		printBlcok(curr);
	curr->blockData = newData;
	printf("\nAfter: ");
		printBlcok(curr);
}

void hackChain() {
	struct block *curr = head, *prev;
	if (curr == NULL) {
		printf("Blockchain is empty!");
		return;
	}
	while (1) {
		prev = curr;
		curr = curr->link;
		if (curr == NULL) {
			return;
		}
		if (!hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->prevHash)) {
			hashPrinter (
				SHA256(toString(*prev), sizeof(*prev), curr->prevHash),
				SHA256_DIGEST_LENGTH
			);
			printf("\n");
		}
	} 
}

unsigned char* toString(struct block b) {
	unsigned char *str = malloc(sizeof(unsigned char) *sizeof(b));
	memcpy(str, &b, sizeof(b));
	return;
}

void hashPrinter(unsigned char hash[], int length) {
	for (int i = 0; i < length; i++) {
		printf("%02x", hash[i]);
	}
}

int hashCompare(unsigned char *str1, unsigned char *str2) {
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}

void printBlcok(struct block *b) {
	printf("%p]t", b);
	hashPrinter(b->prevHash, sizeof(b->prevHash));
	printf("\t[%d]\t", b->blockData);
	printf("%p\n", b->link);
}

void printAllBlocks() {
	struct block *curr = head;
	int count = 0;
	while (curr) {
		printBlcok(curr);
		curr = curr->link;
	}
}

int main() {
	int c, n, r;
	printf("1. Add block\n2.Add n random blocks\n3.Alter Nth block\n4.Print all blocks\n5.Verify blockchain\n6.Hack blockchain\n");
	while (1) {
		printf("Your choice: ");
		scanf("%d", &c);
		switch(c) {
			case 1: 
				printf("Enter data: ");
				scanf("%d", &n);
				addBlock(n);
				break;
			case 2:
				printf("How many blocks to enter? : ");
				scanf("%d", &n);
				for (int i = 0; i < n; ++i)
				{
					r = rand()%(n*10);
					printf("Entering: %d\n", r);
					addBlock(r);
				}
				break;
			case 3:
				printf("Which block to alter? : ");
				scanf("%d", &n);
				printf("Enter the value: ");
				scanf("%d", &r);
				alterNthBlock(n, r);
				break;
			case 4:
				printAllBlocks();
				break;
			case 5:
				verifyChain();
				break;
			case 6:
				hackChain();
				break;
			default:
				printf("Wrong choice!\n");
				break;
		}
	}
	return 0;
}

//gcc Blockchain.c -o Blockchain.c.o -lcrypto
//./Blockchain.c.o

