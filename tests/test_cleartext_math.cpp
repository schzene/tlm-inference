#include "utils/emp-tool.h"
#include "cleartext_library_fixed_uniform.h"
using namespace std;
using namespace sci;

void test_cleartext_div_floor()
{
    int64_t a = 3500, b = 64;
    int64_t quot, rem;
    div_floor(a, b, quot, rem);
    uint64_t result = quot & moduloMask;
    cout << result << endl;
}
void test_cleartext_math() {}
int main()
{
    test_cleartext_math();
    test_cleartext_div_floor();
}