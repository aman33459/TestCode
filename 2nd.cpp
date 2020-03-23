#include <boost/multiprecision/cpp_bin_float.hpp>//for cpp_bin_float_100 
#include <iostream>
#include <boost/math/special_functions/relative_difference.hpp> // for the function relative_difference
//#include<boost/math>
//computing e^x using taylor approxmiation
template<typename value_type>
   value_type e_x(value_type x)
{
 // e^x = 1+x+x^2/2!+x^3/3!+x^4/4!+.....
   value_type temp = x;
   value_type fac = 1 ; // to store the factorial
    value_type answer = 1; // to store the final answer
    value_type prev;
    value_type i =1;
   do{
		prev = answer;
		 fac = fac * i;
		answer = answer + x/fac;
		x = x *temp;
		i=i+1;
	}while(boost::math::relative_difference(prev,answer)); // if the relative difference is very low then exit
	return answer;
}

int main(){
	using boost::multiprecision::cpp_bin_float_100;
	 const cpp_bin_float_100 val = e_x(
      cpp_bin_float_100(2));
	 std:: cout << std::setprecision(std::numeric_limits <cpp_bin_float_100 > :: max_digits10) << val << "\n";
	return 0;
}

/// output
////7.389056098930650227230427460575007813180315570551847324087127822522573796079057763384312485079121795873