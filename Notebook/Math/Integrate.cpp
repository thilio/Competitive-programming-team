/*
   Title: Simpson's rule for numerical integration
   Description: Integrate function f over [a, b] 
   Complexity: O(n), where n is the number of steps
   Details: The error should be proportional to
            h^4, where h is the the size of the
            step.

            Example:
            auto f = [&](double x){
               return x*x;
            };
            quad(0, 1, f);
   Credits: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/Integrate.h
*/

template<class F>

double Simp(double a, double b, F f, const int n = 1000){
   double h = (b - a)/ 2 / n, v = f(a) + f(b);
   for(int i = 1; i < 2*n; i++){
      v += f(a + i*h)*(i&1 ? 4 : 2);
   }

   return v*h/3;
}