#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>
#include "Recipe.hpp"

using std::string;

namespace mobicraft
{
  class Config
  {
    std::vector<string> items;
    std::map<string, Recipe> recipes;

    void loadItems(std::istream &in);
    void loadRecipe(std::istream &in);

  public:
    Config(string itemsFile, string recipesDir);
    ~Config();
  };
}

#endif
