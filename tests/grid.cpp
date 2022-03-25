#include <iostream>
#include <string>
#include "../lib/Grid.hpp"

using namespace mobicraft;

int main(void)
{
  std::cout << "Create 5x5 grid of int.\n";
  Grid<int> grint(5, 5);

  std::cout << "\nPrint.\n";
  grint.print();

  std::cout << "\nCreate 5x5 grid of float.\n";
  Grid<float> grifl(5, 5);

  std::cout << "\nPrint.\n";
  grifl.print();

  std::cout << "\nCompare.\n"
            << (grint == grifl) << "\n";

  std::cout << "\nPopulate with 1-25.\n";
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      grint.at(i, j) = i * 5 + j + 1;

  std::cout << "\nPrint.\n";
  grint.print();

  std::cout << "\nFlip.\n";
  grint = grint.flipVertically();
  grint.print();

  std::cout << "\nFill zeros on sides.\n";
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (j == 0 || j == 4)
        grint.at(i, j) = 0;

  std::cout << "\nPrint.\n";
  grint.print();

  std::cout << "\nReduce.\n";
  grint = grint.reduce(0);
  grint.print();

  std::cout << "Create a 5x3 grid of int with similar values.\n";
  Grid<int> grible(5,3);
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 3; ++j)
        grible.at(i, j) = i * 5 + j + 2;

  std::cout << "\nPrint.\n";
  grible.print();

  std::cout << "\nCompare.\n"
            << (grint == grible) << "\n";

  std::cout << "\nFlip and compare.\n"
            << (grint.flipVertically() == grible) << "\n";
  
  return 0;
}
