#include "config.cpp"

/* There are several variable types available with C++, here are some basic ones, you
must declare the variable type before defining it initially. 
*/

//An integer value, decimal illegal
int integer = 2;

//A float can be represented as a decimal, unlike int
float floatValue = 41.2142;

//A more precise version of float which use 64-bit instead of 32
double doubleValue = 2.1242401024;

//A boolean variable accepts only true or false
bool boolean = true;

//Standard function type, return no value
void doSomething() {
  integer = 2; //We're reusing a variable so no type declaration needed
  //Function cannot return any value
}

//This function, when called, will return floatValue, yes, variable types are function types
float returnFloat() {
  floatValue = floatValue;
  return floatValue; 
}

//This is what functions that return variables are used for: to define a variable
float floatValue2 = returnFloat();

//A more useful application of the above, by using parameters to ask for user input
float returnFloat2(float value) {
  floatValue = 5 * value; //whatever the input is, the function will return 5 times that
  return floatValue;
}

float floatValue3 = returnFloat2(20);