#ifndef GRID_HPP
#define GRID_HPP

#include "PlatformHandler.hpp"
#include "Block.hpp"
#include <thread>

namespace Maze::Platform
{
    using Cell = std::shared_ptr<Block>;

    class Grid : public IPlatform
    {
    public:
        Grid();
        Grid(const Grid &grid) = delete;
        Grid(Grid &&grid) = delete;
        Grid &operator=(const Grid &grid) = delete;
        Grid &operator=(Grid &&grid) = delete;

        ~Grid();

        void Init(const int32_t &, const int32_t &) override;

        void Solve(std::reference_wrapper<sf::RenderWindow>) override;

    private:
        int m_rows, m_columns;
        std::vector<Cell> m_cells;
        Cell m_current;
        std::stack<Cell> m_trace;
        bool mazeCreated{false};
        std::vector<Cell> m_longestPath;
        std::vector<Cell> m_pathTrace;
        bool m_MazeSolved{true};

        int32_t Index(int32_t, int32_t);
        Cell CheckNeighbors(Position);
        std::vector<Cell> FetchNeighbors(Cell);

        void RemoveWalls(Cell a, Cell b);

        void Move(Cell);
    };
}

#endif