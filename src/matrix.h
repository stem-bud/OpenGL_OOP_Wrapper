#include "shader.h"

#ifndef MATRIX_HEADER
#define MATRIX_HEADER
/**
 * @brief wrapper for opengl matrices with helper function (row major matrices)
 */
class matrix
{
    private:
    public:
        static const int number_of_axes = 3;
        enum class Axes
        {   
            x_axis,
            y_axis,
            z_axis,
        };
        enum class Matrix_Types
        {
            MAT_4,
            MAT_3,
            MAT_2
        };
    private:
        matrix::Matrix_Types matrix_type = matrix::Matrix_Types::MAT_3;
        /**
         * @param mat_type enum value of the types of square matrices allowed
         * @return size associated with enum
         */
        static int get_size(Matrix_Types mat_type);
    public:
        matrix() = delete;
        matrix(const matrix&) = delete;
        matrix& operator=(const matrix&) = delete;
        matrix(matrix&& other) = delete;
        matrix& operator=(matrix&& other) = delete;        

        /**
         * @param angle rotation in degrees
         * @param axis which axis the rotation is meant to be about. 0,1,2, for x,y, and z respectively
         * @param store array to store resulting matrix
         * @return void
         */
        static void rotation_matrix(float angle,matrix::Axes axis,float*store);

        /**
         * @param mat_type size of square matrix
         * @param array to store result; must have size equal to the square of the corresponding mat_type n in which n is equal to rows or columns
         */
        static void identity_matrix(matrix::Matrix_Types mat_type,float* store);

        /**
         * @param matrix1 the first square matrix
         * @param matrix2 the second square matrix
         * @param mat_type size of each matrix
         * @param store array to store resulting matrix
         * @return void 
         */
        static void square_matrix_multiplication(const float* matrix1,const float* matrix2,matrix::Matrix_Types mat_type,float* store);
        /**
         * @brief outputs string representation of square matrix
         * @param data square matrix
         * @param mat_type size of matrix MAT_2,MAT_3, and MAT_4 for 2x2, 3x3, and 4x4 respectively
         * @return Pointer to dynamically allocated char array (caller owns memory)
         */
        
        static std::string output_square_matrix(const float* data,matrix::Matrix_Types mat_type);


        /**
         * @brief intrinsic rotation matrix for all axes in 3 dimension
         * @param angle_x angle about x axis in degree
         * @param angle_y angle about y axis in degree
         * @param angle_z angle about z axis in degree
         * @param store array to store resulting matrix
         * @return void
         */
        static void rotation_matrix(float angle_x,float angle_y,float angle_z,float* store);

        /**
         * @brief provides different orders of rotation
         * @param angular_sets n sequences of angles for each axes in degress row_n = [angle_x_n,angle_y_n,angle_z_n] for n = 1...n
         * @param sequences number of sequences in which a sequence is equal to a rotation about the x axis, followed by a rotation about the y axis, followed by a rotation about the z axis
         * @param store array to store resulting matrix
         * @return void
         */
        static void rotation_set(const float* angular_sets,int sequences,float* store);
        /**
         * @brief provides different orders of rotation
         * @param initial_axes starting axes to apply rotations to
         * @param angular_sets n sequences of angles for each axes in degress row_n = [angle_x_n,angle_y_n,angle_z_n] for n = 1...n
         * @param sequences number of sequences in which a sequence is equal to a rotation about the x axis, followed by a rotation about the y axis, followed by a rotation about the z axis
         * @param store array to store resulting matrix
         * @return void
         */
        static void rotation_set(const float* initial_axes,const float* angular_sets,int sequences,float* store);
        /**
         * @brief performs a rotational transformation on the initial axes given
         * @param initial_axes initial axes
         * @param angle angular change to perform in degrees
         * @param axis which axis to perform the rotation on
         * @param store where to store the resulting tranformation
         * @return void
         */
        static void add_rotation(const float* initial_axes,float angle,matrix::Axes axis,float* store);
};

#endif
