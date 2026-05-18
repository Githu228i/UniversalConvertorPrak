#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>

class InputValidator
{
public:
    InputValidator();
    void ShowError(std::string message);
    bool InputCheck(std::string input, double p, double q);

private:
    bool SquareOpen;
    bool PeriodOpen;
    bool PeriodClosed;
    int curNum;
    bool IsNum;
    bool PeriodPart;
    bool WholePart;
    bool RationalPart;
    bool Correct;
    bool WasPoint;

};

#endif // INPUTVALIDATOR_H
