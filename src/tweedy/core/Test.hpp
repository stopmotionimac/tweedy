#ifndef TEST_HPP
#define TEST_HPP

enum ImediaType {
    ImediaTypeClip,
    ImediaTypePisteClip,
    ImediaTypeMediaExt,
    ImediaTypeTimeline
};

class Test
{
public:
    Test(ImediaType i):mediaType(i){};
protected:
    int value;
    ImediaType mediaType;
};

class TestB : public Test {
    TestB(ImediaType i) : Test(i){};
};

//Voiture() : IVehicule(eVehiculeTypeVoiture)
#endif // TEST_HPP
