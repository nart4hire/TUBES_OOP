#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>

#include "Recipe.hpp"

namespace mobicraft
{
  class Config
  {
    std::vector<std::string> items;
    std::map<std::string, Recipe> recipes;

    void loadItems(std::istream &in);
    void loadRecipe(std::istream &in);

  public:
    Config(std::string itemsFile, std::string recipesDir);
    ~Config();
  };
}

#endif
