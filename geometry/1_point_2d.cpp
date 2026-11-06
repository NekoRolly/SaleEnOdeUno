// Base 2D - Coordenadas enteras. Los productos deben caber en ll.
struct point {
    ll x, y;
    point() : x(0), y(0) {}
    point(ll _x, ll _y) : x(_x), y(_y) {}
    point operator+(const point &p) const {
        return {x + p.x, y + p.y};
    }
    point operator-(const point &p) const {
        return {x - p.x, y - p.y};
    }
    bool operator==(const point &p) const {
        return x == p.x && y == p.y;
    }
    bool operator<(const point &p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
};
// O(1) - Producto punto de dos vectores
ll dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}
// O(1) - Producto cruzado de dos vectores
ll cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}
// O(1) - Orientacion de a, b, c; positiva si giro CCW
ll cross(const point &a, const point &b, const point &c) {
    return cross(b - a, c - a);
}
// O(1) - Distancia euclidiana al cuadrado
ll dist2(const point &a, const point &b) {
    return dot(a - b, a - b);
}
