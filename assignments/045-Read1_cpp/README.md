1. Create a file "answer.txt".
2. Execute the code under the instructions by hand as demonstrated with the memory/trace diagrams in class.
3. Write the output in your "answer.txt" file.
4. Take a picture of your diagram.
5. Submit both your answer.txt file and your diagram (this can be png/jpg/pdf) for grading.

```c++
int main(void) {
  int a = 3;
  int b = 9;
  while (a <= b) {
     if (a % 2 == 1) {
        std::cout << "a is " << a << "\n";
     }
     else {
       std::cout << "b is " << b << "\n";
       for (int i = 0; i < b - a ; i++) {
          std::cout << "a * i + b = " << a * i + b << "\n";
       }
     }
     a++;
     b--;
  }
  return 0;
}
```



