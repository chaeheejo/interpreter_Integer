//
//  interpreter.c
//  PL
//
//  Created by chaehee on 2021/03/10.
//
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name;
    char value[10];
}variable; //변수명과 값을 저장할 구조체

void initVariable(variable* num) { //구조체 초기화
    num->name = NULL;

    for (int i = 0; i < 10; i++) {
        num->value[i] = NULL;
    }
}

int main(void) {
    variable num;
    initVariable(&num);

    num.name = getchar(); //변수명을 입력 받음

    char equal;
    equal = getchar(); //'=' 문자를 입력 받음
    if (equal != '=') { //'=' 문자를 제대로 입력했는지 확인
        printf("치환문을 잘못 입력하셨습니다.");
        return;
    }

    int lastValue = 0; //변수의 값이 몇 자리 수인지 저장
    for (int i = 0; i < 10; i++) {
        num.value[i] =getchar(); //변수의 값을 저장함
        if (!(num.value[i] >='0' && num.value[i]<='9')) { //정수가 아닌 다른 자료형이면, 반복문을 멈춤
            lastValue = i; //몇 자리 수인지 저장
            break;
        }
    }

    char compare; //'print' 명령문을 제대로 입력했는지 비교하기 위한 변수
    for (int i = 0; i < 5; i++) {
        switch(i)
        {
            case 0 :
                compare = getchar();
                if (compare != 'p') {
                    printf("예약어를 잘못 입력하셨습니다.");
                    return;
                }
                break;
            case 1:
                compare = getchar();
                if (compare != 'r') {
                    printf("예약어를 잘못 입력하셨습니다.");
                    return;
                }
                break;
            case 2:
                compare = getchar();
                if (compare != 'i') {
                    printf("예약어를 잘못 입력하셨습니다.");
                    return;
                }
                break;
            case 3:
                compare = getchar();
                if (compare != 'n') {
                    printf("예약어를 잘못 입력하셨습니다.");
                    return;
                }
                break;
            case 4:
                compare = getchar();
                if (compare != 't') {
                    printf("예약어를 잘못 입력하셨습니다.");
                    return;
                }
                break;
            
        }
    }
    getchar(); //공백 문자 삭제


    char infix[20]; //변수명 대신, 변수값이 대입된 전위 표기법으로 표현된 수식
    char postfix[20]; //후위 표기법으로 표현된 수식
    char temp[20]; //변수명으로 입력된 수식

    for (int i = 0; i < 20; i++) { //배열의 값을 초기화
        infix[i] = NULL;
        postfix[i] = NULL;
        temp[i] = NULL;
    }

    int i = 0;
    int lastIndex = 0; //수식의 길이를 저장
    do {
        scanf_s("%c", &temp[i], sizeof(1)); //'print ' 예약어 뒤의 수식을 입력 받음
        lastIndex = i;
        i++;
    } while (temp[lastIndex] != '\n'); //엔터가 나올 때까지 입력 받음

    int indexName=0; //수식에서 변수 이름을 값으로 바꾸기 위해 변수 이름이 위치한 인덱스를 저장
    bool check = false; //변수 이름을 제대로 입력했는지 확인
    for (int i = 0; i <= lastIndex; i++) { //수식의 길이만큼 반복문을 실행
        if (temp[i]==num.name) { //수식을 입력 받은 temp 배열에서 변수 이름을 찾았다면,
            indexName = i; //인덱스를 저장
            check = true;
            break;
        }
    }
    if (check==false) { //수식에 변수 이름이 포함되지 않았을 경우,
        printf("변수명을 잘못 입력하셨습니다.");
        return;
    }
    else if (check == true && lastIndex == 1) { //변수만 입력했을 경우,
        for (int i = 0; i < lastValue; i++) {
            printf("%c", num.value[i]); //변수값만 출력
        }
        return;
    }

    int m = 0; //infix배열의 인덱스를 관리하는 변수
    for (int i = 0; i < lastIndex+lastValue; i++) { //변수명이 포함된 초기의 수식의 길이와 변수 값의 자리수를 더하면 총 수식의 길이가 됨
        if (i < indexName || i>indexName) { //변수명의 위치보다 왼쪽이나 오른쪽에 있을 경우,
            infix[m] = temp[i]; //그대로 infix에 저장해줌
            m++;
        }
        else if (i == indexName) { //변수명 위치에 도달했을 경우,
            for (int j = 0; j < lastValue; j++) { //변수 값의 자리수만큼 반복문 실행
                infix[m] = num.value[j]; //infix 배열에 변수명 대신, 변수의 값을 저장해줌
                m++;
            }
        }
    }

    changePostfix(&infix, &postfix); //infix 배열을 후위 표기법으로 변환하여 postfix에 저장함
    printf("%d", compute(&postfix)); //후위 표기법으로 변환한 수식을 계산하여 출력함
}
