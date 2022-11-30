#ifndef TUPLE_H_
#define TUPLE_H_

class Tuple
{
    public:
        Tuple() = default;
        Tuple(float _x, float _y);
        float getX() const;
        float getY() const;
    private:
        float m_x=0.0f;
        float m_y=0.0f;

};

#endif