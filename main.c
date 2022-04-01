#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){
    char arr[10]; //변수명을 입력 받을 배열 arr

    for (int i=0;i<10;i++){
        scanf("%c", arr);
    }

    int equalIndex=0; //"=" 기호의 위치를 저장할 변수

    char strString; //변수명 
    char initString[8]; //초기화 할 변수값의 문자
    int initInt; //초기화 할 변수값의 정수
    
    for(int i=0;i<10;i++){
        if(arr[i]=='=')
            equalIndex=arr[i]; //"=" 기호의 위치를 알아냄
    }
    
    //입력한 치환문 분석
    for(int i=0;i<10;i++){
        if(i<equalIndex){  //"=" 기호 앞의 변수 명
            strString=arr[i];
        }
        else if(i>equalIndex && arr[i]!='\0'){ //"=" 기호 뒤의 변수 값
            if(arr[i]>='0' && arr[i]<='9'){  //변수 값이 정수인지 확인
                
            }
            else //정수 이외의 수가 들어왔을 경우, 에러 메시지 출력
            {
                printf("변수의 값에는 정수만을 지정하실 수 있습니다.");
                return 0;
            }
        }
    }

    initInt=autoi(initString); //변수 값을 정수로 저장

    char arr2[20]; //프린트문을 입력 받을 배열 arr2
    char *checkReserved; //프린트문의 예약어를 확인할 변수
    scanf("%s", arr2);


    for(int i=0;i<5;i++){
        checkReserved +=arr2[i];
    }

    if(checkReserved != "print"){ //예약어가 print인지 확인
        printf("예약어 print를 사용한 명령문을 입력해주세요.");
    }

    /*for (int i=5;i<20;i++){
        if()
    }*/
}
