#ifndef SOMME_HPP
#define	SOMME_HPP

class Somme{
public:
    
    Somme(int i):value(i){};
    ~Somme(){}
    
    int getSommeValue() const;
    void setSommeValue(int value);
    
private:
    int value;
};

#endif	/* SOMME_HPP */

