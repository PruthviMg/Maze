#include "Grid.hpp"

namespace Maze::Platform
{
    Grid::Grid()
    {
        Log(Log::DEBUG, __func__);
    }

    Grid::~Grid()
    {
        Log(Log::DEBUG, __func__);
    }

    void Grid::Init(const int32_t &width, const int32_t &height)
    {
        Log(Log::DEBUG, __func__);

        m_rows = height / MIN_HEIGHT;
        m_columns = width / MIN_WIDTH;
        int count = 0;
        for (int i = 0; i < height; i = i + MIN_HEIGHT)
        {
            for (int j = 0; j < width; j = j + MIN_WIDTH)
            {
                m_cells.emplace_back(std::make_shared<Block>(Position(j, i), count++));
            }
        }

        m_current = m_cells[0];
        m_current->m_visited = true;
    }

    int32_t Grid::Index(int32_t i, int32_t j)
    {
        if (i < 0 || j < 0 || (i > (m_columns - 1) * MIN_WIDTH) || (j > ((m_rows - 1) * MIN_HEIGHT)))
            return -1;
        return (i / MIN_WIDTH) + (j / MIN_WIDTH) * m_columns;
    }

    std::vector<Cell> Grid::FetchNeighbors(Cell cell)
    {
        std::vector<Cell> neighbor;
        // Log(Log::DEBUG, cell->WallPresent(Quadrant::Top), cell->WallPresent(Quadrant::Right), cell->WallPresent(Quadrant::Bottom), cell->WallPresent(Quadrant::Left));

        if (!cell->WallPresent(Quadrant::Top))
        {
            auto top = Index(cell->m_position.x, cell->m_position.y - MIN_HEIGHT);
            if (top >= 0 && !m_cells[top]->m_pathTraversered)
            {
                Log(Log::DEBUG, "Top Path available", m_cells[top]->m_id);
                neighbor.push_back(m_cells[top]);
            }
        }

        if (!cell->WallPresent(Quadrant::Right))
        {
            auto right = Index(cell->m_position.x + MIN_WIDTH, cell->m_position.y);
            if (right >= 0 && !m_cells[right]->m_pathTraversered)
            {
                Log(Log::DEBUG, "Right Path available", m_cells[right]->m_id);
                neighbor.push_back(m_cells[right]);
            }
        }

        if (!cell->WallPresent(Quadrant::Bottom))
        {
            auto bottom = Index(cell->m_position.x, cell->m_position.y + MIN_HEIGHT);
            if (bottom >= 0 && !m_cells[bottom]->m_pathTraversered)
            {
                Log(Log::DEBUG, "Bottom Path available", m_cells[bottom]->m_id);
                neighbor.push_back(m_cells[bottom]);
            }
        }

        if (!cell->WallPresent(Quadrant::Left))
        {
            auto left = Index(cell->m_position.x - MIN_WIDTH, cell->m_position.y);
            if (left >= 0 && !m_cells[left]->m_pathTraversered)
            {
                Log(Log::DEBUG, "Left Path available", m_cells[left]->m_id);
                neighbor.push_back(m_cells[left]);
            }
        }

        return neighbor;
    }

    Cell Grid::CheckNeighbors(Position position)
    {
        auto top = Index(position.x, position.y - MIN_HEIGHT);
        auto right = Index(position.x + MIN_WIDTH, position.y);
        auto bottom = Index(position.x, position.y + MIN_HEIGHT);
        auto left = Index(position.x - MIN_WIDTH, position.y);

        std::vector<Cell> neighbors;

        if (top >= 0 && !m_cells[top]->m_visited)
        {
            neighbors.push_back(m_cells[top]);
        }

        if (right >= 0 && !m_cells[right]->m_visited)
        {
            neighbors.push_back(m_cells[right]);
        }

        if (bottom >= 0 && !m_cells[bottom]->m_visited)
        {
            neighbors.push_back(m_cells[bottom]);
        }

        if (left >= 0 && !m_cells[left]->m_visited)
        {
            neighbors.push_back(m_cells[left]);
        }

        if (neighbors.size() > 0)
        {
            auto index = Common::Utility::GetRandom<int>(0, neighbors.size() - 1);
            return neighbors[index];
        }
        return nullptr;
    }

    void Grid::RemoveWalls(Cell a, Cell b)
    {
        auto Xdiff = a->m_position.x - b->m_position.x;
        if (Xdiff == -MIN_WIDTH)
        {
            a->RemoveWall(Quadrant::Right);
            b->RemoveWall(Quadrant::Left);
        }
        if (Xdiff == MIN_WIDTH)
        {
            a->RemoveWall(Quadrant::Left);
            b->RemoveWall(Quadrant::Right);
        }

        auto Ydiff = a->m_position.y - b->m_position.y;
        if (Ydiff == -MIN_HEIGHT)
        {
            a->RemoveWall(Quadrant::Bottom);
            b->RemoveWall(Quadrant::Top);
        }
        if (Ydiff == MIN_HEIGHT)
        {
            a->RemoveWall(Quadrant::Top);
            b->RemoveWall(Quadrant::Bottom);
        }
    }

    void Grid::Move(Cell cell)
    {
        if (cell)
        {
            cell->m_pathTraversered = true;
            auto neighbors = FetchNeighbors(cell);

            for (auto &neighbor : neighbors)
            {
                m_pathTrace.push_back(neighbor);
                Move(neighbor);

                if (m_longestPath.size() < m_pathTrace.size())
                {
                    m_longestPath = m_pathTrace;
                }
                m_pathTrace.pop_back();
            }
        }
    }

    void Grid::Solve(std::reference_wrapper<sf::RenderWindow> window)
    {
        for (auto it : m_cells)
        {
            it->draw(window);
        }

        if (!mazeCreated)
        {
            auto pos = m_current->m_position;
            auto next = CheckNeighbors(pos);

            if (next)
            {
                next->m_visited = true;
                m_trace.push(m_current);
                RemoveWalls(m_current, next);
                m_current = next;
            }
            else
            {
                if (m_trace.size() > 0)
                {
                    auto prev = m_trace.top();
                    m_trace.pop();
                    m_current = prev;
                }
                else
                {
                    Log(Log::DEBUG, "Maze Successfully Created.........................................................");
                    mazeCreated = true;
                }
            }
            m_current->HighLight(window);
        }
        else
        {
            if (m_MazeSolved)
            {
                Log(Log::DEBUG, "Starting to Solve the MAZE");
                for (auto cell : m_cells)
                {
                    m_pathTrace.push_back(cell);
                    cell->m_pathTraversered = true;
                    auto neighbors = FetchNeighbors(cell);
                    for (auto next : neighbors)
                    {
                        m_pathTrace.push_back(next);
                        Move(next);
                    }
                    neighbors.clear();
                }
                m_MazeSolved = false;
                Log(Log::DEBUG, "MAZE Solved successfully");
            }

            // for (auto it : m_longestPath)
            // {
            //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //     it->HighLight(window);
            //     window.get().display();
            // }
            // m_longestPath[0]->HighLight(window);
            // m_longestPath[m_longestPath.size() - 1]->HighLight(window);
        }
    }

}