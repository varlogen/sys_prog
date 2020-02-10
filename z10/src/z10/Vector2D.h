class Vector2D
{
public:
    Vector2D(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    int x;
    int y;

    friend bool operator==(const Vector2D &left, const Vector2D &right)
    {
        return ((left.x == right.x) && (left.y == right.y));
    }
};

bool rotate(Vector2D &vector, int angle)
{
    if (angle % 90 != 0)
    {
        return false;
    }

    angle %= 360;

    if (angle == 90 || angle == -270)
    {
        vector.y *= -1;
    }
    else if (angle == 180)
    {
        vector.x *= -1;
        vector.y *= -1;
    }
    else if (angle == 270 || angle == -90)
    {
        vector.x *= -1;
    }

    return true;
}