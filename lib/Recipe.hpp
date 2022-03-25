#ifndef RECIPE_H
#define RECIPE_H

#include <string>

#include "Grid.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"

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
    const bool isTool;

    Recipe(int id, std::string name, std::string type, bool isTool);
    bool isCraftable() const;
    bool operator==(const Grid<Item *> &table) const;
    bool operator!=(const Grid<Item *> &table) const;

    virtual int getAmt() = 0;
    virtual void set(const Grid<std::string> &recipe, int quantity) = 0;
    virtual Item *create() = 0;
  };

  class ToolRecipe : public Recipe
  {
  private:
    const int durability = Tool::MaxDurability;

  public:
    ToolRecipe(int id, std::string name, std::string type);
    void set(const Grid<std::string> &recipe, int quantity);
    Item *create();
    int getAmt();
  };

  class NonToolRecipe : public Recipe
  {
  private:
    int quantity = 1;

  public:
    NonToolRecipe(int id, std::string name, std::string type);

    void set(const Grid<std::string> &recipe, int quantity);
    Item *create();
    int getAmt();
  };
}

#endif
