#include <vector>
#include <string>
#include <iostream>
using namespace std;

std::string reverseHelper(const std::string & s, std::string & ans, size_t index) {
  if (index == s.length()) {
    return ans;
  }
  ans[index] = s[s.length() - index - 1];
  return reverseHelper(s, ans, ++index);
}

std::string  reverse(string &str) {
  //WRITE ME
  std::string ans(str.length(), '\0');
  return reverseHelper(str, ans, 0);
}

int main(void) {
    vector<string> strings;

    strings.push_back("");
    strings.push_back("123");
    strings.push_back("abcd");
    strings.push_back("Captain's log, Stardate 42523.7");
    strings.push_back("Hello, my name is Inigo Montoya.");
    strings.push_back("You can be my wingman anyday!");
    strings.push_back("Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!");
    strings.push_back("amanap lanac a nalp a nam a");


    for (string test: strings) {
        test = reverse(test);
        cout << test << endl;
    }

    return EXIT_SUCCESS;
}