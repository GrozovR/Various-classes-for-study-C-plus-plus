#pragma once

#include <vector>

static const int BufferSize = 1000;
/*
//template<typename T>
class CircuralBuffer {
public:
    CircuralBuffer()
  //      : buffer[bufferSize]
    {
        bufferBegin = 0;
        elementCount = 0;
        buffer.reserve(BufferSize);
    }

    size_t GetDataCount() { return elementCount; }

    int Get(size_t index) {
        if (index > BufferSize) {
            return -1;
        }

        int correctIndex = bufferBegin + index < BufferSize
            ? bufferBegin + index
            : bufferBegin + index - BufferSize;

        return buffer[correctIndex];
    }

    void InsertInBegin(std::vector<int> values)
    {
        if (values.size() < BufferSize) {
            //assert();
        }
        if (elementCount == 0) {
            insertInPosition(0, values);
            return;
        }

        size_t indexToInsert = bufferBegin < values.size()
            ? BufferSize - (values.size() - bufferBegin)
            : bufferBegin - values.size();

        insertInPosition(indexToInsert, values);
    }

    void InsertInEnd(std::vector<int> values)
    {
        insertInPosition(bufferEnd(), values);
    }

private:
    //T[] buffer;
    std::vector<int> buffer;
    size_t elementCount;
    size_t bufferBegin;

    size_t bufferEnd()
    {
        return ( bufferBegin + elementCount ) < BufferSize
            ? bufferBegin + elementCount
            : ( bufferBegin + elementCount ) - BufferSize;
    }

    void insertInPosition(size_t indexToInsert, const vector<int>& values) {

        size_t toCopy = min(BufferSize - indexToInsert, values.size());
        
        buffer.insert(indexToInsert, values, toCopy);// TODO: correct function
        if (toCopy < values.size()) {
            buffer.insert(0, values[toCopy], values.size() - toCopy);// TODO: correct function

            elementCount = min(BufferSize, elementCount + values.size());
        }
    }
};
*/