#include "BigInteger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Include ctype.h for isdigit

int isZero(struct BigInteger a)
{
    if(!(a.head)||(a.length==1 && a.head->data==0))
    {
        return 1;
    }
    struct node* itr=a.head;
    while(itr!=NULL)
    {
        if(itr->data!=0)
            return 0;
        itr=itr->next;
    }
    return 1;
}
void insertAtBegin(struct node** head, int k) {
    struct node* temp = createNode(k);
    temp->next = *head;

    // New head
    *head = temp;
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
    struct BigInteger quotient;
    quotient.head = NULL;
    quotient.length = 0;
    quotient.sign = a.sign * b.sign;

    struct BigInteger remainder;
    remainder.head = NULL;
    remainder.length = 0;
    remainder.sign = 1;

    if (Compare(a, b) < 0) {
        // If a < b, the quotient is 0 and the remainder is a
        quotient.head = createNode(0);
        quotient.length = 1;
        return quotient;
    }

    struct node* current = a.head;
    while (current) {
        // Append the current digit to the remainder
        struct node* newNode = createNode(current->data);
        newNode->next = remainder.head;
        remainder.head = newNode;
        remainder.length++;

        // Check if the remainder is greater than or equal to b
        while (Compare(remainder, b) >= 0) {
            // Subtract b from the remainder
            remainder = sub(remainder, b);

            // Increment the quotient
            quotient.head = createNode(quotient.head ? quotient.head->data + 1 : 1);
            quotient.length++;

            // Remove leading zeros from the remainder
            while (remainder.head && remainder.head->data == 0) {
                struct node* temp = remainder.head;
                remainder.head = remainder.head->next;
                free(temp);
                remainder.length--;
            }
        }

        current = current->next;
    }

    // Remove leading zeros from the quotient
    while (quotient.head && quotient.head->data == 0) {
        struct node* temp = quotient.head;
        quotient.head = quotient.head->next;
        free(temp);
        quotient.length--;
    }

    // If quotient is empty, set it to 0
    if (!quotient.head) {
        quotient.head = createNode(0);
        quotient.length = 1;
    }

    return quotient;
}
    /*long int quotient = 0;
    struct BigInteger result;
    struct BigInteger aTemp;
    result.sign = a.sign * b.sign;
    a.sign = 1;
    b.sign = 1;
    aTemp=a;
    if (b.head==NULL||isZero(b)) {
        printf("INVALID");
        result.head = NULL;
    }
    
    if (a.head==NULL||isZero(a)) {
        result.head = createNode(0);
        return result;
    } else {
        struct BigInteger rem;
        while (Cmp(aTemp,b)==1) {
            aTemp=sub(aTemp,b);
            quotient++;
        }
    result.head=createNode(quotient);
    return result;
    }*/
int Compare(struct BigInteger a, struct BigInteger b) {
    int max=1;
    if (a.length < b.length)
        return 2;
    else if (a.length > b.length)
        return 1;
    else {
        struct BigInteger num1 = a;
        struct BigInteger num2 = b;
        reverse(&num1.head);
        reverse(&num2.head);
        struct node* itr1 = num1.head;
        struct node* itr2 = num2.head;
        while (itr1 && itr2) {
            if (itr1->data > itr2->data)
            {
                max= 1;
                break;
            }
            if (itr1->data < itr2->data)
            {
               max= 2;
                break;
            }
            itr1 = itr1->next;
            itr2 = itr2->next;
        }
    reverse(&num1.head);
    reverse(&num2.head);
    
    }
    return max;
}

struct node* addition(struct node* num1, struct node* num2) {
    int sum, carry = 0;
    struct node* result = NULL;
    //itr used to treverse resultant LL
    struct node* itr = NULL;
    while (num1 && num2) {
        sum = num1->data + num2->data + carry;
        carry = sum / 10;
        
        //loop for the first time
        if (result == NULL) {
            result = createNode(sum % 10);
            itr = result;
        } 
        else {
            itr->next = createNode(sum % 10);
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1) {
        sum = num1->data + carry;
        carry = sum / 10;
        itr->next = createNode(sum % 10);
        num1 = num1->next;
        itr = itr->next;
    }
    while (num2) {
        sum = num2->data + carry;
        carry = sum / 10;
        itr->next = createNode(sum % 10);
        num2 = num2->next;
        itr = itr->next;
    }
    if (carry > 0) {
        itr->next = createNode(carry);
    }
    return result;
}
void insertAtEnd(struct node**Head,int insert)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = insert;
    newNode->next=NULL;
    if(*Head==NULL)
    {
        *Head=newNode;
        (*Head)->next=NULL;
        return;
    }
    struct node *iter=*Head;
    while(iter->next)
        iter=iter->next;
    iter->next=newNode;
}
struct node* multiply(struct node* num1, struct node* num2) {
    struct node* result = createNode(0);
    struct node* tempResult = NULL;
    int pos = 0; // For the position of the second number's digit

    while (num2) {
        int carry = 0;
        struct node* num1Copy = num1;
        tempResult = NULL;
        for (int i = 0; i < pos; i++)
            insertAtBegin(&tempResult, 0); // Initialize with trailing zeros

        while (num1Copy) {
            int product = 0;
            product = (num1Copy->data) * (num2->data) + carry;
            carry = product / 10;
            insertAtEnd(&tempResult, product % 10); // Append the result to the currentResult
            num1Copy = num1Copy->next;
        }

        if (carry > 0) {
            insertAtEnd(&tempResult, carry); // If there is a carry, add it
        }

        result = addition(result, tempResult); // Add currentResult to the overall result
        num2 = num2->next;
        pos++;
    }
    return result;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger result;
    result.head=(struct node*)malloc(sizeof(struct node));

    if(isZero(a)||isZero(b))
    {
        result.head=createNode(0);
        result.sign=1;
    }
    else
    {
        result.head=multiply(a.head,b.head);
        result.sign=a.sign*b.sign;
    }
    result=truncateZeros(result);
    return result;
}
struct node* subtract(struct node* num1, struct node* num2) {
    int diff=0, borrow = 0;
    struct node* res = NULL;
    struct node* itr = num1;
    while (num1 && num2) {
        diff = num1->data - num2->data - borrow;
        if (diff < 0) {
            borrow = 1;
            diff = diff + 10;
        } else {
            borrow = 0;
        }
        if (res == NULL) {
            res = createNode(diff);
            itr = res;
        } else {
            itr->next = createNode(diff);
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1) {
        diff = num1->data - borrow;
        if (diff < 0) {
            borrow = 1;
            diff = diff + 10;
        } else {
            borrow = 0;
        }
        itr->next = createNode(diff);
        itr = itr->next;
        num1 = num1->next;
    }
    return res;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    if (a.sign == b.sign) {
        result.head = addition(a.head, b.head);
        result.sign = a.sign;
    }
    else if(a.sign==1&&b.sign==-1)
    {
        b.sign=1;
        result=sub(a,b);

    }
    else
    {
        a.sign=1;
        result=sub(b,a);
    }
     result=truncateZeros(result);
    return result;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    struct node* itr1=a.head;
    struct node* itr2=b.head;
    if (a.sign != b.sign) {
        result.head = addition(a.head, b.head); // Fixed function call
        result.sign = a.sign;
    } else {
        int max;
        max = Cmp(a, b);
        if (max == 1)
        {
            result.head = subtract(a.head, b.head);
            result.sign=1;
        }
        else {
            result.head = subtract(b.head, a.head);
            result.sign = -1;
        }
        result.sign = a.sign * result.sign;
    }
    result=truncateZeros(result);
    return result;
}

void reverse(struct node** head) {
    struct node* itr = *head;
    struct node* prev = NULL;
    struct node* nextNode = NULL;
    while (itr != NULL) {
        nextNode = itr->next;
        itr->next = prev;
        prev = itr;
        itr = nextNode;
    }
    *head = prev;
}

void display(struct BigInteger num) {
    if(isZero(num))
        num.sign=1;
    struct node* itr = num.head;
    reverse(&itr);

    if (num.sign == -1) {
        printf("-");
    }

    while (itr != NULL) {
        printf("%d", itr->data);
        itr = itr->next;
    }
    printf("\n");
}
struct BigInteger initialise(char* s) {
    struct BigInteger num1;
    num1.length = strlen(s);
    num1.sign = 1;
    num1.head = NULL;
    for (int i = 0; i < num1.length; i++) {
        if (isdigit(s[i]))
            insertAtBegin(&(num1.head), (s[i] - '0'));
        else {
            num1.sign = -1;
        }
    }
    if (num1.sign == -1)
        num1.length--;
    num1=truncateZeros(num1);
    return num1;
}
struct node* createNode(int value) {
    struct node* t = (struct node*)malloc(sizeof(struct node));
    if (t == NULL) {
        printf("Memory ERROR!\n");
        return NULL;
    }
    t->data = value;
    t->next = NULL;
    return t;
}
struct BigInteger truncateZeros(struct BigInteger num)
{
    reverse(&num.head);
    // Remove leading zeroes
    while (num.head != NULL && num.head->data == 0) {
        struct node* temp = num.head;
        num.head = num.head->next;
        free(temp);
        num.length--;

        if (num.length == 0) {
            num.sign = 1; // Set the sign to positive if the number is zero
            break;
        }
    }

    // Ensure that the head node stores the unit place
    if (num.head == NULL) {
        num.head = createNode(0);
        num.length = 1;
        num.sign = 1;
    }
    reverse(&num.head);
    return num;
}
