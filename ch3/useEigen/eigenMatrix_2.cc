#include <iostream>
#include <ctime>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

#define MATRIX_SIZE 50

int main(int argc, char const *argv[])
{
    Matrix<float, 2, 3> matrix_23;
    Vector3d v_3d;

    Matrix<double, 3, 1> vd_3d;

    Matrix3d matrix_33 = Matrix3d::Zero();

    Matrix<double, Dynamic, Dynamic> matrix_dynamic;

    MatrixXd matrix_xd;
    
    matrix_23 << 1, 2,3,4,5,6;
    cout << "matrix_23 from 1 to 6: \n" << matrix_23 << endl;

    cout << "print matrix_23" << endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix_23(i, j) << "\t";
        }
        cout << endl;
    }

    v_3d << 3,2,1;
    vd_3d << 4, 5,6;

    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;

    cout << " [1,2,3,4,5,6] * [3,2,1]="<<result.transpose()<<endl;

    Matrix<double, 2, 1> result_2 = matrix_23.cast<double>() * vd_3d;

    cout << "[1,2,3,4,5,6] * [4,5,6] = "<<result_2.transpose()<<endl;

    matrix_33 = Matrix3d::Random();

    cout << "random matrix: "<< matrix_33 << endl;
    cout << "transpose: " << matrix_33.transpose() << endl;
    cout << "sum: " << matrix_33.sum() << endl;
    cout << "trace: " << matrix_33.trace() << endl;
    cout << "times 10: \n" << 10 * matrix_33 << endl;
    cout << "inverse: \n" << matrix_33.inverse() << endl;
    cout << "det: " << matrix_33.determinant() << endl;

    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;

    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);

    matrix_NN = matrix_NN * matrix_NN.transpose(); 

    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    // To solve Matrix_NN * x = v_Nd

    // Use x = Matrix_NN.transpose() * v_Nd.
    clock_t time_start = clock();
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time of normal inverse is " 
        << 1000 * (clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;

    cout << "x=" << x.transpose() << endl;


    // QR decomposition
    time_start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomposition is "
        << 1000 * (clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;

    cout << "x=" << x.transpose() << endl;

    // Cholesky for Positive Definite Matrix.
    time_start = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of Cholesky decomposition is "
        << 1000 * (clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;
    
    cout << "x=" << x.transpose() << endl;

    return 0;
}
