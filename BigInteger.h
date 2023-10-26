#ifndef BigInteger_h
#define BigInteger_h
struct node {
    int data;
    struct node* next;
};
struct BigInteger {
    struct node* head;
    int length;
    int sign;
};
struct BigInteger initialise(char* s); 
struct node* createNode(int value);
void insertAtBegin(struct node** head, int k);
int Compare(struct BigInteger a, struct BigInteger b); 
struct BigInteger add(struct BigInteger a, struct BigInteger b);
void display(struct BigInteger num);
struct node* addition(struct node* num1, struct node* num2);
struct node* subtract(struct node* num1, struct node* num2); 
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
void reverse(struct node** head);
void insertAtEnd(struct node**Head,int insert);
int isZero(struct BigInteger a);
struct BigInteger truncateZeros(struct BigInteger num);

#endif