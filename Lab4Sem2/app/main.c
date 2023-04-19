#include "../include/include.h"

/*1:It's alive?:2:3
2:does it have 4 legs?:4:5
3:is it edible?:6:7
4:is it a mammal?:8:9
5:Got wings?:10:11
6:is it a vegetable?:12:13
7:Is it man made?:14:15
8:Pet?:16:17
9:Have a shell?:18:19
10:Predator?:20:21
11:Lives in water?:22:23
12:Growing in Belarus?:24:25
13:is it a fruit?:26:27
14:is it a jewelry?:28:29
15:is this a natural phenomenon?:30:31
16:Cat?
17:Fox?
18:Turtle?
19:Crocodile?
20:Eagle?
21:hummingbird?
22:Fish?
23:Snake?
24:Potatoes?
25:Jerusalem artichoke?
26:Apple?
27:Nut?
28:Necklace?
29:Chair?
30:Rain?
31:Stone?*/

int main() {
    Node *root = NULL;
    FILE* log = fopen("log.txt", "a");
    printf("Enter you're name::");
    char* username = inputStr();
    printf("\n");

    while (1) {
        printf("Welcome to Akinator!\n");
        printf("Do you want to (g)uess an object, (s)ave the current tree, (l)oad a saved tree, or (q)uit?\n");

        char answer[MAX_LINE_LENGTH];
        fgets(answer, MAX_LINE_LENGTH, stdin);
        if (strlen(answer) > 0 && answer[strlen(answer) - 1] == '\n') {
        answer[strlen(answer) - 1] = '\0';
        }

        if (strcmp(answer, "g") == 0) {
            guessObject(root,log,username);
        } else if (strcmp(answer, "s") == 0) {
            printf("Enter filename to save to: ");
            char filename[MAX_LINE_LENGTH];
            fgets(filename, MAX_LINE_LENGTH, stdin);
            filename[strlen(filename) - 1] = '\0';

            FILE *file = fopen(filename, "w");
            saveTree(root, file);
            fclose(file);
            printf("Tree saved to %s.\n", filename);
        } else if (strcmp(answer, "l") == 0) {
            printf("Enter filename to load from: ");
            char filename[MAX_LINE_LENGTH];
            fgets(filename, MAX_LINE_LENGTH, stdin);
            filename[strlen(filename) - 1] = '\0';

            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                printf("Could not open file %s.\n", filename);

            } else {
                destroyNode(root);
                root = readTreeFromFile(file);
                fclose(file);
                printf("Tree loaded from %s.\n", filename);
            }
        }
        else if (strcmp(answer, "q") == 0) {
            destroyNode(root);
            break;
        } else
            printf("Please enter 'g', 's', 'l', or 'q'.\n");
    }
    return 0;
}
