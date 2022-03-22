#ifndef RECIPE_H
#define RECIPE_H

#include <string>

#include "Grid.hpp"
#include "Item.hpp"

namespace mobicraft
{
  class Recipe
  {
  protected:
    Grid<std::string> recipe;

  public:
    const int id;
    const std::string name;
    const std::string type;

    Recipe(int id, std::string name, std::string type);
    bool operator==(const Grid<std::string> &table) const;
    bool operator!=(const Grid<std::string> &table) const;

    virtual void set(const Grid<std::string> &recipe, int quantity) = 0;
    virtual Item *create() = 0;
    virtual bool isTool() = 0;
  };

  class ToolRecipe : public Recipe
  {
  private:
    const int durability = 10;

  public:
    ToolRecipe(int id, std::string name, std::string type);
    void set(const Grid<std::string> &recipe, int quantity);
    Item *create();
    bool isTool();
  };

  class NonToolRecipe : public Recipe
  {
  private:
    int quantity = 1;

  public:
    NonToolRecipe(int id, std::string name, std::string type);
    void set(const Grid<std::string> &recipe, int quantity);
    Item *create();
    bool isTool();
  };
}

#endif
