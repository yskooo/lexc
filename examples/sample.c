// Sample C-like code for lexical analysis
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

void main() {
    int result = 0;
    float pi = 3.14159;
    
    result = factorial(5);
    
    if (result > 100) {
        result = 100;
    } else {
        result = result + 1;
    }
    
    while (result > 0) {
        result = result - 1;
    }
}
