// #include <iostream>
// // #include <bits/stdc++.h>

// using namespace std;

// void Hello()
// {
//     cout << "Hello, World!";
//     return;
// }
// void Numbers()
// {
//     float a = 1, b = 1.2, c = 1.9;
//     cout << "\n"
//         << a << "\n"
//         << b << "\n"
//         << c;
//     cin >> a;
//     cout << a;
// }

// void NumberAndfloat()
// {
//     int a, c;
//     float b, d;
//     cin >> a;
//     cin >> b;
//     c = a + b;
//     d = a + b;
//     cout << c << d;
// }
// void Condition()
// {
//     int a = 2;
//     if (a > 1)
//     {
//         cout << "masuk sini\n";
//     }
//     string Sekarang = "Pelatdas";
//     if (Sekarang == "Pelatdas")
//     {
//         cout << "makan roti";
//     }
//     else if (Sekarang == "minum")
//     {
//         cout << "tidak haus";
//     }
//     else
//     {
//         cout << "tidur";
//     }
//     return;
// }
// void looping(){
//     for (int i = 1; i <=5; i++){
//         cout << "halo : "<< i << endl;
//     }
// }

// void WhileBreak(){
//     int n = 0;
//     while(true){
//         if (n>100){
//             break;
//         }
//         if(n%2 == 0){
//             n++;
//             continue;
//         }

//         cout<<n<<endl;
//         n++;
//     }
// }

// void teriak(string nama){
//     cout<<"hidup "<<nama<<endl;
// }

// int main()
// {
//     // Hello();
//     // Numbers();
//     // NumberAndfloat();
//     // Condition();
//     // looping();
//     // WhileBreak();
//     teriak("Jokowi");
//     teriak("Fufufafa");
// }

#include <stdio.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point a, b, c;
} CustomStruct;

float CustomFunc(CustomStruct cs) {
    float ar = (float) cs.a.x * (cs.b.y - cs.c.y)
             + cs.b.x * (cs.a.y - cs.c.y) + cs.c.x * (cs.a.y - cs.b.y);
            printf("%f", ar);
    if (ar < 0.0)
        ar *= -1.0;
    return 0.5 * ar;
}

int main() {
    CustomStruct strct;
    strct.a.x = -5;
    strct.a.y = -10;
    strct.b.x = 0;
    strct.b.y = 5;
    strct.c.x = 5;
    strct.c.y = -10;
    
    printf("%.2f\n", CustomFunc(strct));
    return 0;
}