#include <iostream>
#include <vector>
using namespace std;

void someFunction(vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

vector<int> anotherFunction(vector<int> vec) {
  for (int step = 0; step < vec.size() - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < vec.size(); i++) {

      if (vec[i] > vec[min_idx])
        min_idx = i;
    }

    int temp = vec[min_idx];
    vec[min_idx] = vec[step];
    vec[step] = temp;
  }
  return vec;
}

// Driver code
int main(void) {
  vector<int> data = {5, 6, 4, 7, 3};
  vector<int> revised_data = anotherFunction(data);
  someFunction(revised_data);
}