// Requiere: point 2d
// O(1) - Verifica si p pertenece al segmento cerrado ab
bool onSegment(const point &a, const point &b, const point &p) {
    if (cross(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y &&
           p.y <= max(a.y, b.y);
}
// O(1) - Interseccion de segmentos, incluidos extremos y solapes
bool intersect(const point &a, const point &b, const point &c, const point &d) {
    ll x = cross(a, b, c), y = cross(a, b, d);
    ll z = cross(c, d, a), w = cross(c, d, b);
    if (((x > 0 && y < 0) || (x < 0 && y > 0)) && ((z > 0 && w < 0) || (z < 0 && w > 0)))
        return true;
    if (x == 0 && onSegment(a, b, c)) return true;
    if (y == 0 && onSegment(a, b, d)) return true;
    if (z == 0 && onSegment(c, d, a)) return true;
    if (w == 0 && onSegment(c, d, b)) return true;
    return false;
}
// O(1) - 0 fuera, 1 borde, 2 dentro del triangulo abc
int pointInTriangle(point a, point b, point c, point p) {
    if (cross(a, b, c) == 0) {
        return (onSegment(a, b, p) || onSegment(b, c, p) || onSegment(c, a, p)) ? 1 : 0;
    }
    ll x = cross(a, b, p), y = cross(b, c, p);
    ll z = cross(c, a, p);
    bool neg = x < 0 || y < 0 || z < 0;
    bool pos = x > 0 || y > 0 || z > 0;
    if (neg && pos) return 0;
    if (x == 0 || y == 0 || z == 0) return 1;
    return 2;
}
