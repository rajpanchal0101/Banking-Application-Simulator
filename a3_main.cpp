/**
1) Module Name: a3_main.cpp
2) Author: Raj Panchal (rjp659@uregina.ca)
3) Date of creation: 2023-10-21
4) Purpose:This is the file which consists of the main function from where the compilation of the program commences.
*/
#include "a3_class_methods.cpp" 

/**
1) Purpose:This is the main function from where the program's compilation begins and various user defined functions are invoked here based on the requirement.
2) Parameters: None
3) Return type: int
4) Side Effect: None 
*/
int main() 
{
	//! Creating a new Application instance.
	Application* app = new Application();

	//! Run the application.
	app->action();
}