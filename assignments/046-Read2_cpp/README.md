1. Create a file "answer.txt".
2. Execute the code under the instructions by hand as demonstrated with the memory/trace diagrams in class. Write the output in your "answer.txt" file
3. Take a picture of your diagram.
4. Copy the source code into a file 'read2_string.cpp' and change it to work with the following data:
   ```
   vector<string> data = {"Duke", "University", "FinTech", "510"};
   ```
   You will need to change the type in several locations to make the code work.

5. After compiling and running read2_string.cpp, add its output to your answer.txt file.
6. Submit answer.txt, read2_string.cpp, and your diagram (this can be png/jpg/pdf) for grading in gradescope.
   
   Please note the correct file names to submit.


**Notes:**

- In C++, the size of vectors are unsigned integers - the size cannot be negative. So, rather than using int as the type to store the size of the vector and for index variables, we need to use a special alias `std::size_t` for these variable types.  In the code below, we do not need to use the `std::` prefix as that namespace has been import into the scope of the source file with using namespace std;.
- This code file uses two styles of for loops:  a  "for each" loop and a traditional C/C++ "for" loop.  The "for each" loop in someFunction equates to the "for" loop used with Python.  Also, notice that the keyword auto defines the variable type. The C++ compiler can appropriately infer that since we are tracking a vector of integers(ints), the type should be int.
- `endl` is a special constant used to represent the newline character, which can be platform-dependent. This constant also flushes the stream - forces all output to be written.

```c++
#include <iostream>
#include <vector>
using namespace std;

void someFunction(vector<int> vec) {
  for (auto value : vec) {
    cout << value << " ";
  }
  cout << endl;
}

vector<int> anotherFunction(vector<int> vec) {
  for (size_t step = 0; step < vec.size() - 1; step++) {
    size_t min_idx = step;
    for (size_t i = step + 1; i < vec.size(); i++) {

      if (vec[i] > vec[min_idx])
        min_idx = i;
    }

    int temp = vec[min_idx];
    vec[min_idx] = vec[step];
    vec[step] = temp;
  }
  return vec;
}

int main(void) {
  vector<int> data = {5, 6, 4, 7, 3};
  vector<int> revised_data = anotherFunction(data);
  someFunction(revised_data);
}
```