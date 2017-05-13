#ifndef ARRAY3D_H
#define ARRAY3D_H

class Array3D
{
private:
    int height, width, depth;
    double *array;

public:
    Array3D(const int height, const int width, const int depth)
    {
        this->height = height;
        this->width  = width;
        this->depth  = depth;

        if(height <= 0) this->height = 1;
        if(width <= 0)  this->width  = 1;
        if(depth <= 0)  this->depth  = 1;

        array = new double[this->height * this->width * this->depth];
        //array = (double*) malloc( (this->height*) * sizeof(double));
    }

    ~Array3D()
    {
        delete [] array;
    }

    void setValue(const int i, const int j, const int k, double value)
    {
        array[(i * this->width + j) * this->depth + k] = value;
    }

    double getValue(const int i, const int j, const int k) const
    {
        return array[(i * this->width + j) * this->depth + k];
    }

    int getHeight(void) const
    {
        return this->height;
    }

    int getWidth(void) const
    {
        return this->width;
    }

    int getDepth(void) const
    {
        return this->depth;
    }
};

#endif // ARRAY3D_H
