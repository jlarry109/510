# Read - Template

1. Create a file "answer.txt".
2. Execute the code under the instructions by hand as demonstrated with the memory/trace diagrams in class.
3. Write the output in your "answer.txt" file.
4. Take a picture of your diagram.
5. Compile and execute code.cpp. Compare the output to that expected.  Make any necessary corrections. 
6. Submit your answer.txt file and your diagram (this can be png/jpg/pdf) for grading.

```c++
#include <cstdlib>
#include <iostream>
template<typename T> class MyClass;
template<typename T> std::ostream & operator<<(std::ostream & s, const MyClass<T> & x);

template<typename T>
class MyClass {
private:
  T data;
public:
  void setData(const T& d) {
    data = d;
  }
  template<typename A> T f(const A& x) {
    return data + x;
  }
  template<typename X> friend std::ostream & operator<<(std::ostream &s, const MyClass<X> & x);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const MyClass<T> & x) {
  return s << x.data;
}


int main(void) {
  MyClass<std::string> s;
  std::cout << s << std::endl;

  MyClass<int> num;
  num.setData(42);
  std::cout << num << std::endl;

  s.setData("Hello");

  std::cout <<  s.f<std::string>(" World") << std::endl;

  std::cout << num.f<double>(3.14) << std::endl;

  MyClass<MyClass<int> > mc;
  mc.setData(num);
  
  std::cout << mc << std::endl;

  return EXIT_SUCCESS;
}
```