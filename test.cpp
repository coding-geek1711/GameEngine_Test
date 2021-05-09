#include <iostream>

int main()
{
    int arr[] = {
        4,2,2,1,1,2,
        1,2,2,1,1,2,
        1,2,2,1,1,2,
        1,1,2,3,3,2,
        1,1,2,1,3,2,
        1,2,2,1,3,2,
        1,2,2,1,4,2
    };

    int arr1[7*6];
    for(int i = 0; i <6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            std::cout << arr[j + i*6] << " ";
            arr1[i + j * 6] = arr[i + j * 6];
        }
        std::cout<<std::endl;
    }
    std::cout <<"+++++++++++++++++++++\n"; 
    for(int i = 0; i <6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            std::cout << arr1[i + j*6] << " ";
            // arr1[i + j * 6] = arr[i + j * 6];
        }
        std::cout<<std::endl;
    }

    return 0;
}