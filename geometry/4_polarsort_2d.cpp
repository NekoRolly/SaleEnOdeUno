// Requiere: point 2d; precondicion: o no pertenece a p
// O(n log n) - Ordena CCW por angulo desde el eje X positivo
void polarSort(vector<point> &p, point o = {0, 0}) {
    auto half = [](point a) { return a.y > 0 || (a.y == 0 && a.x >= 0) ? 0 : 1; };
    sort(all(p), [&](point a, point b) {
        a = a - o, b = b - o;
        if (half(a) != half(b)) return half(a) < half(b);
        ll c = cross(a, b);
        if (c != 0) return c > 0;
        return dot(a, a) < dot(b, b);
    });
}
