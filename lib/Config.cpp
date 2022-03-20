#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Config.hpp"
#include "Grid.hpp"

namespace mobicraft
{
  Config::Config(std::string itemsFile, std::string recipesDir)
  {
    std::ifstream fin;

    fin.open(itemsFile);
    loadItems(fin);
    fin.close();

    for (auto i = items.begin(); i != items.end(); ++i)
    {
      fin.open(recipesDir + "/" + *i + ".txt");

      if (fin.good())
      {
        loadRecipe(fin);
      }
      fin.close();
    }
  }

  Config::~Config()
  {
  }

  void Config::loadItems(std::istream &in)
  {
    int id;
    std::string name, type, tool;

    while (in >> id)
    {
      in >> name;
      in >> type;
      in >> tool;

      items.push_back(name);
    }
  }

  void Config::loadRecipe(std::istream &in)
  {
    int row, col, qty;
    std::string name;

    in >> row;
    in >> col;

    Grid<std::string> recipe(row, col);

    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        in >> recipe.at(i, j);
      }
    }

    in >> name;
    in >> qty;

    recipes.insert(std::pair<std::string, Recipe>(name, Recipe(name, recipe, qty)));
  }
}
