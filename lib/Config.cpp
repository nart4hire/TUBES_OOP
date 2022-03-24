#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "Config.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include "Grid.hpp"
#include "Exception.hpp"

namespace mobicraft
{
  Config::Config(std::string itemsFile, std::string recipesDir)
      : itemsFile(itemsFile), recipesDir(recipesDir)
  {
  }

  Config::~Config()
  {
    for (auto const &i : recipesList)
    {
      delete i;
    }
  }

  void Config::load()
  {
    loadItems();
    for (auto const &i : recipesList)
    {
      loadRecipe(i->name);
    }
  }

  void Config::loadItems()
  {
    int id;
    std::string name, type, tool;

    std::ifstream fin(itemsFile);
    if (!fin.is_open())
    {
      throw ConfigFileException();
    }

    while (fin >> id)
    {
      fin >> name;
      fin >> type;
      fin >> tool;

      Recipe *recipe;

      if (tool == "TOOL")
      {
        recipe = new ToolRecipe(id, name, type);
      }
      else
      {
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

  const std::vector<Recipe *> &Config::getRecipes() const
  {
    return recipesList;
  }

  const Recipe *Config::getRecipe(const std::string &name) const
  {
    try {
      return recipesMap.at(name);
    } catch (const std::out_of_range &err) {
      throw NotExistsException();
    }
  }

  void Config::printStatus() const
  {
    int craftables = 0;
    for (const auto &i : recipesList)
    {
      if (i->isCraftable())
        ++craftables;
    }

    std::cout << "Successfully loaded " << recipesList.size() << " items and "
              << craftables << " recipes.\n";
  }
}
