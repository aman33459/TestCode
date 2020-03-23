#include <boost/math/tools/precision.hpp>
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include<iomanip>
//typedef cpp_bin_float_2000 cpp_bin_float_2000;
typedef boost::multiprecision::number<boost::multiprecision::cpp_bin_float<2000> > cpp_bin_float_2000;
cpp_bin_float_2000 sqr(cpp_bin_float_2000 n, cpp_bin_float_2000 i, cpp_bin_float_2000 j) 
{ 
    cpp_bin_float_2000 mid = (i + j) / 2; 
    cpp_bin_float_2000 mul = mid * mid; 
    // If mid itself is the square root, 
    // return mid
    //std:: cout << std::setprecision(std::numeric_limits <cpp_bin_float_2000 > :: max_digits10) << fabs(mul- n) <<  " " << n-mul <<  "  " << cpp_bin_float_2000(1e-9)   << "\n"; 
    if ((mul == n) || fabs(mul - n) <= cpp_bin_float_2000(1e-18)) 
        return mid; 
  
    // If mul is less than n, recur second half 
    else if (mul < n) 
        return sqr(n, mid, j); 
  
    // Else recur first half 
    else
        return sqr(n, i, mid); 
} 
void convert_to_hex(cpp_bin_float_2000 point){
	//std::cout << point << std::endl; 
	int precision = std::numeric_limits <cpp_bin_float_2000 > :: max_digits10;
	precision+=(4- precision%4); // converting it to 
	int cn=4;
	int val = 0;
	int two[]={1,2,4,8};
	char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	while(point && precision ){
		//std::cout << point << std::endl;
		if(cn == 0) {
			std::cout << hex[val];
			val = 0;
			cn=4;
		}
		if(point * 2 >= cpp_bin_float_2000(1)) {
			val += two[(cn-1)];
			point = point*2 - cpp_bin_float_2000(1);
		}
		else point = point*2;
		cn--;
		precision--;
	}
	return;
}
int main(){
	using boost::multiprecision::cpp_int;
	//taking an unsigned int of 1024 bits and more
	cpp_int number = (cpp_int(1) << 1025)-1;
	//number= 25;
	// the value of the number taken as input
	std::cout << number << "\n\n\n\n****\n\n\n\n";
	//sqrt(x) calculate the integral square root of the number . the actual value will lie somewhere in between [sqrt(x),sqrt(x)+1] so we do 
	//a binary search on it.
	cpp_int square_root = sqrt(number);
	if(square_root * square_root == number){
		std::cout << "Decimal value is " << square_root << std::endl;
		std::cout << "Hexadecimal value is " << std::hex << std::showbase << square_root << std::endl;
	}
	else{
		//std::string s = answer.str(0, std::ios_base::fmtflags(std::ios_base::floatfield));
		cpp_bin_float_2000 answer  = sqr(cpp_bin_float_2000(number) , cpp_bin_float_2000(square_root), cpp_bin_float_2000(square_root+1) );
		std::cout << std::setprecision(std::numeric_limits <cpp_bin_float_2000 > :: max_digits10)  << answer << std::endl;
		std::cout << "Hexadecimal value is-\n"; 
		std::cout << std::hex << std::showbase  << cpp_int(answer) << ".";
		cpp_bin_float_2000 point = answer - cpp_bin_float_2000(cpp_int(answer));
		convert_to_hex(point);
		std::cout << std::endl;
		std::cout << "Hexadecimal value for double precision is " << std::hexfloat << double(answer) << std::endl;
	}
	
	

}