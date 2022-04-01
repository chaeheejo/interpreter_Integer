//
//  interpreter.c
//  PL
//
//  Created by chaehee on 2021/03/10.
//


#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//  stack

void init(StackType *stack){ //스택 초기화
  stack->top=-1; 
}

bool isFull(StackType *stack){ //스택이 다 찼는지 확인하는 함수
  if(stack->top>=20){ //스택이 다 차면 false
    return false;
  }
  else{ //다 차지 않았으면 true
    return true;
  }
}

bool isEmpty(StackType *stack){ //스택이 비어있는지 확인하는 함수
  if(stack->top==-1){ //스택이 비어있으면 true
    return true;
  }
  else{ //그렇지않으면 false
    return false;
  }
}

int peek(StackType *stack){ //스택의 최상위 원소를 반환하는 함수
  if(isEmpty(stack)){ //스택이 비어있는지 확인
    printf("스택이 비어서 최상위 item을 찾을 수 없습니다. by peek function");
    return 0; 
  }
  else{ //비어있지 않다면, 최상위 원소를 반환
    return stack->stackBuf[stack->top];
  }
}

void push(StackType *stack, element value){ //스택에 원소를 집어 넣는 함수
  if(isFull(stack)){ //스택에 원소가 들어갈 자리가 있는지 확인
    printf("스택이 꽉 차서 item를 넣을 수 없습니다. by push function");
    return;
  }
  else{ //자리가 있다면, 스택에 원소를 저장하고, top을 증가시켜 줌
    stack->stackBuf[++(stack->top)]=value;
  }
}

int pop(StackType *stack){ //스택에 있는 원소를 빼는 함수
  if(isEmpty(stack)){ //스택에 뺄 수 있는 원소가 있는지 확인
    printf("스택이 비어서 item를 뺄 수가 없습니다. by pop function");
    return 0;
  }
  else{ //뺄 원소가 있다면, 스택에 원소를 반환하고, top을 감소시켜 원소를 빼줌
    return stack->stackBuf[(stack->top)--];
  }
}





//  postfix calculator 


role setRole(char *postfix){ //입력받은 문자가 어떤 연산자인지, 피연산자인지 구분
  switch (*postfix)
  {
  case '(':
    return leftBracket;
  case ')':
    return rightBracket;
  case '+':
    return plus;
  case '-':
    return minus;
  case '*':
    return multiply;
  case '/':
    return divide;
  default : return operand;
  }
}


int operator(char op){ //연산자의 우선 순위를 결정하는 함수
  switch (op)
  {
  case '(':
  case ')':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  }
  return -1;
}


void changePostfix(char *infix, char *postfix){ //후위 표기법으로 변환
  StackType stack; //스택 생성
  init(&stack); //스택 초기화

  while (*infix != '\0') //전위 표기법으로 표기된 수식이 null이 아닐 때까지 스택을 이용해 반복하며 후위 표기법으로
  {
    if(*infix=='('){ //수식에 여는 괄호가 있으면,
      push(&stack, *infix); //스택에 여는 괄호를 집어 넣음
      infix++; //infix char 배열의 포인터를 한 자리 앞으로 이동
    }
    else if(*infix==')'){ //수식에 닫는 괄호가 있으면,
      while(peek(&stack)!='('){ //스택에서 여는 괄호를 만날 때까지 
        *postfix++=pop(&stack); //스택 안의 연산자를 빼줌 
        *postfix++=' '; //연산자 빼준 뒤에 postfix에 공백을 넣어줌
      }
    }
    else if(*infix=='+'||*infix=='-'||*infix=='*'||*infix=='/'){ //수식에 연산자가 나온다면,
      while(!isEmpty(&stack) && (operator(*infix)<=operator(peek(&stack)))){ //수식의 연산자와 스택 안의 연산자의 우선순위를 확인한 다음,
        *postfix++ = pop(&stack); //스택의 우선순위가 더 크면 빼서 postfix에 넣어줌
        *postfix++ =' '; //연산자를 뺀 후, 공백을 넣어줌
      }
      push(&stack, *infix); //수식의 연산자가 더 크면, 스택에 넣어줌
      infix++; //infix 배열의 포인터를 한 자리 앞으로 이동
    }
    else if(*infix>='0'&&*infix<='9'){ //수식에 정수가 나온다면,
      do{
        *postfix++ = *infix++; //postfix에 넣어줌
      }while(*infix>='0' && *infix<='9'); //정수가 아닐 때까지 반복
      *postfix++ = ' '; //정수가 끝날 때까지 정수를 넣어준 뒤, 공백을 넣어줌
    }
    else //아무것도 아니면, infix를 한칸 앞으로 이동시킴
    {
      infix++;
    }
  }
  

  while(!isEmpty(&stack)){ //스택이 다 빌 때까지
    *postfix++=pop(&stack); //postfix에 연산자를 넣어줌
    *postfix++=' '; //연산자를 넣어준 다음에는 공백을 만들어 구분
  }
  postfix--; //postfix의 마지막 원소는 공백의 다음을 가르키기 때문에 주소를 뒤로 이동시키고,
  *postfix= '\0'; //null을 가르키게 함
  
}


int changeInt(char *postfix, int *index){
  int result; //int형으로 변환한 원소를 저장할 변수
  char temp[100]; //두 자리 이상의 원소를 임시적으로 저장할 변수
  int i;

  for(i=0; postfix[i]!=' ';i++){ //postfix 문자열에서 원소들을 공백 단위로 구분지어 놨기 때문에 공백을 만날 때까지 반복
    temp[i]=postfix[i]; //공백과 공백 사이의 원소들은 하나의 원소로 취급해야 함
  }

  temp[i]='\0'; //for문의 마지막 과정에서, temp[i]가 공백을 가르키고 있기 때문에 null로 
  result = atoi(temp); //temp에 저장된 char형 정수를 int형으로 변환

  *index +=i; //index를 업데이트 해주고,
  return result; //result를 반환
}

int compute(char *postfix){ //후위 계산식으로 최종적으로 계산할 함수
  role temp; //열거형 자료형 role의 변수
  int result; //수식의 정답을 저장할 변수
  int num1, num2; //계산할 두 연산자를 저장할 변수

  StackType stack; //후위 계산을 위한 스택 생성
  init(&stack); //스택 초기화

  for(int i=0;postfix[i]!='\0';i++){ //후위 계산식이 끝날 때까지 반복문 진행
    if(postfix[i]==' '){ //계산식에 공백이 있으면, 한 자리 앞으로 이동
      i++;
    }
    temp=setRole(&postfix[i]); //postfix i번째의 문자의 역할을 구함
    if(temp==operand){ //temp가 피연산자라면,
      result = changeInt(&postfix[i], &i); //postfix[i]를 int형 변수로 변환해줌
      push(&stack, result); //스택에 넣어줌
    }
    else{ //temp가 연산자라면,
      num2=pop(&stack); //stack에서 연산을 위해 두 피연산자를 빼줌
      num1=pop(&stack);
      switch (temp) //temp의 종류에 따라 맞는 연산을 해준 뒤, 다시 스택에 넣어줌 
      {
      case plus : 
        push(&stack, num1+num2);
        break;
      case minus :
        push(&stack, num1-num2);
        break;
      case multiply :
        push(&stack, num1*num2);
        break;
      case divide:
        push(&stack, num1/num2);
      }
    }
  }

  return pop(&stack); //마지막으로 pop을 해주어 최종 결과값을 반환함
}

int main(void){
  char infix[20];
  char postfix[20];

  scanf("%s", infix);

  changePostfix(*infix, *postfix);

  printf("%s\n", *postfix);
}