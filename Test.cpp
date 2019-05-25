#include <unittest++/UnitTest++.h>
#include "/home/asic27/LFSR/PSPGen/LFSR.h"
#include "/home/asic27/LFSR/PSPGen/LFSR.cpp"
struct LFSRSeed_fixture {
    LFSR * p;
   LFSRSeed_fixture() {
      p = new LFSR(1);
   }
   ~LFSRSeed_fixture() {
        delete p;
   }
};
SUITE(SeedTest)
{
    TEST(ValidSeed) {
        CHECK_EQUAL(0xfffffffeaaaaaaa8,LFSR(1).LFSR_Galois(0x8000000080000002));
    }
    TEST(ZEROSedd){
    CHECK_THROW(LFSR(0),LFSR_error);
    }
    TEST(NegativeSeed){
        CHECK_THROW(LFSR(-23),LFSR_error);
    }
}
SUITE(PolynominalTest){
    TEST_FIXTURE(LFSRSeed_fixture,ValidPolynomial){
        CHECK_EQUAL(0x8000000080000002,p->Polynomial_Converter("x^64+x^32+x^2+1"));
    }
    TEST_FIXTURE(LFSRSeed_fixture,Polynomialwhithout64){
        CHECK_THROW(p->Polynomial_Converter("x^63+x^3+x^2+1"),LFSR_error);
    }
    TEST_FIXTURE(LFSRSeed_fixture,Polynomialwithoutdegree){
        CHECK_THROW(p->Polynomial_Converter("x^64+x^+x^2+1"),LFSR_error);
    }
    TEST_FIXTURE(LFSRSeed_fixture,PolynomialwhithAlienSimbol){
        CHECK_THROW(p->Polynomial_Converter("y^64+x^2+1"),LFSR_error);
    }
    TEST_FIXTURE(LFSRSeed_fixture,Polynomialmore64){
        CHECK_THROW(p->Polynomial_Converter("x^64+x^127+x^2+1"),LFSR_error);
    }
    TEST_FIXTURE(LFSRSeed_fixture,MAXPolymial){
        CHECK_EQUAL(0xffffffffffffffff,p->Polynomial_Converter("x^64+x^63+x^62+x^61+x^60+x^59+x^58+x^57+x^56+x^55+x^54+x^53+x^52+x^51+x^50+x^49+x^48+x^47+x^46+x^45+x^44+x^43+x^42+x^41+x^40+x^39+x^38+x^37+x^36+x^35+x^34+x^33+x^32+x^31+x^30+x^29+x^28+x^27+x^26+x^25+x^24+x^23+x^22+x^21+x^20+x^19+x^18+x^17+x^16+x^15+x^14+x^13+x^12+x^11+x^10+x^9+x^8+x^7+x^6+x^5+x^4+x^3+x^2+x^1+1"));
    }
    TEST_FIXTURE(LFSRSeed_fixture,WrongOrder){
        CHECK_THROW(p->Polynomial_Converter("x^64+x^31+x^62+1"),LFSR_error);
    }
    TEST_FIXTURE(LFSRSeed_fixture,Equaldegree){
        CHECK_THROW(p->Polynomial_Converter("x^64+x^32+x^32+1"),LFSR_error);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
