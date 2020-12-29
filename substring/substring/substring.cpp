
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int substr() {
    char input_s[] = "input string:\n";
    char input_p[] = "input position:\n";
    char result[] = "result:\n%s";
    char incorrect[] = "incorrect position!\n";
    char d[] = "%d";
    char s[] = "%s";

    char str[512];
    char* res;
    int pos = 0;
    __asm {
        ; printf("input string:\n");
        lea     eax, input_s
            push    eax
            call    printf
            add     esp, 4

            ; gets_s(str, 512)
            lea     ebx, str
            push    512
            push    ebx
            call    gets_s
            add     esp, 8

            ; printf("input position:\n");
        lea     eax, input_p
            push    eax
            call    printf
            add     esp, 4

            ; scanf("%d", &pos)
            lea     eax, pos
            push    eax
            lea     eax, d
            push    eax
            call    scanf
            add     esp, 8

            ; Определим длину строки
            ; strlen(str)
            lea     eax, str
            push    eax
            call    strlen
            add     esp, 4

            ; Распределим данные по регистрам :
        ; ebx - str
            ; ecx - n
            ; edx - newSize
            ; esi - i
            ; edi - j
            ; dl и eax - буферный элемент
            ;Найдём длину новой строки
            ; n = strlen(str)
            mov     ecx, eax
            mov     edx, eax
            lea     ebx, str

            ; newSize = n - pos;
        mov     eax, [pos]
            sub     edx, eax

            ; if (newSize < 1 || newSize > n)
            mov     eax, 1
            cmp     edx, eax
            jl      ERR
            cmp     edx, ecx
            jng     MLC

            ERR :
        ; printf("incorrect position!");
        lea     eax, incorrect
            push    eax
            call    printf
            add     esp, 4
            jmp     FIN

            MLC :
        ; сохраняем регистры в стек
            push    edx
            push    ecx

            ; malloc(newSize + 1)
            inc     edx
            push    edx
            call    malloc
            add     esp, 4
            ; выделенная память сохранилась в eax
            ; восстанавливаем n из стека
            pop     ecx

            ; инициализация цикла
            lea     ebx, str
            mov     esi, pos
            xor edi, edi
            FOR :
        ; i < n
            cmp     esi, ecx
            je      NXT
            mov     dl, [ebx][esi]
            mov[eax][edi], dl
            inc     esi
            inc     edi
            jmp     FOR
            NXT :
        pop     edx
            mov[eax][edx], '\0'

            ; printf("result:\n%s", res);
        push    eax
            lea     eax, result
            push    eax
            call    printf
            add     esp, 8
            FIN:
    }
}
int main() {
 
    substr();
    
    return 0;
}
/*
input
012345
 position 
 1
 result 
 12345

input
01&3 45
 position
 1
 result
 1&3 45


 input
abcdefgh
 position
 3
 result
 defgh


input
abc def ger
 position
 4
 result
 def ger

 input
 asdsd
 position 
 -1
 result
 incorrect position!

 input
 asdsd
 position
 120
 result
 incorrect position!

*/