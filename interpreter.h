//
//  interpreter.h
//  PL
//
//  Created by chaehee on 2021/03/10.
//

#ifndef interpreter_h
#define interpreter_h

#include <stdio.h>
#include <stdbool.h>

typedef int element;
typedef struct 
{
    element stackBuf[10]; //계산을 위한 원소들이 저장
    int top; //스택의 가장 상위 원소의 위치를 저장
}StackType; //stack 구조체 선언

void init(StackType *stack);
bool isFull(StackType *stack);
bool isEmpty(StackType *stack);
int peek(StackType *stack);
void push(StackType *stack, element value);
int pop(StackType *stack);


typedef enum{
    leftBracket, rightBracket, plus, minus, multiply, divide, operand
}role; //열거형 변수에 연산자의 종류와 피연산자를 저장

role setRole(char *postfix);
int operator(char op);
void changePostfix(char *infix, char *postfix);
int changeInt(char *postfix, int *index);
int compute(char *postfix);

#endif /* interpreter_h */