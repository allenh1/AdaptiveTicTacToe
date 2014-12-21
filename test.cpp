#include <iostream>

int main(int argc, char ** argv)
{
   if (argc == 1)
   {
      std::cout<<"Please enter a character: ";
      char read;
      std::cin>>read;
      std::cout<<"\nInteger value: "<< (int) read<<std::endl;
  }

  return 0;
}
