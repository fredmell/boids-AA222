#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstddef>
#include <array>
#include <iostream>
#include "vec2.hpp"

struct Rectangle{
    Rectangle(const Vec2& p1, const Vec2& p2){
        double x1, x2, y1, y2;
        if (p1.x < p2.x){
            x1 = p1.x;
            x2 = p2.x;
        } else {
            x1 = p2.x;
            x2 = p1.x;
        }
        if (p1.y < p2.y){
            y1 = p1.y;
            y2 = p2.y;
        } else {
            y1 = p2.y;
            y2 = p1.y;
        }
        ul = Vec2(x1, y2);
        ll = Vec2(x1, y1);
        ur = Vec2(x2, y2);
        lr = Vec2(x2, y1);
        center = Vec2((x2-x1)/2, (y2-y1)/2);
    }
    Vec2 ul;
    Vec2 ll;
    Vec2 ur;
    Vec2 lr;
    Vec2 center;
    inline const double width(){
        return ur.x - ul.x;
    };
    inline const double height(){
        return ul.y - ll.y;
    };
    bool contains(const Vec2& point) const{
        if(point.x < ll.x || point.x > lr.x)
            return false;
        if(point.y < ll.y || point.y > ul.y)
            return false;
        return true;
    }
};

template <typename T>
class QuadTree
{
public:
    QuadTree(int level, Rectangle bounds);
    virtual ~QuadTree(){};

    void clear();
    void split();
    int index(const T& object);
    void insert(const T& object);


    const static unsigned int max_objects = 10;
    const unsigned int max_levels = 5;

    const unsigned int level;
    const Rectangle bounds;

protected:
    std::size_t num_objs = 0;
    T objects[max_objects];
    std::array<QuadTree<T>*, 4> nodes;
};

template <typename T>
QuadTree<T>::QuadTree(int level_, Rectangle bounds_)
    :level(level_), bounds(bounds_) {
}

template <typename T>
void QuadTree<T>::clear() {
    num_objs = 0;
    for(int i = 0; i < 4; i++){
        if(nodes[i] != nullptr){
            nodes[i]->clear();
            nodes[i] = nullptr;
        }
    }
}

template <typename T>
void QuadTree<T>::split(){
    /*
   ul +-----+-----+ ur
      |     |     |
      |  3  |  2  |
      |     |     |
      +-----+-----+
      |     |     |
      |  0  |  1  |
      |     |     |
   ll +-----+-----+ lr

     */
    nodes[0] = new QuadTree<T>(level+1, Rectangle(bounds.ll, bounds.center));
    nodes[1] = new QuadTree<T>(level+1, Rectangle(bounds.lr, bounds.center));
    nodes[2] = new QuadTree<T>(level+1, Rectangle(bounds.ur, bounds.center));
    nodes[3] = new QuadTree<T>(level+1, Rectangle(bounds.ul, bounds.center));
}

template <typename T>
int QuadTree<T>::index(const T& object){
    if(bounds.contains(object->pos)){
        bool left = object->pos.x < bounds.center.x;
        bool lower = object->pos.y < bounds.center.y;
        if(left){
            if(lower){
                return 0;
            } else {
                return 3;
            }
        } else {
            if(lower){
                return 1;
            } else {
                return 2;
            }
        }
    }
    // Not contained, must be contained in parent
    return -1;
}

template <typename T>
void QuadTree<T>::insert(const T& object){
    int index_;

    std::cerr << "Inserting at level " << level << std::endl;
    std::cerr << "Nodes[0]" << nodes[0] << std::endl;
    // Attempt to add the object to a child
    if(nodes[0] != nullptr){
        index_ = index(object);
        if (index_ != -1){
            nodes[index_]->insert(object);
            return;
        }
    }

    //std::cerr << "to myself" << std::endl;
    // No children, so add the object to me
    objects[num_objs++] = object;

    // If I need to split, send all of my elements to my children
    // or copy the remaining to myself
    if (num_objs >= max_objects && level < max_levels){
        //std::cerr << "Nodes[0]" << nodes[0] << std::endl;
        if(nodes[0] == nullptr){
            std::cerr << "I should split now" << std::endl;
            split();
        }

        T tmp[max_objects];
        int k = 0;
        // Move to children
        for(int i = 0; i < num_objs; i++){
            index_ = index(objects[i]);
            //std::cerr << "moving to " << index_ << std::endl;
            if(index_ != -1){
                //std::cerr << objects[i] << std::endl;
                //std::cerr << (nodes[0] == nullptr) << std::endl;
                //std::cerr << (nodes[index_] == nullptr) << std::endl;
                nodes[index_]->insert(objects[i]);
            } else {
                tmp[k++] = objects[i];
            }
        }
        // std::cerr << "Done" << std::endl;
        // Copy remaining back to myself
        for(int i = 0; i < k; i++){
            objects[i] = tmp[i];
        }
        num_objs = k;
    }
}

#endif /* QUADTREE_H */
