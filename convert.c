#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *out;

void print_to_out(char s[]){
    fprintf(out, "%s\n", s);
}

int main()
{
    char ch, file_name[25];
    FILE *fp;


    printf("Enter name of a file you wish to compile to C\n");
    gets(file_name);

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    out = fopen("out/output.c", "w");

    print_to_out("#include <stdio.h>");
    print_to_out("#include <stdlib.h>");

    print_to_out(
    "typedef struct DoubleLinkedList{"
        "struct DoubleLinkedList *prev;"
        "unsigned int value;"
        "struct DoubleLinkedList *next;"
    "} DoubleLinkedList;"
    );

    print_to_out("int main(){");
    print_to_out("DoubleLinkedList* current = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));");
    print_to_out("current->value = 0;");
    print_to_out("current->prev = NULL;");
    print_to_out("current->next = NULL;");

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
        switch(ch) {
            case '[':
                print_to_out("while (current->value != 0) {");
                break;
            case ']':
                print_to_out("}");
                break;
            case '+':
                print_to_out("current->value++;");
                break;
            case '-':
                print_to_out("current->value--;");
                break;
            case '<':
                print_to_out(
                "if(current->prev == NULL){"
                    "DoubleLinkedList *a = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));"
                    "a->prev = NULL;"
                    "a->next = current;"
                    "a->value = 0;"
                    "current->prev = a;"
                "}"
                "current = current->prev;");
                break;
            case '>':
                print_to_out(
                "if(current->next == NULL){"
                    "DoubleLinkedList *a = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));"
                    "a->next = NULL;"
                    "a->prev = current;"
                    "a->value = 0;"
                    "current->next = a;"
                "}"
                "current = current->next;");
                break;
            case '.':
                print_to_out("printf(\"%c\", current->value);");
                break;
            case ',':
                print_to_out("current->value = getchar();");
                break;
            default:
                break;
        }
    }
    print_to_out("}");

    fclose(fp);
    fclose(out);
    return 0;
}
