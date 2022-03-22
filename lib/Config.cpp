#include <iostream>
#include <fstream>
#include <string>

#include "Config.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include "Grid.hpp"

namespace mobicraft
{
  Config::Config(std::string itemsFile, std::string recipesDir)
    : itemsFile(itemsFile), recipesDir(recipesDir)
  {
    loadItems();
    for (auto const &i : recipesList)
    {
      loadRecipe(i->name);
    }
  }

  Config::~Config()
  {
    for (auto const& i : recipesList)
    {
      delete i;
    }
  }

  void Config::loadItems()
  {
    int id;
    std::string name, type, tool;

    std::ifstream fin(itemsFile);
    while (fin >> id)
    {
      fin >> name;
      fin >> type;
      fin >> tool;

      Recipe *recipe;

      if (tool == "TOOL")
      {
        recipe = new ToolRecipe(id, name, type);
      } else {
        recipe = new NonToolRecipe(id, name, type);
      }

      recipesList.push_back(recipe);
      recipesMap[name] = recipe;
    }

    fin.close();
  }

  void Config::loadRecipe(std::string name)
  {
    std::ifstream fin(recipesDir + "/" + name + ".txt");

    if (fin.good())
    {
      int row, col, qty;

      fin >> row;
      fin >> col;

      Grid<std::string> recipe(row, col);

      for (int i = 0; i < row; ++i)
      {
        for (int j = 0; j < col; ++j)
        {
          fin >> recipe.at(i, j);
        }
      }

      fin >> name;
      fin >> qty;

      recipesMap[name]->set(recipe, qty);
    }

    fin.close();
  }
}
