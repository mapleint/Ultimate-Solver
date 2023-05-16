#include <iostream>
#include <vector>

struct piece {
    char t, r, b, l;

    piece(char in1, char in2, char out1, char out2) {
        t = in1;
        r = in2;
        b = out1;
        l = out2;
    }
    piece flip() {
        piece out = piece(r, t, l, b);
        return out;
    }
};
int sol = 0;
void solve(std::vector<piece> a, std::vector<piece> s) {
    
    if (a.size() < 1)
        sol++;
    std::vector<piece> f;
    std::vector<int> l;
    for (int i = 0; i < a.size(); i++) {
        auto t = a[i];
        bool left = s.size() % 4 == 0 ? true : (-t.l == s.back().r);

        bool up = s.size() < 4 ? true : (-t.t == s[s.size() - 4].b);
        if (left && up) {
            f.push_back(t);
            l.push_back(i);
        }

        t = t.flip();
        left = s.size() % 4 == 0 ? true : (-t.l == s.back().r);

        up = s.size() < 4 ? true : (-t.t == s[s.size() - 4].b);
        if (left && up) {
            f.push_back(t);
            l.push_back(i);
        }
    }

    for (int j = 0; j < f.size(); j++) {
        std::vector<piece> at, as;
        at = a;
        as = s;
        at.erase(at.begin() + l[j]);
        as.push_back(f[j]);
        solve(at, as);
    }
}

int main()
{
    const std::vector<piece> p =
    { 
        /*top, right, bottom, left*/
    piece(1, 4, -1, -3),
    piece(1, 4, -4, -2),
    piece(4, 2, -2, -1),
    piece(2, 1, -1, -2),
    piece(2, 1, -4, -4),
    piece(4, 2, -2, -4),
    piece(2, 1, -3, -2),
    piece(3, 3, -2, -1),
    piece(2, 3, -1, -3),
    piece(2, 3, -2, -1),
    piece(3, 1, -4, -3),
    piece(2, 2, -2, -4),
    piece(2, 3, -3, -4),
    piece(3, 4, -4, -2),
    piece(3, 3, -4, -1),
    piece(4, 4, -2, -3) };

    for (int i = 0; i < 16; i++) {
        std::vector<piece> a = p;
        std::vector<piece> s; 
        s.push_back(p[i]);
       
        a.erase(a.begin() + i);

        solve(a, s);
    }
    printf("%i", sol);
}

