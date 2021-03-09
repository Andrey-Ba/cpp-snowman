#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

using namespace std;

void valid_number_check(int n)
{
    string err_msg = "Invalid code '" + to_string(n) + "'";
    if(n < 10000000 || n > 99999999) {throw out_of_range{err_msg};}
    int i = 7;
	while(n > 0)
	{
        int temp = n%10;
        if(temp == 0 || temp > 4) {throw out_of_range{err_msg};}
		n /= 10;
		i--;
	}
}

void int_to_array2(int *arr, int n)
{
	int i = 7;
	while(n > 0)
	{
		arr[i] = n%10;
		n /= 10;
		i--;
	}
}

string draw_hat(int h)
{
    if(h == 1) {return " _===_";}
    if(h == 2) {return "  ___ \n  .....";}
    if(h == 3) {return "   _ \n  /_\\";}
    return " ___ \n(_*_)";
}

string draw_eye(int e)
{
    if(e == 1) {return ".";}
    if(e == 2) {return "o";}
    if(e == 3) {return "O";}
    return "-";
}

string draw_nose(int n)
{
    if(n == 1) {return ",";}
    if(n == 2) {return ".";}
    if(n == 3) {return "_";}
    return " ";
}

string draw_head(int n, int l, int r, int x, int y)
{
    string s = "";
    if(x == 2) {s += "\\";}
    else {s += " ";}
    s += "(";
    s += draw_eye(l);
    s += draw_nose(n);
    s += draw_eye(r);
    s += ")";
    if(y == 2) {s += "/";}
    else {s += " ";}
    return s;
}

string draw_torso(int t, int x, int y)
{
    string s = "";
    if(x == 1) {s += "<";}
    else if(x == 3) {s += "/";}
    else {s += " ";}
    s += "(";
    if(t == 1) {s += " : ";}
    else if(t == 2) {s += "] [";}
    else if(t == 3) {s += "> <";}
    else {s += "   ";}
    s += ")";
    if(y == 1) {s += ">";}
    else if(y == 3) {s += "\\";}
    else {s+= " ";}
    return s;
}

string draw_bottom(int b)
{
    if(b == 1) {return " ( : )";}
    if(b == 2) {return " (\" \")";}
    if(b == 3) {return " (___)";}
    return " (   )";
}

namespace ariel{
    string snowman(int n)
    {
        valid_number_check(n);
        string drawing = "";
        int arr[8] = {0};
        int_to_array2(arr, n);
        drawing += draw_hat(arr[0]) + "\n";
        drawing += draw_head(arr[1], arr[2], arr[3], arr[4], arr[5]) + "\n";
        drawing += draw_torso(arr[6], arr[4], arr[5]) + "\n";
        drawing += draw_bottom(arr[7]);
        return drawing;
    }
}

