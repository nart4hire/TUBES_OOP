#ifndef GRID_H
#define GRID_H

#include <vector>
#include <utility>
#include <iostream>

namespace mobicraft
{
  template <class T>
  class Grid
  {
    int row, col;
    std::vector<T> table;

  public:
    Grid(int row, int col) : row(row), col(col), table(row * col)
    {
    }

    Grid() : Grid(0, 0)
    {
    }

    int rows() const
    {
      return row;
    }

    int cols() const
    {
      return col;
    }

    T &at(int i, int j)
    {
      return table.at(i * col + j);
    }

    const T &at(int i, int j) const
    {
      return table.at(i * col + j);
    }

    bool isNull() const
    {
      return (row == 0) && (col == 0);
    }

    template <class U>
    bool operator==(const Grid<U> &o) const
    {
      if (row != o.rows() || col != o.cols())
        return false;

      for (int i = 0; i < row; ++i)
      {
        for (int j = 0; j < col; ++j)
        {
          if (at(i, j) != o.at(i, j))
            return false;
        }
      }

      return true;
    }

    template <class U>
    bool operator!=(const Grid<U> &o) const
    {
      return !(*this == o);
    }

    Grid<T> flipVertically() const
    {
      Grid<T> flip(*this);

      for (int i = 0; i < row; ++i)
      {
        for (int j = 0; j < col / 2; ++j)
        {
          std::swap(flip.at(i, j), flip.at(i, col - j - 1));
        }
      }

      return flip;
    }

    Grid<T> reduce(const T &null) const
    {
      int imin = row - 1, jmin = col - 1;
      int imax = 0, jmax = 0;

      for (int i = 0; i < row; ++i)
      {
        for (int j = 0; j < col; ++j)
        {
          if (at(i, j) != null)
          {
            if (i < imin)
              imin = i;
            if (i > imax)
              imax = i;

            if (j < jmin)
              jmin = j;
            if (j > jmax)
              jmax = j;
          }
        }
      }

      return subGrid(imin, imax, jmin, jmax);
    }

    Grid<T> subGrid(int istart, int iend, int jstart, int jend) const
    {
      Grid<T> sub(iend - istart + 1, jend - jstart + 1);

      for (int i = 0; i < sub.rows(); ++i)
      {
        for (int j = 0; j < sub.cols(); ++j)
        {
          sub.at(i, j) = at(i + istart, j + jstart);
        }
      }

      return sub;
    }

    void print()
    {
      for (int i = 0; i < row; ++i)
      {
        for (int j = 0; j < col; ++j)
        {
          std::cout << at(i, j) << ' ';
        }
        std::cout << '\n';
      }
      std::cout << '\n';
    }
  };
}

#endif
