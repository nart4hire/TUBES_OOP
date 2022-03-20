#include "lib/Config.hpp"

using namespace mobicraft;

int main(void)
{
  Config conf = Config("./config/item.txt", "./config/recipe");
  return 0;
}
