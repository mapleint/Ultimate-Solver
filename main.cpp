#include <iostream>
#include <vector>

struct piece {
    char t, r, b, l;
    int i = 0;
    piece(char in1, char in2, char out1, char out2, char index) {
        t = in1;
        r = in2;
        b = out1;
        l = out2;
        i = index;
    }
    piece flip() {
        piece out = piece(r, t, l, b, i);
        return out;
    }
};
int sol = 0;
void solve(std::vector<piece> a, std::vector<piece> s) {
    /*if no pieces are avaliable, we won*/
    if (a.size() < 1){
        for(int i = 0; i < 16; i++)
            printf("index %i, top is %i + ", s[i].i, s[i].t);
        exit();
        sol++;
        return;
        }
    std::vector<piece> f;
    std::vector<int> l;
    /* go through all unused pieces, see if they would fit, if so add them to 'fit' vector*/
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
    /*call solve with every fitting piece*/
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
        /*stout, stin, cross, circle*/
    piece(1, 1, -3, -4, 1),
    piece(2, 4, -4, -2, 2),
    piece(4, 4, -4, -2, 3),
    piece(4, 2, -3, -4, 4),
    
    piece(1, 4, -3, -4, 5),
    piece(1, 1, -2, -3, 6),
    piece(1, 3, -2, -1, 7),
    piece(4, 1, -3, -1, 8),
    
    piece(4, 3, -2, -2, 9),
    piece(3, 2, -3, -1, 10),
    piece(2, 1, -4, -2, 11),
    piece(2, 2, -1, -4, 12),
    
    piece(3, 4, -4, -3, 13),
    piece(3, 4, -4, -1, 14),
    piece(3, 2, -2, -4, 15),
    piece(4, 1, -1, -2, 16) };

    for (int i = 0; i < 16; i++) {
        // a = avaliable, s = solution vectors
        std::vector<piece> a = p;
        std::vector<piece> s; 
        s.push_back(p[i]);
       
        a.erase(a.begin() + i);

        solve(a, s);
        if(!sol)
            return 0;
    }
    printf("%i", sol);
}
