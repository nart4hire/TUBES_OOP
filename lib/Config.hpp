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
  private:
    std::string itemsFile;
    std::string recipesDir;
    std::vector<Recipe *> recipesList;
    std::map<std::string, Recipe *> recipesMap;

    void loadItems();
    void loadRecipe(std::string name);

  public:
    Config(std::string itemsFile, std::string recipesDir);
    ~Config();
    const std::vector<Recipe *> &getRecipes() const;
    const Recipe *getRecipe(const std::string &name) const;
  };
}

#endif
