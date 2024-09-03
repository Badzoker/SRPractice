#include <iostream>

using namespace std;


float Plus(float _x, float _y);
float Minus(float _x, float _y);
float Divine(float _x, float _y);


int main()
{
    cout << "Hello World!\n";
    cout << "각자 자신의 이름을 쓰시오." << endl;
    cout << "이름 : 김유빈";
    cout << "이름 : 이종한";
    
    cout << "이름 : 김유빈";
    cout << "이름 : 정연욱" << endl;


    cout << "계산기" << endl;

    int a(0);
    float x(0.f), y(0.f), z(0.f);
    cout << "1번째 값 :  ";
    cin >> x;
    cout << "2번째 값 :  ";
    cin >> y;

    cout << "어떤 계산을 할 것인가" << endl;
    cout << "1.더하기 2.빼기 3.곱하기 4.나누기 " << endl;
    cin >> a;


    switch (a)
    {
    case 1:
         z = Plus(x, y);
        break;
    case 2:
        z = Minus(x, y);
        break;
    case 3:
        break;
    case 4:
        z = Divine(x, y);
        break;
    default:
        break;
    }

    cout << "계산한 값은 : " << z << endl;
}

float Plus(float _x, float _y)
{
    //이종한
    return _x + _y;
}

float Minus(float _x, float _y)
{
    //강범승
    return _x - _y;
}

float Multi(float _x, float _y)
{
    //정연욱
    return _x * _y;
}

float Divine(float _x, float _y)
{
    //김유빈
    return _x / _y;
}