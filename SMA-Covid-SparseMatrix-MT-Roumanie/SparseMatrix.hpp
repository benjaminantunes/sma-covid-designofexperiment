#pragma once
#include <iostream>
#include <set>
#include <exception>

template<typename T>
class MatrixCell{
    private:
        unsigned int x;
        unsigned int y;
        T elem;

    public:
        MatrixCell(unsigned int x, unsigned int y, T elem): x(x), y(y), elem(elem) {}

        const unsigned int getX() const
        {
            return x;
        }

        const unsigned int getY() const
        {
            return y;
        }

        T getElem() const
        {
            return elem;
        }

        void setElem(T inElem){
            elem = inElem;
        }


};

template<typename T>
bool operator<( const MatrixCell<T> & a, const MatrixCell<T> & b)
{
    if( a.getX() == b.getX())
    {
        return a.getY() < b.getY();
    }
    else
    {
        return a.getX() < b.getX();
    }
}

template<class T>
struct cell_less{
    constexpr bool operator()(const MatrixCell<T>& lhs, const MatrixCell<T>& rhs) const 
    {
        return lhs < rhs; // assumes that the implementation handles pointer total order
    }
};


template<typename T>
class SparseMatrix
{
    private:
        T defaultValue;
        unsigned int width;
        unsigned int height;
        std::set<MatrixCell<T>, cell_less<T>> tab;

    public:
        SparseMatrix(T defaultValue): 
            defaultValue(defaultValue), width(0), height(0), tab(std::set<MatrixCell<T>, cell_less<T>>()) 
            {}

        SparseMatrix(T defaultValue, unsigned int inWidth, unsigned int inHeight): 
            defaultValue(defaultValue), width(inWidth), height(inHeight), tab(std::set<MatrixCell<T>, cell_less<T>>()) 
            {}

        void set_size(unsigned int inWidth, unsigned int inHeight)
        {
            width = inWidth;
            height = inHeight;
        }
        
        void add(T inElem, unsigned int inX, unsigned int inY)
        {
            if( inX < width && 0 <= inX && inY < height && 0 <= inY)
            {
                if(tab.find(MatrixCell<T>(inX, inY, defaultValue)) == tab.end())
                {
                    tab.insert(MatrixCell<T>(inX, inY, inElem));
                }
                else
                {
                    throw std::invalid_argument(
                            "Cell (" + std::to_string(inX) + ", " + std::to_string(inY) + ") is already filled");
                }
            }
            else
            {
                throw std::out_of_range(
                            "Cell (" + std::to_string(inX) + ", " + std::to_string(inY) + ") is out of bounds");
            }
        }

        unsigned int getNumberOfElements() const
        {
            return tab.size();
        }

        unsigned int getWidth() const
        {
            return width;
        }

        unsigned int getHeight() const
        {
            return height;
        }

        void remove(unsigned int inX, unsigned int inY)
        {
            auto elemIterator = tab.find(MatrixCell<T>(inX, inY, defaultValue));

            if(elemIterator != tab.end())
            {
                tab.erase(elemIterator);
            }
            else
            {
                throw std::out_of_range(
                        "Element (" + std::to_string(inX) + " , " + std::to_string(inY) + " ) was not found"
                        );
            }
        }

        T operator()(unsigned int inX, unsigned int inY) const
        {
            auto elemIterator = tab.find(MatrixCell<T>(inX, inY, defaultValue));

            if(elemIterator != tab.end())
            {
                return elemIterator->getElem();
            }
            else
            {
                return defaultValue;
            }
        }
};