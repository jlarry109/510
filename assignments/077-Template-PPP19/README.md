# PPP Chapter 19 Vector / Template
In this assignment, you modify your vector1 class to utilize C++'s template 
functionality such that it can store a type selected by the caller.

Steps:
1. Beginning with your code from ppp_ch19_vector, modify, and test, the 
   template feature described in Section 19.3 

   Roughly, you'll need to add `template <typename T>` just before the start of the
   `vector1` class.  Then, replace `double` with `T` throughout the class.

2. Implement range-checking, and throw an exception if an index is out of range. 
   This is described in Section 19.4.  Use the `Range_error` struct/class defined in 19.4.2 as the exception to throw.
   
   ```
   struct Range_error : out_of_range {   // enhanced vector range error reporting
		int index;
		Range_error(size_t i) :out_of_range{"Range error"}, index(i) { }
	};
   ```
   Then to throw that exception - 
   ```
   throw Range_error(bad_index_value);
   ```

3. Submit `vector1.hpp` to the Gradescope assignment.
