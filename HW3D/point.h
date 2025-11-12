//
// Created by bambuchachkin on 11/12/25.
//

#ifndef POINT_H
#define POINT_H



class point {
    int p_x, p_y, p_z;
public:
    point(int x, int y, int z);

    int get_x() const;
    int get_y() const;
    int get_z() const;
};



#endif //POINT_H
