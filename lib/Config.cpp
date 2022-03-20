#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using std::string;

#include "Config.hpp"

namespace mobicraft
{
  Config::Config(string itemsFile, string recipesDir)
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
    string name, type, tool;

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
    string name;

    in >> row;
    in >> col;

    std::vector<string> recipe;

    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        in >> name;
        recipe.push_back(name);
      }
    }

    in >> name;
    in >> qty;

    recipes.insert(std::pair<string, Recipe>(name, Recipe(name, row, col, recipe, qty)));
  }
}
