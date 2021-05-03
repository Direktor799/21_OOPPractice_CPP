#include <iostream>

class Point
{
private:
    double m_pos_x, m_pos_y;

public:
    Point(double x = 0, double y = 0);
    const double pos_x() const;
    const double pos_y() const;
    const Point &operator++();
    const Point &operator--();
    const Point operator++(int);
    const Point operator--(int);
};

Point::Point(double x, double y)
{
    m_pos_x = x;
    m_pos_y = y;
}

const double Point::pos_x() const
{
    return m_pos_x;
}

const double Point::pos_y() const
{
    return m_pos_y;
}

const Point &Point::operator++()
{
    m_pos_x += 1;
    m_pos_y += 1;
    return *this;
}

const Point &Point::operator--()
{
    m_pos_x -= 1;
    m_pos_y -= 1;
    return *this;
}

const Point Point::operator++(int)
{
    Point tmp = *this;
    ++(*this);
    return tmp;
}

const Point Point::operator--(int)
{
    Point tmp = *this;
    --(*this);
    return tmp;
}

int main()
{
    Point p(6.6, 5.5);
    std::cout << (++p).pos_x() << ' ' << p.pos_y() << std::endl;
    std::cout << (--p).pos_x() << ' ' << p.pos_y() << std::endl;
    std::cout << (p++).pos_x() << ' ' << p.pos_y() << std::endl;
    std::cout << (p--).pos_x() << ' ' << p.pos_y() << std::endl;
}