#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstddef>
#include <array>
#include <iostream>
#include <stdexcept>
#include "vec2.hpp"
#include <SFML/Graphics.hpp>


struct Rectangle{
    Rectangle(const Vec2& p1, const Vec2& p2){
        double x1, x2, y1, y2;
        if (p1.x < p2.x){
            x1 = p1.x;
            x2 = p2.x;
        } else if (p1.x > p2.x){
            x1 = p2.x;
            x2 = p1.x;
        } else {
            p1.print();
            p2.print();
            throw(std::runtime_error("Rectangle corners are equal in x"));
        }
        if (p1.y < p2.y){
            y1 = p1.y;
            y2 = p2.y;
        } else if (p1.y > p2.y){
            y1 = p2.y;
            y2 = p1.y;
        } else {
            throw(std::runtime_error("Rectangle corners are equal in y"));
        }
        ll = Vec2(x1, y1);
        lr = Vec2(x2, y1);
        ul = Vec2(x1, y2);
        ur = Vec2(x2, y2);
        center = Vec2(x1 + (x2-x1)/2, y1 + (y2-y1)/2);
    }
    Rectangle(const Vec2& centrum, double width)
        : Rectangle(centrum - width/2, centrum+width/2){
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
    void draw(sf::Vertex* box) const{
        box[0].position = ll.toSf();
        box[1].position = lr.toSf();

        box[2].position = lr.toSf();
        box[3].position = ur.toSf();

        box[4].position = ur.toSf();
        box[5].position = ul.toSf();

        box[6].position = ul.toSf();
        box[7].position = ll.toSf();
    }
    void print() const{
        ll.print();
        lr.print();
        ul.print();
        ur.print();
        center.print();
    }
};

template <typename T>
class QuadTree
{
public:
    QuadTree(int level, Rectangle bounds);
    QuadTree(int level, Rectangle bounds, QuadTree<T>* parent);
    virtual ~QuadTree(){};

    void clear();
    void split();
    int index(const T& object);
    void insert(const T& object);
    void print() const;
    void printTree() const;
    void increaseDepth();

    void draw(sf::VertexArray&) const;
    void draw(sf::VertexArray&, int&) const;
    int getDepth() const;

    const static unsigned int max_objects = 5;
    const unsigned int max_levels = 100;

    const unsigned int level;
    const Rectangle bounds;

    int depth = 0;
protected:
    std::size_t num_objs = 0;
    T objects[max_objects];
    std::array<QuadTree<T>*, 4> nodes;
    QuadTree<T>* parent;
};

template <typename T>
QuadTree<T>::QuadTree(int level_, Rectangle bounds_)
    :level(level_), bounds(bounds_) {
    nodes[0] = nullptr;
    nodes[1] = nullptr;
    nodes[2] = nullptr;
    nodes[3] = nullptr;
    depth = 0;
}

template <typename T>
QuadTree<T>::QuadTree(int level_, Rectangle bounds_, QuadTree<T>* parent_)
    :QuadTree(level_, bounds_) {
    parent = parent_;
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
    nodes[0] = new QuadTree<T>(level+1, Rectangle(bounds.ll, bounds.center), this);
    nodes[1] = new QuadTree<T>(level+1, Rectangle(bounds.lr, bounds.center), this);
    nodes[2] = new QuadTree<T>(level+1, Rectangle(bounds.ur, bounds.center), this);
    nodes[3] = new QuadTree<T>(level+1, Rectangle(bounds.ul, bounds.center), this);
    increaseDepth();
}

template <typename T>
void QuadTree<T>::increaseDepth(){
    depth++;
    if(level != 0){
        parent->increaseDepth();
    }
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
    } else if (level == 0){
        throw(std::runtime_error("Initial bounding box too small"));
    }
    // Not contained, must be contained in parent
    return -1;
}

template <typename T>
void QuadTree<T>::insert(const T& object){
    int index_;

    //std::cerr << "Inserting at level " << level << std::endl;
    //std::cerr << "with " << num_objs << " objects" << std::endl;
    //std::cerr << "Nodes[0]" << nodes[0] << std::endl;
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
    if (num_objs >= max_objects && level < max_levels){
        //std::cerr << "Nodes[0]" << nodes[0] << std::endl;
        if(nodes[0] == nullptr){
            //std::cerr << "I should split now" << std::endl;
            split();
        }
        //printTree();

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
                std::cerr << "Error at level: " << level
                          << "\nwith objects: " << num_objs
                          << "\nand a node[0]: " << nodes[0];
                printTree();

                throw(std::runtime_error("Unable to fit my own object into any children"));
            }
        }
        // std::cerr << "Done" << std::endl;
        num_objs = 0;
    }
}

template <typename T>
void QuadTree<T>::print() const {
    std::string offset(level, ' ');
    std::cout << offset << "Level: " << level << " with " << num_objs << " objects.\n"
              << offset << "Box: " << bounds.ll << " " << bounds.lr << " "
              << bounds.ur << " " << bounds.ul << "\n"
              << offset << "Nodes: \n";
    for(auto node: nodes){
        if(node != nullptr){
            node->print();
        }
    }
}

template <typename T>
void QuadTree<T>::printTree() const {
    if(level != 0){
        parent->printTree();
    } else {
        print();
    }
}

template <typename T>
int QuadTree<T>::getDepth() const {
    int d = 1;
    for(auto node: nodes){
        if(node != nullptr){
            d += node->getDepth();
        }
    }
    return d;
}


template <typename T>
void QuadTree<T>::draw(sf::VertexArray& array) const {
    int start = 0;
    draw(array, start);
    //std::cout << "ROOT START: " << start << std::endl;
}


template <typename T>
void QuadTree<T>::draw(sf::VertexArray& array, int& start) const {
    // Uses up 4
    bounds.draw(&array[start]);
    start += 8;

    for(auto node: nodes){
        if(node != nullptr){
            node->draw(array, start);
        }
    }
    //std::cout << "START: " << start << std::endl;
}

#endif /* QUADTREE_H */
