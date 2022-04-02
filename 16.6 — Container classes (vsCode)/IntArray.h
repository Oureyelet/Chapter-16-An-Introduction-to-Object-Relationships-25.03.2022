#ifndef INTARRAY_H
#define INTARRAY_H

#include <cassert> // for assert()
#include <iostream>

class IntArray
{
private:
    int m_lenght{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int lenght)
        :m_lenght{ lenght }
    {
        assert(lenght >= 0);

        if(lenght > 0)
        {
            m_data = new int[lenght]{};
        }
    }

    void printOn(std::ostream& out) const
    {
        if(m_lenght == 0)
            out << "Empty array" << '\n';

        for(int index{ 0 }; index < m_lenght; ++index)
        {
            out << m_data[index] << ' ';
        }
        out << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, const IntArray array)
    {
        array.printOn(out);
        return out;
    }

    ~IntArray()
    {
        delete[] m_data;
        // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately 
        //after this function anyway
    }

    void erase()
    {
        delete[] m_data;

        // We need to make sure we set m_data to nullptr here, otherwise it will
        // be left pointing at deallocated memory!
        m_data = nullptr;
        m_lenght = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_lenght);
        return m_data[index];
    }

    int getLenght() const { return m_lenght; };

    // reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
    void reallocate(int newLengt)
    {
        // First we delete any existing elements
        erase();

        // If our array is going to be empty now, return here
        if(newLengt <= 0)
            return;

        // Then we have to allocate new elements
        m_data = new int[newLengt];
        m_lenght = newLengt;
    }

    // resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
    void resize(int newLenght)
    {
        // if the array is already the right length, we're done
        if(newLenght == m_lenght)
            return;

        // If we are resizing to an empty array, do that and return
        if(newLenght <= 0)
        {
            erase();
            return;
        }

        /*
        Now we can assume newLength is at least 1 element.  This algorithm
        works as follows: First we are going to allocate a new array.  Then we
        are going to copy elements from the existing array to the new array.
        Once that is done, we can destroy the old array, and make m_data
        point to the new array.
        */

        // First we have to allocate a new array
        int* data{ new  int[newLenght] };

        /*
        Then we have to figure out how many elements to copy from the existing
        array to the new array.  We want to copy as many elements as there are
        in the smaller of the two arrays.
        */
        if(m_lenght > 0)
        {
            int elementToCopy{ (newLenght > m_lenght) ? m_lenght : newLenght };

            for(int index{ 0 }; index < elementToCopy; ++index)
            {
                data[index] = m_data[index];
            }
        }

        // Now we can delete the old array because we don't need it any more
        delete[] m_data;

        /*
        And use the new array instead!  Note that this simply makes m_data point
        to the same address as the new array we dynamically allocated.  Because
        data was dynamically allocated, it won't be destroyed when it goes out of scope.
        */
        m_data = data;
        m_lenght = newLenght;
    }

    void insertBefore(int value, int index)
    {
        // Sanity check our index value
        assert(value >= 0 && index <= m_lenght);

        // First create a new array one element larger than the old array
        int* data{ new int[m_lenght+1] };

        // Copy all of the elements up to the index
        for(int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        // Insert our new element into the new array
        data[index] = value;

        // Copy all of the values after the inserted element
        for(int after{ index }; after < m_lenght; ++after)
            data[after+1] = m_data[after];
        
        // Finally, delete the old array, and use the new array instead
        delete[] m_data;
        m_data = data;
        m_lenght = m_lenght + 1;

    }

    void remove(int index)
    {
        // Sanity check our index value
        assert(index >= 0 && index < m_lenght);

        // If this is the last remaining element in the array, set the array to empty and bail out
        if(m_lenght == 1)
        {
            erase();
            return;
        }

        // First create a new array one element smaller than the old array
        int* data{ new int{m_lenght - 1} };

        // Copy all of the elements up to the index
        for(int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        // Copy all of the values after the removed element
        for(int after{ index + 1 }; after < m_lenght; ++after)
            data[ after - 1 ] = m_data[ after ];
    
        delete[] m_data;
        m_data = data;
        --m_lenght;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_lenght); }
};

#endif // end INTARRAY_H