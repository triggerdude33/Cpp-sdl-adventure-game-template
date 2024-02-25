#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <vector>

template <typename T>
class Matrix {
    // T must be move-constructible
    static_assert(std::is_copy_constructible_v<T>, "Matrix elements requires copying");

    // T must be move-assignable
    static_assert(std::is_move_assignable_v<T>, "Matrix elements requires assigning");

public:
    
    Matrix(size_t rows, size_t cols)
        : m_rows(rows)
        , m_cols(cols)
        , m_capacity(rows*cols)
        , m_vec(std::vector<T>(m_capacity, T()))
    {}

    size_t rows() const {
        return m_rows;
    }
    
    size_t cols() const {
        return m_cols;
    }
    
    T& operator()(size_t row, size_t col) {
        if(row >= m_rows || col >= m_cols || (int)row < 0 || (int)col < 0){
            std::cerr << "Element (" << row << ", " << col << ")" << std::endl;
            throw std::out_of_range("Specified element is out of bounds for matrix");
        } 
            
        return *(m_vec.begin() + m_cols*row + col);
    }

    
    const T& operator()(size_t row, size_t col) const {
        if(row >= m_rows || col >= m_cols || (int)row < 0 || (int)col < 0) 
            throw std::out_of_range("Specified element is out of bounds for matrix");

        return *(m_vec.begin() + m_cols*row + col);
    }
    
    T* begin() const {
        return m_vec.begin();
    }

    T* end() const {
        return m_vec.end();
    }

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    std::vector<T> m_vec;
};


#endif //MATRIX_H

