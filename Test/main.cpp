#include <stdio.h>

int main()
{
    char str1 [8] = "privet";
    char str2 [8] = "privet";

    int result = 2;

    asm volatile
    (
        ".intel_syntax noprefix;"

        "xor rax, rax;"
        "cld;"
        "while:;"

        "mov ah , byte [rsi - 1];"
        "cmp ah , 0;"
        "je zeroFound;"

        "cmpsb;"
        "je notEqual;"

        "mov al, 1;"
        "jmp endOfWord;"
        "notEqual:;"

        "jmp while;"
        "zeroFound:;"
        "mov ah, byte [rdi - 1];"
        "cmp ah, 0;"
        "je endOfWord;"
        "mov al, 1;"

        "endOfWord:;"
        "xor ah, ah;"
        ".att_syntax noprefix;"

        : "=a"(result)
        : "S"(str1), "D"(str2)
    );




   printf ("%d", result);

    return 0;
}









/*
            asm volatile
            (
                ".intel_syntax noprefix;"

                "nop\n"
                "nop\n"
                "nop\n"

                "xor rax, rax;"

                "while: ;"

                "cmp [rsi], 0;"
                "je zeroFound;"

                "cmpsb;"
                "je notEqual;"

                "mov rax, 1;"
                "jmp endOfWord;"

                "notEqual: ;"

                "jmp while;"

                "zeroFound: ;"
                "cmp r9, 0;"
                "je endOfWord;"
                "mov rax, 1;"

                "endOfWord: ;"

                ".att_syntax noprefix;"

                : "=a"(result)
                : "S"(str1), "D"(str2)
            );

*/
