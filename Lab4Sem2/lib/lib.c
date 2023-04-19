//
// Created by stasc on 19.04.2023.
//
#include "../include/include.h"

int max = 0;

Node *createNode(const char *question, int index) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->question = strdup(question);
    node->yes = NULL;
    node->no = NULL;
    node->index = index;
    return node;
}


void readTreeFromFileHelper(Node* current, FILE* file, int count) {
    max++;
    char* line = (char*)malloc(SIZE*sizeof(char));
    fseek(file, 0, SEEK_SET);
    while(count--) {
        fgets(line, sizeof(line), file);
        size_t len = strcspn(line, "\n");
        if (len > 0) line[len] = '\0';
    }

    int index = atoi(strtok_r(line, ":", &line));
    const char *question = strtok_r(NULL, ":", &line);
    int yesIndex = atoi(strtok_r(NULL, ":", &line));
    int noIndex = atoi(strtok_r(NULL, ":", &line));
    current->question = strdup(question);
    current->index = index;
    int i;
    if (yesIndex > 0) {
        Node* yesNode = createNode(NULL, 0);
        current->yes = yesNode;
        fseek(file, 0, SEEK_SET);
        for (i = 1;;i++) {
            fgets(line, sizeof(line), file);
            const char *p = strtok_r(line, ":", &line);
            if (yesIndex == atoi(p))
                break;
        }
        readTreeFromFileHelper(yesNode, file, i);
    }

    if (noIndex > 0) {
        Node* noNode = createNode(NULL, 0);
        current->no = noNode;
        fseek(file, 0, SEEK_SET);
        for (i = 1;;i++) {
            fgets(line, sizeof(line), file);
            const char* p = strtok_r(line, ":", &line);
            if(noIndex == atoi(p))
                break;
        }
        readTreeFromFileHelper(noNode, file, i);
    }
}



Node* readTreeFromFile(FILE* file) {
    if (file == NULL) {
        return NULL;
    }

    Node* root = createNode(NULL, 1);

    readTreeFromFileHelper(root, file, 1);

    fclose(file);
    return root;
}


void destroyNode(Node* node) {
    if (node == NULL) return;
    destroyNode(node->yes);
    destroyNode(node->no);
    free(node->question);
    free(node);
}

char* inputStr() {
    char* str = NULL;
    int pos = 0;
    int len = 0;
    int c = getchar();

    while (c != '\n') {
        if (pos == len) {
            len += 10;
            str = (char*) realloc(str, len * sizeof(char));
        }

        str[pos] = (char)c;
        pos++;
        c = getchar();
    }

    if (pos == len) {
        len++;
        str = (char*) realloc(str, len * sizeof(char));
    }

    str[pos] = '\0';
    return str;
}


void guessObject(Node* node, FILE* logFile, char* username) {
    char answer[MAX_LINE_LENGTH];
    time_t t = time(NULL);
    struct tm tm;
    localtime_r(&t, &tm);
    char time_string[MAX_LINE_LENGTH];
    strftime(time_string, MAX_LINE_LENGTH, "[%Y-%m-%d %H:%M:%S]", &tm);
    fprintf(logFile, "%s User %s: Question: %s\n",
            time_string, username, node->question);
    printf("%s\n", node->question);
    fgets(answer, MAX_LINE_LENGTH, stdin);
    answer[strlen(answer) - 1] = '\0';

    strftime(time_string, MAX_LINE_LENGTH, "[%Y-%m-%d %H:%M:%S]", &tm);
    fprintf(logFile, "%s User %s: Answer: %s\n",
            time_string, username, answer);
    if (strcmp(answer, "yes") == 0) {
        if (node->yes == NULL) {
            printf("I guessed your object!\n");
        } else {
            guessObject(node->yes, logFile, username);
        }
    } else if (strcmp(answer, "no") == 0) {
        if (node->no == NULL) {
            printf("I give up. What was your object?\n");
            char object[MAX_LINE_LENGTH];
            fgets(object, MAX_LINE_LENGTH, stdin);
            object[strlen(object) - 1] = '\0';
            printf("What question would distinguish %s from %s?\n", object, node->question);
            char question[MAX_LINE_LENGTH];
            fgets(question, MAX_LINE_LENGTH, stdin);
            question[strlen(question) - 1] = '\0';
            node->no = createNode(node->question, ++max);
            node->yes = createNode(object, ++max);
            free(node->question);
            node->question = strdup(question);
            strftime(time_string, MAX_LINE_LENGTH, "[%Y-%m-%d %H:%M:%S]", &tm);
            fprintf(logFile, "%s User %s: New question: %s, New object: %s\n",
                    time_string, username, question, object);
        } else {
            guessObject(node->no, logFile, username);
        }
    } else {
        printf("Please answer 'yes' or 'no'.\n");
        guessObject(node, logFile, username);
    }
}





void saveTree(Node* node, FILE* file)
{
    if(node -> yes == NULL || node -> no == NULL)
    {
        fprintf(file, "%d:%s\n", node->index, node->question);
        printf("%d:%s\n", node->index, node->question);
        return;
    }
    else
    {
        fprintf(file, "%d:%s:%d:%d\n", node->index, node->question, node->yes->index, node->no->index);
        printf("%d:%s:%d:%d\n", node->index, node->question, node->yes->index, node->no->index);
    }
    saveTree(node->yes, file);
    saveTree(node->no, file);

}

Node *findNode(Node *node, int node_num) {
    if (node == NULL) {
        return NULL;
    }
    if (node_num == 1) {
        return node;
    }
    Node *result = findNode(node->yes, node_num - 1);
    if (result == NULL) {
        result = findNode(node->no, node_num - 1);
    }
    return result;
}

void printTree(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%s\n", root->question);
    printf("Yes:\n");
    printTree(root->yes);
    printf("No:\n");
    printTree(root->no);
}
