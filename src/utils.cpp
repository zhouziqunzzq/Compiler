#include "utils.h"

using namespace std;

int calcConstResult(Operation op, int a, int b) {
    int x = a;
    int y = b;
    switch (op) {
        case ADD:
            return x + y;
        case MINUS:
            return x - y;
        case MUL:
            return x * y;
        case DIV:
            return x / y;
        default:
            return 0;
    }
}

float calcConstResult(Operation op, float a, int b) {
    float x = a;
    float y = float(b);
    switch (op) {
        case ADD:
            return x + y;
        case MINUS:
            return x - y;
        case MUL:
            return x * y;
        case DIV:
            return x / y;
        default:
            return 0;
    }
}

float calcConstResult(Operation op, int a, float b) {
    float x = float(a);
    float y = b;
    switch (op) {
        case ADD:
            return x + y;
        case MINUS:
            return x - y;
        case MUL:
            return x * y;
        case DIV:
            return x / y;
        default:
            return 0;
    }
}

float calcConstResult(Operation op, float a, float b) {
    float x = a;
    float y = b;
    switch (op) {
        case ADD:
            return x + y;
        case MINUS:
            return x - y;
        case MUL:
            return x * y;
        case DIV:
            return x / y;
        default:
            return 0;
    }
}
